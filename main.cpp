#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

void init (void){
    glClearColor (1.0, 1.0, 1.0, 0.0); // Set display-window color to white.
    glMatrixMode (GL_PROJECTION); // Set projection parameters.
    gluOrtho2D (0.0, 200.0, 0.0, 150.0);
}

void lineSegment (void){
    glClear (GL_COLOR_BUFFER_BIT); // Clear display window.
    glColor3f (0.0, 0.4, 0.2); // Set line segment color to green.
    glBegin (GL_LINES);
    glVertex2i (180, 15); // Specify line-segment geometry.
    glVertex2i (10, 145);
    glEnd ( );
    glFlush ( ); // Process all OpenGL routines as quickly as possible.
}

void polygon(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2i(50, 50);
    glVertex2i(150, 50);
    glVertex2i(150, 120);
    glEnd();
    glFlush();
}

int main (int argc, char **argv){
    glutInit (&argc, argv); // Initialize GLUT.
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // Set display mode.
    glutInitWindowPosition (50, 70); // Set top-left display-window position.
    glutInitWindowSize (400, 300); // Set display-window width and height.
    glutCreateWindow ("First1");
    init();
    glutDisplayFunc(lineSegment);
    glutInitWindowPosition (50, 420);
    glutCreateWindow ("First2"); // Create display window.
    init ( ); // Execute initialization procedure.
    glutDisplayFunc (polygon); // Send graphics to display window.
    glutMainLoop ( ); // Display everything and wait.
}
