#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <math.h>
#include <stdlib.h>

const double TWO_PI = 0.0 - 6.2831853;
GLsizei width = 400, height = 400;

GLuint regHex;

class screenPt{
private: GLint x, y;
    
public:
    screenPt(){
        x = y = 0;
    }
    void setCoor (GLint xC, GLint yC){
        x = xC;
        y = yC;
    }
    GLint getx() const{
        return x;
    }
    GLint gety() const{
        return y;
    }
    void incrX(){
        x++;
    }
    void decrY(){
        y--;
    }
};

void setPixel (GLint xC, GLint yC){
    glBegin(GL_POINTS);
    glVertex2i(xC, yC);
    glEnd();
}

void circleMidpoint(GLint xc, GLint yc, GLint radius){
    screenPt circPt;
    GLint p = 1 - radius;
    circPt.setCoor(0, radius);
    void circlePlotPoints(GLint, GLint, screenPt);
    circlePlotPoints(xc, yc, circPt);
    while (circPt.getx()<circPt.gety()) {
        circPt.incrX();
        if(p<0)
            p += 2*circPt.getx()+1;
        else{
            circPt.decrY();
            p += 2*(circPt.getx()-circPt.gety())+1;
        }
        circlePlotPoints(xc, yc, circPt);
    }
}

void circlePlotPoints(GLint xc, GLint yc, screenPt circPt){
    setPixel(xc + circPt.getx(), yc + circPt.gety());
    setPixel(xc - circPt.getx(), yc + circPt.gety());
    setPixel(xc + circPt.getx(), yc - circPt.gety());
    setPixel(xc - circPt.getx(), yc - circPt.gety());
    setPixel(xc + circPt.gety(), yc + circPt.getx());
    setPixel(xc - circPt.gety(), yc + circPt.getx());
    setPixel(xc + circPt.gety(), yc - circPt.getx());
    setPixel(xc - circPt.gety(), yc - circPt.getx());
}

void init(){
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 400.0, 0.0, 400.0);
}

void printCircle(){
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    circleMidpoint(200, 200, 90);
    circleMidpoint(100, 100, 40);
    circleMidpoint(100, 300, 40);
    circleMidpoint(300, 100, 40);
    circleMidpoint(300, 300, 40);
    glEnd();
    glFlush();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Circles");
    init();
    glutDisplayFunc(printCircle);
    glutMainLoop();
    return 0;
}
