#include <iostream>
#include <GL/glut.h>
#include <Draw.h>
#include "Controller.h"

// Makes a square move accross the screen forever
Controller controller;
Point p = {0, 0};

// you can change these to make it faster or bigger
double size = .06;
const double max_vel = .015;

double x_vel = 0;
double y_vel = 0;




void update(int value) {
    static_cast<void>(value);
    controller.update();
    x_vel = max_vel*controller.getX();
    y_vel = max_vel*controller.getY();
    p.x += x_vel;
    p.y += y_vel;
    
    glutPostRedisplay(); // calls the display function
    glutTimerFunc(16, update, 0); // calls the update function again after 16 milliseconds (60FPS)
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT); // clears the canvas
    drawSquare(size, p); // draws a square on the canvas at the point
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
    glutInit(&argc, argv); // Intiates screen?
    glutInitDisplayMode(GLUT_SINGLE); //You need to do once ig
    glutInitWindowSize(1400, 1400); //sets the size, might be pixel by pixel
    glutInitWindowPosition(0,0);    //position of window on screen
    glutCreateWindow("Funny little square!!"); 

    // Game Loop:
    glutDisplayFunc(display); // function that paints everything on the screen
    glutTimerFunc(25, update, 0); // function that should do all the logic for entities
    glutKeyboardFunc(handleKeyPress);
    glutKeyboardUpFunc(handleKeyReleased);
    
    // these two should be realy simple

    glutMainLoop(); //runs the function.
    return 0;   
}



