#include <GL/glut.h>

// Rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

////////////////////////////////////////////////////////////////////////////
// Change viewing volume and viewport.  Called when window is resized
void ChangeSize(int w, int h)
{
    GLfloat fAspect;

    // Prevent a divide by zero
    if (h == 0)
        h = 1;

    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);

    fAspect = (GLfloat)w / (GLfloat)h;

    // Reset coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Produce the perspective projection
    gluPerspective(35.0f, fAspect, 1.0, 40.0);
    // glOrtho(-5.0, 5.0, -5.0, 5.0, 5.0, -5.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// This function does any needed initialization on the rendering
// context.  Here it sets up and initializes the lighting for
// the scene.
void SetupRC()
{

    // Light values and coordinates
    GLfloat whiteLight[] = {0.05f, 0.05f, 0.05f, 1.0f};
    GLfloat sourceLight[] = {0.25f, 0.25f, 0.25f, 1.0f};
    GLfloat lightPos[] = {-10.f, 5.0f, 5.0f, 1.0f};

    glEnable(GL_DEPTH_TEST);
    // Hidden surface removal
    glFrontFace(GL_CCW);
    // Counter clock-wise polygons face out
    glEnable(GL_CULL_FACE);
    // Do not calculate inside

    // Enable lighting
    glEnable(GL_LIGHTING);

    // Setup and enable light 0
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, sourceLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glEnable(GL_LIGHT0);

    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);

    // Set Material properties to follow glColor values
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glClearColor(0.25f, 0.25f, 0.50f, 1.0f);
}

void SpecialKeys(int key, int x, int y)

{
    if (key == GLUT_KEY_UP)
        xRot -= 5.0f;

    if (key == GLUT_KEY_DOWN)
        xRot += 5.0f;

    if (key == GLUT_KEY_LEFT)
        yRot -= 5.0f;

    if (key == GLUT_KEY_RIGHT)
        yRot += 5.0f;

    xRot = (GLfloat)((const int)xRot % 360);
    yRot = (GLfloat)((const int)yRot % 360);

    glutPostRedisplay();
}

// Function to draw a cube
void drawCube(float size)
{
    glutSolidCube(size);
}

void DrawLimb(float originX, float originY)
{
    // Upper
    glPushMatrix();
    glTranslatef(originX, originY, 0.0);
    drawCube(0.2);
    glTranslatef(0.0, -0.2, 0.0);
    drawCube(0.2);
    // Lower
    glTranslatef(0.0, -0.22, 0.0);
    drawCube(0.2);
    glTranslatef(0.0, -0.2, 0.0);
    drawCube(0.2);
    glPopMatrix();
}

// Function to draw the robot
void drawRobot()
{

    GLUquadricObj *pObj;

    pObj = gluNewQuadric();
    gluQuadricNormals(pObj, GLU_SMOOTH);

    // Head
    glPushMatrix();
    glTranslatef(0.0, 1.75, 0.0);
    drawCube(0.4);

    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.1f, 0.13f, 0.25f);
    gluSphere(pObj, 0.02f, 26, 13);
    glTranslatef(-0.2f, 0.0f, 0.0f);
    gluSphere(pObj, 0.02f, 26, 13);

    glPopMatrix();

    // Body
    glColor3f(0.8f, 0.8f, 0.8f);
    glPushMatrix();
    glTranslatef(0.0, 1, 0.0);
    drawCube(1.0);
    // glRotatef(90, 1.0f, 0.0f, 0.0f);
    // gluCylinder(pObj, 0.5f, 0.5f, 1, 26, 13);
    // gluDisk(pObj, 0.17f, 0.28f, 26, 13);
    glPopMatrix();

    // Left Arm
    DrawLimb(-0.65, 1.3);

    // Right Arm
    DrawLimb(0.65, 1.3);

    // Left Leg
    DrawLimb(-0.3, 0.33);
    // Right Leg
    DrawLimb(0.3, 0.33);
}

// Called to draw scene
void RenderScene(void)
{
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Save the matrix state and do the rotations
    glPushMatrix();
    // Move object back and do in place rotation
    glTranslatef(0.0f, -1.0f, -5.0f);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    drawRobot();

    glTranslatef(0.0f, 0.0f, 0.40f);
    glPopMatrix();

    // Restore the matrix state
    glPopMatrix();

    // Buffer swap
    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Modeling with Quadrics");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();

    return 0;
}