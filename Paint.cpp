#include <GL/glut.h>
#include <stdio.h>

int screenWidth = 800;
int screenHeight = 600;

int brushSize = 5;  // Initial brush size

bool isMousePressed = false;
int mouseX, mouseY;

void drawBrush(float x, float y) {
    glPointSize(brushSize);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

void mouseMotion(int x, int y) {
    if (isMousePressed) {
        glColor3f(0.0, 0.0, 0.0);  // Set brush color (black in this case)
        drawBrush(x, screenHeight - y);  // Invert y-coordinate to match OpenGL's coordinate system
        glutSwapBuffers();
    }
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isMousePressed = true;
            mouseX = x;
            mouseY = screenHeight - y;  // Invert y-coordinate to match OpenGL's coordinate system
        } else if (state == GLUT_UP) {
            isMousePressed = false;
        }
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'c':
            glClear(GL_COLOR_BUFFER_BIT);
            glutSwapBuffers();
            break;
        case '+':
            brushSize++;
            break;
        case '-':
            if (brushSize > 1) {
                brushSize--;
            }
            break;
    }
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // Set background color to white
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, screenWidth, 0.0, screenHeight);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(screenWidth, screenHeight);

    glutCreateWindow("Simple Paint in GLUT");
    glutDisplayFunc(display);
    
    glutPassiveMotionFunc(mouseMotion);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    
    init();
    glutMainLoop();
    return 0;
}
