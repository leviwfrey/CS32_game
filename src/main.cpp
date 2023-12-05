#include <iostream>
#include <GL/glut.h>
#include <random>
#include <vector>
#include "Entity.h"
#include "Controller.h"
#include "EntityHandler.h"
#include <memory>

using namespace std;

//Global Constants
int const SCREEN_WIDTH = 1400;
int const SCREEN_HEIGHT = 1400;


// Instansiate needed classes
shared_ptr<EntityHandler> entityHandler = make_shared<EntityHandler>();
shared_ptr<Player> player = make_shared<Player>(entityHandler); // Our games only Player object


void update(int value) {
    static_cast<void>(value);
    entityHandler->updateAll();
    entityHandler->checkCollisions();
    
    glutPostRedisplay();          // calls the display function
    glutTimerFunc(16, update, 0); // calls the update function again after 16 milliseconds (60FPS)
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);                // clears the canvas
    entityHandler->drawAll();
    glutSwapBuffers();  // swaps the canvas with the current screen
}

void handleKeyPress(unsigned char key, int x, int y) {
    static_cast<void>(x);
    static_cast<void>(y);
    player->controller.setKey(key, true); // feeds the controller keys pressed
}

void handleKeyReleased(unsigned char key, int x, int y) {
    static_cast<void>(x);
    static_cast<void>(y);
    player->controller.setKey(key, false); // feeds the controller keys unpressed
}

void mouseMotion(int x, int y) {
    Vector2d mousePos;
    mousePos.x = x - (SCREEN_WIDTH / 2);
    mousePos.y = (SCREEN_HEIGHT / 2) - y;
    player->controller.setMousePos(mousePos); // feeds controller the position of the mouse on the screen
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width / 2.0, width / 2.0, -height / 2.0, height / 2.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {

    // Initiation:
    glutInit(&argc, argv);                          // Intiates screen?
    glutInitDisplayMode(GLUT_SINGLE);               //You need to do once ig
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT); //sets the size, might be pixel by pixel
    glutCreateWindow("Funny little square!!"); 
    reshape(SCREEN_WIDTH, SCREEN_HEIGHT);
    

    // Game Loop:
    glutDisplayFunc(display); // function that paints everything on the screen
    glutTimerFunc(25, update, 0); // function that should do all the logic for entities
    glutKeyboardFunc(handleKeyPress);
    glutKeyboardUpFunc(handleKeyReleased);
    glutPassiveMotionFunc(mouseMotion);
    glutReshapeFunc(reshape);
    // these two should be realy simple

    entityHandler->addGroup("Players");
    entityHandler->addGroup("Projectiles");
    entityHandler->addGroup("Enemies");

    entityHandler->addCollision("Players", "Enemies");
    entityHandler->addCollision("Enemies", "Projectiles");

    entityHandler->addEntity(player, "Players");

    shared_ptr<Npc> enemy = make_shared<Npc>();
    entityHandler->addEntity(enemy, "Enemies");


    glutMainLoop(); //runs the function.
    return 0;   
}



