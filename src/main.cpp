#include <iostream>
#include <GL/glut.h>
#include <random>
#include <vector>
#include "Entity.h"
#include "Controller.h"
#include "EntityHandler.h"
#include "Difficulty.h"
#include <memory>
#include <algorithm>

using namespace std;

//Global Constants
int const SCREEN_WIDTH = 1400;
int const SCREEN_HEIGHT = 1400;
size_t const MAX_DIFFICULTY = 10;

enum GameState {
    START_SCREEN,
    GAME_SCREEN,
    END_SCREEN
};

// Instansiate needed classes and variables
shared_ptr<EntityHandler> entityHandler = make_shared<EntityHandler>();
size_t difficulty = 0;
shared_ptr<Player> player = make_shared<Player>(entityHandler); // Our games only Player object
vector<size_t> highscores;
GameState gameState;

void drawText(double r, double g, double b, int xPos, int yPos, string text){
    glColor3f(r,g,b);  // Set text color
    glRasterPos2f(xPos, yPos);  // Set the starting position for the text
    // Render each character in the string
    for (char c: text) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
}

void removeDuplicatesAndSort(std::vector<size_t>& arr) {
    // Remove duplicates
    std::sort(arr.begin(), arr.end());
    auto last = std::unique(arr.begin(), arr.end());
    arr.erase(last, arr.end());

    // Sort in ascending order
    std::sort(arr.begin(), arr.end());
}

void spawnEnemies(size_t _difficulty){
    if(gameState == GAME_SCREEN){
    
        Difficulty diff = Difficulty(player, entityHandler);
        vector<shared_ptr<Entity>> enemies = diff.getEnemiesByDifficulty(_difficulty);
        for(shared_ptr<Entity> npc : enemies){
            entityHandler->addEntity(npc, "Enemies");
        }
    }
}

void drawEndScreen(size_t score){
    
    drawText(1.0, 1.0, 1.0, -200, 300, "YOU DIED");
    drawText(1.0, 1.0, 1.0, -200, 250, "Press k to play again");
    drawText(1.0, 1.0, 1.0, -200, 200, "Difficulty on Death: " + to_string(score - 1));
    drawText(1.0, 1.0, 1.0, -200, 150, "Top 5 Attempts By Difficulty Reached:");
    int originaly = 100;
    removeDuplicatesAndSort(highscores); //sorts in ascending order
    std::reverse(highscores.begin(), highscores.end()); //now in descending order
    int numScores = 0;
    for(size_t score: highscores){
        drawText(1.0, 1.0, 1.0, -200, originaly, to_string(score));
        originaly -= 50; numScores++;
        if(numScores >= 5){break;}
    }
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    if(gameState == START_SCREEN){
        drawText(1.0, 1.0, 1.0, -200, 600, "WELCOME: press w to begin");
        drawText(1.0, 1.0, 1.0, -200, 550, "use WASD to move, and spacebar to shoot");
        drawText(1.0, 1.0, 1.0, -200, 500, "don't get shot or collide with an enemy!");
    }
    if (gameState == GAME_SCREEN) {
        string text2 = "Difficulty: " + std::to_string(difficulty);
        drawText(1.0, 1.0, 1.0, 0, 600, text2);
        entityHandler->drawAll();
    } else if(gameState == END_SCREEN) {
        drawEndScreen(difficulty);
    }
    glutSwapBuffers();  // swaps the canvas with the current screen
}

void handleKeyPress(unsigned char key, int x, int y) {

    if(gameState == GAME_SCREEN){
        static_cast<void>(x);
        static_cast<void>(y);
        player->controller.setKey(key, true); // feeds the controller keys pressed
    } else if (gameState == END_SCREEN && key == 'k'){ //resets the game
        gameState = GAME_SCREEN;
        difficulty = 0;
        player = make_shared<Player>(entityHandler);
        entityHandler->addEntity(player, "Players");
        spawnEnemies(difficulty);
    } else if (gameState == START_SCREEN && key == 'w'){
        gameState = GAME_SCREEN;
    }
}

void handleKeyReleased(unsigned char key, int x, int y) {
    if(gameState == GAME_SCREEN) {
        static_cast<void>(x); 
        static_cast<void>(y);
        player->controller.setKey(key, false); // feeds the controller keys unpressed
    }
}

void mouseMotion(int x, int y) {
    if(gameState == GAME_SCREEN) {
        Vector2d mousePos;
        mousePos.x = x - (SCREEN_WIDTH / 2);
        mousePos.y = (SCREEN_HEIGHT / 2) - y;
        player->controller.setMousePos(mousePos); // feeds controller the position of the mouse on the screen
    }
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width / 2.0, width / 2.0, -height / 2.0, height / 2.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

void update(int value) {
    if(gameState == GAME_SCREEN) {
        static_cast<void>(value);
        entityHandler->updateAll();
        entityHandler->checkCollisions();
        entityHandler->print();
        if(!player->alive()) {
            player = nullptr;
            gameState = END_SCREEN;
            highscores.push_back(difficulty);
            entityHandler->clearAllEntities();
        }
        if(entityHandler->empty("Enemies")){
            difficulty++;
            if(difficulty > MAX_DIFFICULTY){
              gameState = END_SCREEN;
              highscores.push_back(difficulty - 1);
              //drawEndScreen();
              return;
            }
            spawnEnemies(difficulty);
          }
    } else {
        entityHandler->print();
    }
    
    glutPostRedisplay();          // calls the display function
    glutTimerFunc(16, update, 0); // calls the update function again after 16 milliseconds (60FPS)
}


int main(int argc, char** argv) {

    // Initiation:
    glutInit(&argc, argv);                          // Intiates screen?
    glutInitDisplayMode(GLUT_SINGLE);               //You need to do once ig
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT); //sets the size, might be pixel by pixel
    glutCreateWindow("Funny little square!!"); 
    reshape(SCREEN_WIDTH, SCREEN_HEIGHT);
    
    gameState = START_SCREEN;
    // Game Loop:
    glutDisplayFunc(display); // function that paints everything on the screen
    glutTimerFunc(25, update, 0); // function that should do all the logic for entities
    glutKeyboardFunc(handleKeyPress);
    glutKeyboardUpFunc(handleKeyReleased);
    glutPassiveMotionFunc(mouseMotion);
    glutReshapeFunc(reshape);
    
    entityHandler->addGroup("Players");
    entityHandler->addGroup("Projectiles");
    entityHandler->addGroup("Enemies");
    entityHandler->addGroup("EnemyProjectiles");

    entityHandler->addCollision("Players", "Enemies");
    entityHandler->addCollision("Enemies", "Projectiles");

    entityHandler->addCollision("Players", "EnemyProjectiles");


    entityHandler->addEntity(player, "Players");
    spawnEnemies(difficulty);
    glutMainLoop(); //runs the function.
    return 0;   
}



