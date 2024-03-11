#include <GL/freeglut.h>
#include <cmath>
#include <bits/c++config.h>

int gridRows = 4;
int gridCols = 4;

void drawWheel(float centerX, float centerY, float radius)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < 20; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(20);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(x + centerX, y + centerY);
    }
    glEnd();
}

void drawCar()
{
    // Car body
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(0.1, 0.1);
    glVertex2f(0.1, 0.25);
    glVertex2f(0.4, 0.25);
    glVertex2f(0.4, 0.35);
    glVertex2f(0.8, 0.35);
    glVertex2f(0.9, 0.25);
    glVertex2f(0.9, 0.1);
    glEnd();

    // Car windows
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(0.4, 0.25);
    glVertex2f(0.45, 0.3);
    glVertex2f(0.55, 0.3);
    glVertex2f(0.55, 0.25);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.65, 0.25);
    glVertex2f(0.65, 0.3);
    glVertex2f(0.75, 0.3);
    glVertex2f(0.8, 0.25);
    glEnd();

    // Wheels
    glColor3f(0.0, 0.0, 0.0);
    float wheelRadius = 0.05;
    float wheel1CenterX = 0.3, wheel1CenterY = 0.1;
    float wheel2CenterX = 0.7, wheel2CenterY = 0.1;

    drawWheel(wheel1CenterX, wheel1CenterY, wheelRadius);
    drawWheel(wheel2CenterX, wheel2CenterY, wheelRadius);
}

void display(void)
{
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);

    glClear(GL_COLOR_BUFFER_BIT);

    for (int row = 0; row < gridRows; ++row)
    {
        for (int col = 0; col < gridCols; ++col)
        {
            glViewport(col * width / gridCols, row * height / gridRows, width / gridCols, height / gridRows);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            bool mirrorX = col % 2 != 0;
            bool mirrorY = row % 2 != 0;
            if (mirrorX && mirrorY)
            {
                glOrtho(1, 0, 1, 0, -1, 1);
            }
            else if (mirrorX)
            {
                glOrtho(1, 0, 0, 1, -1, 1);
            }
            else if (mirrorY)
            {
                glOrtho(0, 1, 1, 0, -1, 1);
            }
            else
            {
                glOrtho(0, 1, 0, 1, -1, 1);
            }

            drawCar();
        }
    }

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mirrored Triangle Grid");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
