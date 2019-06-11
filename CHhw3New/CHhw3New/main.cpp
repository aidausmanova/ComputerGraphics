#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

const double TWO_PI = 6.28;
GLint vert;
GLsizei winWidth = 400, winHeight = 400;
GLuint regHex;

class screenPt{
private:
    GLint x, y;
public:
    screenPt(){
        x = y = 0;
    }
    void setCoords (GLint xCoord, GLint yCoord){
        x = xCoord;
        y = yCoord;
    }
    GLint getx() const{
        return x;
    }
    GLint gety() const{
        return y;
    }
};

void init(void){
    screenPt hexVertex, circCtr;
    GLdouble theta;
    
    circCtr.setCoords(winWidth/2, winHeight/2);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    
        regHex = glGenLists(1);
        glNewList(regHex, GL_COMPILE);
        glColor3f(0.0, 0.5, 0.0);
        glBegin(GL_POLYGON);
        for(int i=0; i<vert; i++){
            theta = TWO_PI*i/(vert*1.0);
            hexVertex.setCoords(circCtr.getx()+150*cos(theta), circCtr.gety()+150*sin(theta));
            glVertex2i(hexVertex.getx(), hexVertex.gety());
        }
        glEnd();
        glEndList();
    
}

void Polygon (void){
    glClear(GL_COLOR_BUFFER_BIT);
    glCallList(regHex);
    glFlush();
}

void Reshape(int newW, int newH){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble) newW, 0.0, (GLdouble) newH);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char * argv[]) {
    cin>>vert;
    
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("HW3");
    
    init();
    glutDisplayFunc(Polygon);
    glutReshapeFunc(Reshape);
    glutMainLoop();
    return 0;
}
