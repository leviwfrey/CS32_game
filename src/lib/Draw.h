#ifndef DRAW_H
#define DRAW_H

#include <GL/glut.h>
#include <Point.h>


void drawSquare(double size, Point p) {
    glBegin(GL_POLYGON);

        glVertex3f(p.x - (size/2), p.y + (size/2), 0.0);  // set top left       
        glVertex3f(p.x + (size/2), p.y + (size/2), 0.0);  // set top right      
        glVertex3f(p.x + (size/2), p.y - (size/2), 0.0);  // set bottom right   
        glVertex3f(p.x - (size/2), p.y - (size/2), 0.0);  // set bottom left    
    
    glEnd(); 
}

void drawRect(double width, double height, Point p) {
    glBegin(GL_POLYGON);

        glVertex3f(p.x - (width/2), p.y + (height/2), 0.0);
        glVertex3f(p.x + (width/2), p.y + (height/2), 0.0);
        glVertex3f(p.x + (width/2), p.y - (height/2), 0.0);
        glVertex3f(p.x - (width/2), p.y - (height/2), 0.0);

    glEnd();
}


#endif