#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <stdbool.h>

unsigned char header[54];
unsigned int dataPos;
unsigned int width, height;
unsigned int imageSize;
unsigned char* data;
GLint ListBase = 0;
GLfloat xRotated, yRotated;

int ObjectRotatingAngle = 0;
unsigned int MyTextureObject[3];

typedef union PixelInfo{
    std::uint32_t Colour;
    struct{
        std::uint8_t B, G, R, A;
    };
} *PPixelInfo;

class BMP{
private:
    std::uint32_t width, height;
    std::uint16_t BitsPerPixel;
    std::vector<std::uint8_t> Pixels;
    
public:
    BMP(const char* FilePath);
    std::vector<std::uint8_t> GetPixels() const { return this->Pixels; }
    std::uint32_t GetWidth() const { return this->width; }
    std::uint32_t GetHeight() const { return this->height; }
    bool HasAlphaChannel() { return BitsPerPixel == 32; }
};

BMP::BMP(const char* FilePath){
    std::fstream hFile(FilePath, std::ios::in | std::ios::binary);
    if (!hFile.is_open()) throw std::invalid_argument("Error: File Not Found.");
    hFile.seekg(0, std::ios::end);
    std::size_t Length = hFile.tellg();
    hFile.seekg(0, std::ios::beg);
    std::vector<std::uint8_t> FileInfo(Length);
    hFile.read(reinterpret_cast<char*>(FileInfo.data()), 54);
    if (FileInfo[0] != 'B' && FileInfo[1] != 'M'){
        hFile.close();
        throw std::invalid_argument("Error: Invalid File Format. Bitmap Required.");
    }
    if (FileInfo[28] != 24 && FileInfo[28] != 32){
        hFile.close();
        throw std::invalid_argument("Error: Invalid File Format. 24 or 32 bit Image Required.");
    }
    BitsPerPixel = FileInfo[28];
    width = FileInfo[18] + (FileInfo[19] << 8);
    height = FileInfo[22] + (FileInfo[23] << 8);
    std::uint32_t PixelsOffset = FileInfo[10] + (FileInfo[11] << 8);
    std::uint32_t size = ((width * BitsPerPixel + 31) / 32) * 4 * height;
    Pixels.resize(size);
    
    hFile.seekg(PixelsOffset, std::ios::beg);
    hFile.read(reinterpret_cast<char*>(Pixels.data()), size);
    hFile.close();
}
void init() {
    glClearColor(0.0, 0.01, 0.1, 0.0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_SMOOTH);
    
    GLfloat ambient[] = { 0.4,0.4,0.4,1.0 };
    GLfloat diffuse[] = { 1.0,1.0,1.0,1.0 };
    GLfloat specular[] = { 1.0,1.0,1.0,1.0 };
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
}
void LoadEarth() {
    GLUquadricObj* sphere = NULL;
    sphere = gluNewQuadric();
    gluQuadricDrawStyle(sphere, GLU_FILL);
    gluQuadricTexture(sphere, true);
    gluQuadricNormals(sphere, GLU_SMOOTH);
    ListBase = glGenLists(9);
    glListBase(ListBase);
    glNewList(ListBase + 1, GL_COMPILE);
    gluSphere(sphere, 1.23, 35, 35);
    glEndList();
    gluDeleteQuadric(sphere);
}
void DrawEarth() {
    GLfloat position[] = { 0.0,0.0,0.0,1.0 };
    glPushMatrix();
    
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(270, 1.0, 0.0, 0.0);
    glRotatef(15, 0.0, 1.0, 0.0);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glColor3f(1.0, 1.0, 1.0);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, MyTextureObject[0]);
    glCallList(ListBase + 1);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
void LoadGLTextures(void) {
    glClearColor(0.0, 0.01, 0.1, 0.0);
    BMP info = BMP("/Users/aidausmanova/Desktop/texturemap1.bmp");
    glGenTextures(1, &MyTextureObject[0]);
    glBindTexture(GL_TEXTURE_2D, MyTextureObject[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, info.GetWidth(), info.GetHeight(), 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, info.GetPixels().data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glEnable(GL_TEXTURE_2D);
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(0.0, 0.0, -10.0); //VIEW!!!!!!!!!!!
    glRotatef(xRotated, 1.0, 0.0, 0.0);
    glRotatef(yRotated, 0.0, 1.0, 0.0);
    //DrawSpace();
    DrawEarth();
    glEnable(GL_LIGHTING);
    glPopMatrix();
    glRotated((GLdouble)ObjectRotatingAngle, 0.0, 1, 0.0);
    glColor3f(0.5, 0.5, 0);
    glFlush();
}
void MyReshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
//ROTATION
void idleFunc(void){
    yRotated += 0.2;
    display();
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 700);
    glutCreateWindow("Earth");
    xRotated=33;
    yRotated=40;
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(MyReshape);
    LoadEarth();
    LoadGLTextures();
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glutIdleFunc(idleFunc);
    glutMainLoop();
    return 0;
}
