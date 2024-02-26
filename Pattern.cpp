#include <GL/glut.h>
#include <cmath>

int segmentCount = 8;
float size = 20;
float currentSize;

void drawShape(float radius, int numSegments, float offset = 0)
{
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numSegments; ++i)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);

        float x = radius * cosf(theta + offset);
        float y = radius * sinf(theta + offset);

        glVertex2f(x, y);
    }
    glEnd();
}

void drawPattern()
{
    for (int i = 0; i < 10; i++)
    {
        drawShape(currentSize * (float)i / 10, segmentCount);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);

    int numRepetitionsX = 10;
    int numRepetitionsY = 10;

    for (int i = 0; i < numRepetitionsX; ++i)
    {
        for (int j = 0; j < numRepetitionsY; ++j)
        {
            glPushMatrix();
            glTranslatef(i * size, j * size, 0.0);
            drawPattern();
            glPopMatrix();
        }
    }

    glutSwapBuffers();
}

void handleKeyPress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        segmentCount++;
        break;
    case 's':
        segmentCount--;
        break;
    case 'd':
        currentSize++;
        break;
    case 'a':
        currentSize--;
        break;
    }

    glutPostRedisplay();
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, (size) * 5, 0, (size) * 5);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char *argv[])
{
    currentSize = size;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(600, 600);

    glutCreateWindow("Pattern");
    glutDisplayFunc(display);
    init();

    glutKeyboardFunc(handleKeyPress);

    glutMainLoop();
    return 0;
}
