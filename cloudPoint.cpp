#include <GL/glut.h>
#include <fstream>
#include <sstream>
#include <vector>

struct Vertex {
    float x, y, z;
};

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

std::vector<Vertex> vertices;

void loadOBJ(const char* filename) {
    std::ifstream file(filename);
    std::string line;
    
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;
        
        if (type == "v") {
            Vertex vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            vertices.push_back(vertex);
        }
    }
}

void SpecialKeys(unsigned char key, int x, int y)
{
    if (key == 'w')
        xRot -= 5.0f;

    if (key == 's')
        xRot += 5.0f;

    if (key == 'a')
        yRot -= 5.0f;

    if (key == 'd')
        yRot += 5.0f;

    xRot = (GLfloat)((const int)xRot % 360);
    yRot = (GLfloat)((const int)yRot % 360);

    glutPostRedisplay();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glLoadIdentity();
    
    glTranslatef(0.0f, 0.0f, -5.0f);
    
    glColor3f(1.0f, 1.0f, 1.0f);
    
    glBegin(GL_POINTS);
    for (const auto& vertex : vertices) {
        glVertex3f(vertex.x, vertex.y, vertex.z);
    }
    glEnd();
    
    glutSwapBuffers();
}

void reshape(int w, int h) {
    GLfloat fAspect;

    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);

    fAspect = (GLfloat)w / (GLfloat)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(35.0f, fAspect, 1.0, 40.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("OBJ Viewer");
    glEnable(GL_DEPTH_TEST);
    
    loadOBJ("dragon.obj");
    
    glutReshapeFunc(reshape);
    // glutKeyboardFunc(SpecialKeys);
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}
