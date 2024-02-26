#include <GL/glut.h>
#include <GL/glu.h>
#include <cmath>
#include <stdio.h>

float colorR = 0.0;
float colorG = 0.0;
float colorB = 0.0;

float size = 0.5;
int segmentCount = 8;

void resize(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawShape(float radius, int numSegments, float offset = 0)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments; ++i)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);

        float x = radius * cosf(theta + offset);
        float y = radius * sinf(theta + offset);

        glVertex2f(x, y);
    }
    glEnd();
}

void handleKeyPress(unsigned char key, int x, int y)
{
    switch (key)
    {
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
    case 'w':
        segmentCount++;
        break;
    case 's':
        segmentCount--;
        break;
    }

    glutPostRedisplay();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(colorR, colorG, colorB);

    // for (int i = 0; i < 10; i++)
    // {
    //     drawShape(size * (float)i / 10, segmentCount);
    // }
    drawShape(size, segmentCount);

    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(600, 600);

    glutCreateWindow("Polygon");
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(handleKeyPress);

    glClearColor(1, 1, 1, 1);
    glutMainLoop();
    return EXIT_SUCCESS;
}
