#include <GL/glut.h>
#include <cmath>

float shapeVertices[10][2] = {{0.0f, 1.0f}, {1.0f, 0.5f}, {2.0f, 0.0f}, {1.5f, -1.0f}, {1.0f, -2.0f}, {0.0f, -2.0f}, {-1.0f, -2.0f}, {-1.5f, -1.0f}, {-2.0f, 0.0f}, {-1.0f, 0.5f}};

float pentagonVertices[10][2] = {{0.0f, 1.0f}, {1.0f, 0.5f}, {2.0f, 0.0f}, {1.5f, -1.0f}, {1.0f, -2.0f}, {0.0f, -2.0f}, {-1.0f, -2.0f}, {-1.5f, -1.0f}, {-2.0f, 0.0f}, {-1.0f, 0.5f}};

float starVertices[10][2] = {{0.0f, 1.0f}, {0.5f, 0.0f}, {2.0f, 0.0f}, {1.0f, -1.0f}, {1.5f, -2.0f}, {0.0f, -1.5f}, {-1.5f, -2.0f}, {-1.0f, -1.0f}, {-2.0f, 0.0f}, {-0.5f, 0.0f}};

int animationDuration = 5000;
int animationStartTime;
bool isAnimating = false;
bool isPentagon = true;

void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-5.0f, 5.0f, -5.0f, 5.0f);
}

void drawShape()
{
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 0.0f, 0.0f);
    for (int i = 0; i < 10; ++i)
    {
        glVertex2fv(shapeVertices[i]);
    }
    glEnd();
}

void updateVertices(float targetShape[10][2])
{
    float t = (glutGet(GLUT_ELAPSED_TIME) - animationStartTime) / static_cast<float>(animationDuration);
    if (t >= 1.0f)
    {
        isAnimating = false;
        return;
    }

    for (int i = 0; i < 10; ++i)
    {
        float x = (1.0f - t) * shapeVertices[i][0];
        float y = (1.0f - t) * shapeVertices[i][1];
        x += t * targetShape[i][0];
        y += t * targetShape[i][1];
        shapeVertices[i][0] = x;
        shapeVertices[i][1] = y;
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (isAnimating)
    {
        if (isPentagon)
            updateVertices(starVertices);
        else
            updateVertices(pentagonVertices);
    }

    drawShape();

    glutSwapBuffers();
}

void animate(int value)
{
    glutPostRedisplay();
    if (isAnimating)
    {
        glutTimerFunc(16, animate, 0);
    }
}

void startAnimation()
{
    isAnimating = true;
    isPentagon = !isPentagon;
    animationStartTime = glutGet(GLUT_ELAPSED_TIME);
    glutTimerFunc(0, animate, 0);
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'a')
    {
        startAnimation();
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Pentagon to Star Animation");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();
    return 0;
}
