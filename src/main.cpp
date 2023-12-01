#include <iostream>
#include <GL/glut.h>
#include <random>
#include <vector>

#include "Draw.h"
#include "Entity.h"
#include "Controller.h"

//Global Constants
size_t const WINDOW_DIM_1 = 1400;
size_t const WINDOW_DIM_2 = 1400;


// Instansiate needed classes
Controller controller;
Player player(0.12, 0.015); //see constructor for instantitaion details
std::vector<Npc> npc_vec;


//Random Number generation
std::random_device rd;
std::uniform_real_distribution<double> distribution(-1, 1);
auto gen = std::default_random_engine(rd()); //distribution(gen) will generate a random number

void update(int value) {
    static_cast<void>(value);
    controller.update();
    player.update(controller.getX(), controller.getY());
    for(size_t i = 0; i < npc_vec.size(); ++i){ //updates the npc position
        npc_vec.at(i).update(distribution(gen), distribution(gen));
    }
    
    glutPostRedisplay();          // calls the display function
    glutTimerFunc(16, update, 0); // calls the update function again after 16 milliseconds (60FPS)
}

void spawnNpcs(size_t num_to_generate) {
    while(num_to_generate != 0){
        Npc npc = Npc(0.06, 0.015, distribution(gen), distribution(gen)); 
        npc.draw();
        npc_vec.push_back(npc);
        num_to_generate -= 1;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);                // clears the canvas
    player.draw();                               // draws a square on the canvas at the point
    for(size_t i = 0; i < npc_vec.size(); ++i){  //draws the npcs
        npc_vec.at(i).draw();
    }
    glutSwapBuffers();  // swaps the canvas with the current screen
}

void handleKeyPress(unsigned char key, int x, int y) {
    static_cast<void>(x);
    static_cast<void>(y);
    controller.setKey(key, true);
}

void handleKeyReleased(unsigned char key, int x, int y) {
    static_cast<void>(x);
    static_cast<void>(y);
    controller.setKey(key, false);
}

int main(int argc, char** argv) {

    // Initiation:
    glutInit(&argc, argv);                          // Intiates screen?
    glutInitDisplayMode(GLUT_SINGLE);               //You need to do once ig
    glutInitWindowSize(WINDOW_DIM_1, WINDOW_DIM_2); //sets the size, might be pixel by pixel
    glutInitWindowPosition(0,0);                    //position of window on screen
    glutCreateWindow("Funny little square!!"); 

    // Game Loop:
    spawnNpcs(5);
    glutDisplayFunc(display); // function that paints everything on the screen
    glutTimerFunc(25, update, 0); // function that should do all the logic for entities
    glutKeyboardFunc(handleKeyPress);
    glutKeyboardUpFunc(handleKeyReleased);
    
    // these two should be realy simple

    glutMainLoop(); //runs the function.
    return 0;   
}



