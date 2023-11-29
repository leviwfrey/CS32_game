#include <iostream>
#include <GL/glut.h>
#include <Draw.h>

// Makes a square move accross the screen forever

Point p = {-.5, 0};

// you can change these to make it faster or bigger
double size = .15;
double velocity = .01;



void update(int value) {
    static_cast<void>(value);
    p.x += velocity;
    if(p.x >= 1+size/2) {
        p.x = -1-size/2;
    }
    
    glutPostRedisplay(); // calls the display function
    glutTimerFunc(16, update, 0); // calls the update function again after 16 milliseconds (60FPS)
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT); // clears the canvas
    drawRect(.1, .4, p); // draws a square on the canvas at the point
    glutSwapBuffers();  // swaps the canvas with the current screen
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
    //    these two should be realy simple

    glutMainLoop(); //runs the function.
    return 0;   
}



