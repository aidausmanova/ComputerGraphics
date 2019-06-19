#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

void square(void){
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBegin(GL_QUADS);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(-0.5, -0.5);
        glVertex2f(0.5, -0.5);
        glVertex2f(0.5, 0.5);
        glVertex2f(-0.5, 0.5);
    glEnd();
     
    /*
    glBegin (GL_LINE_STRIP);
     glColor3f(1.0, 0.0, 0.0);
    glVertex2f(200, 100);
    glVertex2f(100, 200);
    glVertex2f(120, 50);
    glVertex2f(150, 200);
    glVertex2f(50, 100);
    glEnd ( );
    */
    glFlush();
}

void teapot(void){
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);
    glutWireTeapot(0.5);
    //glutSolidTeapot(.5);
    glFlush();
}

void points(void){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    //glClear(GL_COLOR_BUFFER_BIT);
    
    glBegin(GL_POINTS);
        glColor3f(1.0, 1.0, 1.0);
        glVertex2i(50, 100);
        glVertex2i(75, 150);
        glVertex2i(100, 200);
    glEnd();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(300, 300);
    glutCreateWindow("Square");
    glutDisplayFunc(square);
    
    glutInitWindowPosition(400, 50);
    glutCreateWindow("Teapot");
    glutDisplayFunc(teapot);
    
    glutInitWindowPosition(50, 400);
    glutCreateWindow("Points");
    glutDisplayFunc(points);
    glutMainLoop();
    return 0;
}
