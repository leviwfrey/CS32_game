#ifndef DRAW_H
#define DRAW_H

#include <GL/glut.h>
#include <vector>
#include "Vector2d.h"

using namespace std;

void drawSquare(double size, Vector2d p) {
    glBegin(GL_POLYGON);

        glVertex3f(p.x - (size/2), p.y + (size/2), 0.0);  // set top left       
        glVertex3f(p.x + (size/2), p.y + (size/2), 0.0);  // set top right      
        glVertex3f(p.x + (size/2), p.y - (size/2), 0.0);  // set bottom right   
        glVertex3f(p.x - (size/2), p.y - (size/2), 0.0);  // set bottom left    
    
    glEnd(); 
}

void drawRect(double width, double height, Vector2d p) {
    glBegin(GL_POLYGON);

        glVertex3f(p.x - (width/2), p.y + (height/2), 0.0);
        glVertex3f(p.x + (width/2), p.y + (height/2), 0.0);
        glVertex3f(p.x + (width/2), p.y - (height/2), 0.0);
        glVertex3f(p.x - (width/2), p.y - (height/2), 0.0);

    glEnd();
}

void drawPoly(Vector2d center, vector<Vector2d> points, double angle) {
    glBegin(GL_POLYGON);
        for(Vector2d p : points) {
            p = p.rotate(angle);
            glVertex3f(center.x + p.x, center.y + p.y, 0.0);
        }
    glEnd();
}

#endif