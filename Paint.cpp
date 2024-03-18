#include <GL/glut.h>

float window_width = 500.0f;
float window_height = 500.0f;

float calculateX(float x)
{
    return ((float)x) / window_width * 2.0f - 1.0f;
}
float calculateY(float y)
{
    return 1.0f - ((float)y) / window_height * 2.0f;
}

void drawPoint(int x, int y)
{
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex2f((x - glutGet(GLUT_WINDOW_WIDTH) / 2.0) / (glutGet(GLUT_WINDOW_WIDTH) / 2.0),
               -(y - glutGet(GLUT_WINDOW_HEIGHT) / 2.0) / (glutGet(GLUT_WINDOW_HEIGHT) / 2.0));
    glEnd();
    glFlush();
}

void display(void)
{
    glFlush();
}

void clearScreen()
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(1);
    glBegin(GL_POINTS);
    for (int x = 0; x < window_width; x++)
    {
        for (int y = 0; y < window_height; y++)
        {
            glVertex2f(calculateX((float)x), calculateY((float)y));
        }
    }
    glEnd();
    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'q':
        exit(0);
        break;

    case 'r':
        glColor3f(1.0f, 0.0f, 0.0f);
        break;
    case 'g':
        glColor3f(0.0f, 1.0f, 0.0f);
        break;
    case 'b':
        glColor3f(0.0f, 0.0f, 1.0f);
        break;

    case 'c':
        clearScreen();
        break;

    default:
        break;
    }
}

void reshape(int w, int h)
{
    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // gluOrtho2D(0, w, 0, h);

    // glMatrixMode(GL_MODELVIEW);
    // glViewport(0, 0, w, h);
}

void motion(int x, int y)
{
    drawPoint(x, y);
}

void timerRedisplay(int value)
{
    glutTimerFunc(32, timerRedisplay, 0);
    display();
}

void glutCallbacks()
{
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutMotionFunc(motion);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("Paint");
    clearScreen();
    glutCallbacks();
    glutMainLoop();
    return (0);
}