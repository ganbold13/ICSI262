#include <GL/glut.h>
#include <GL/glu.h>
#include <cmath>

float cameraX = 3.0;
float cameraY = 3.0;
float cameraZ = 3.0;

float colorR = 0;
float colorG = 0;
float colorB = 0;

GLfloat lightPosition[] = {1.0, 3.0, 2.0, 0.0};
GLfloat lightAmbient[] = {0.2, 0.2, 0.2, 1.0};
GLfloat lightDiffuse[] = {1.0, 1.0, 1.0, 1.0};
GLfloat lightSpecular[] = {1.0, 1.0, 1.0, 1.0};

GLfloat materialAmbient[] = {1.0, 0.0, 0.0, 1.0};
GLfloat materialDiffuse[] = {1.0, 0.0, 0.0, 1.0};
GLfloat materialSpecular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat materialShininess = 50.0;

GLfloat planeMaterialAmbient[] = {0.6, 0.6, 0.6, 1.0};

void drawCube()
{
    glColor3f(colorR, colorG, colorB);
    materialAmbient[0] = colorR;
    materialAmbient[1] = colorG;
    materialAmbient[2] = colorB;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, materialShininess);
    glutSolidCube(1.0);
}

void drawPlane()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, planeMaterialAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, materialShininess);

    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_QUADS);
    glVertex3f(-5.0, -0.5, -5.0);
    glVertex3f(5.0, -0.5, -5.0);
    glVertex3f(5.0, -0.5, 5.0);
    glVertex3f(-5.0, -0.5, 5.0);
    glEnd();
}

void setupLighting()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
}

void handleKeyPress(unsigned char key, int x, int y)
{
    int modifiers = glutGetModifiers();

    switch (key)
    {
    case 'w':
        cameraZ -= 0.1;
        break;
    case 's':
        cameraZ += 0.1;
        break;
    case 'a':
        cameraX -= 0.1;
        break;
    case 'd':
        cameraX += 0.1;
        break;
    case 'r':
        colorR += 0.1;
        break;
    case 'g':
        colorG += 0.1;
        break;
    case 'b':
        colorB += 0.1;
        break;
    case 't':
        colorR -= 0.1;
        break;
    case 'h':
        colorG -= 0.1;
        break;
    case 'n':
        colorB -= 0.1;
        break;
    }

    glutPostRedisplay();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(cameraX, cameraY, cameraZ, 0, 0, 0, 0, 1, 0);

    setupLighting();

    drawCube();
    drawPlane();

    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("3D Cube");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(handleKeyPress);

    glClearColor(1, 1, 1, 1);

    glutMainLoop();
    return EXIT_SUCCESS;
}
