#include <GL/glut.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

struct Vertex
{
    float x, y, z;
};

struct VertexI
{
    int x, y, z;
};

std::vector<Vertex> vertices;
std::vector<VertexI> faces;
std::vector<Vertex> normals;

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

int count = 0;

void loadOBJ(const char *filename)
{
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "v")
        { // Vertex
            Vertex vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            vertices.push_back(vertex);
            // printf("%f %f %f\n", vertex.x, vertex.y, vertex.z);
        }
        else if (type == "f")
        { // Face
            VertexI v;
            iss >> v.x >> v.y >> v.z;
            faces.push_back(v);
        }
    }

    // // Calculate normals
    // normals.resize(vertices.size(), {0.0f, 0.0f, 0.0f});
    // for (const auto &face : faces)
    // {
    //     const Vertex &v1 = vertices[face.x - 1];
    //     const Vertex &v2 = vertices[face.y - 1];
    //     const Vertex &v3 = vertices[face.z - 1];
    //     // Calculate face normal using cross product
    //     Vertex normal = {
    //         (v2.y - v1.y) * (v3.z - v1.z) - (v2.z - v1.z) * (v3.y - v1.y),
    //         (v2.z - v1.z) * (v3.x - v1.x) - (v2.x - v1.x) * (v3.z - v1.z),
    //         (v2.x - v1.x) * (v3.y - v1.y) - (v2.y - v1.y) * (v3.x - v1.x)};
    //     // Add the face normal to each vertex's normal
    //     normals[face.x - 1].x += normal.x;
    //     normals[face.x - 1].y += normal.y;
    //     normals[face.x - 1].z += normal.z;
    //     normals[face.y - 1].x += normal.x;
    //     normals[face.y - 1].y += normal.y;
    //     normals[face.y - 1].z += normal.z;
    //     normals[face.z - 1].x += normal.x;
    //     normals[face.z - 1].y += normal.y;
    //     normals[face.z - 1].z += normal.z;
    // }
    // // Normalize the normals
    // for (auto &normal : normals)
    // {
    //     float length = std::sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
    //     if (length > 0)
    //     {
    //         normal.x /= length;
    //         normal.y /= length;
    //         normal.z /= length;
    //     }
    // }
}

void init(void)
{
    GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat position[] = {0.0, 3.0, 3.0, 0.0};

    GLfloat lmodel_ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat local_view[] = {0.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

    glFrontFace(GL_CW);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
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

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    glColor3f(1.0f, 1.0f, 1.0f);

    GLfloat mat[4];
    mat[0] = 0.0215;
    mat[1] = 0.1745;
    mat[2] = 0.0215;
    mat[3] = 1.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
    mat[0] = 0.07568;
    mat[1] = 0.61424;
    mat[2] = 0.07568;
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
    mat[0] = 0.633;
    mat[1] = 0.727811;
    mat[2] = 0.633;
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.6 * 128.0);

    glBegin(GL_TRIANGLES);
    for (const auto &face : faces)
    {
        // Calculate normal for the face
        Vertex v1 = vertices[face.x - 1];
        Vertex v2 = vertices[face.y - 1];
        Vertex v3 = vertices[face.z - 1];

        Vertex edge1 = {v2.x - v1.x, v2.y - v1.y, v2.z - v1.z};
        Vertex edge2 = {v3.x - v1.x, v3.y - v1.y, v3.z - v1.z};

        // Calculate cross product of edge vectors to get normal
        Vertex normal = {
            edge1.y * edge2.z - edge1.z * edge2.y,
            edge1.z * edge2.x - edge1.x * edge2.z,
            edge1.x * edge2.y - edge1.y * edge2.x};

        // Normalize normal
        GLfloat length = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
        normal.x /= length;
        normal.y /= length;
        normal.z /= length;

        // Set normal for lighting
        glNormal3f(normal.x, normal.y, normal.z);

        // Draw vertices of the face
        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);
        // printf("%f %f %f\n", vertex.x, vertex.y, vertex.z);
    }
    glEnd();

    // glBegin(GL_POINTS);
    // glColor3f(1.0f, 1.0f, 0.0f);
    // for (const auto &vertex : vertices)
    // {
    //     glVertex3f(vertex.x, vertex.y, vertex.z);
    // }
    // glEnd();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
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

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("OBJ Viewer");
    glEnable(GL_DEPTH_TEST);
    init();
    loadOBJ("dragon.obj");

    glutReshapeFunc(reshape);
    glutKeyboardFunc(SpecialKeys);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
