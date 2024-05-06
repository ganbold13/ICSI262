#include <GL/glut.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <SOIL/SOIL.h>
#include <SOIL.h>

struct Vertex
{
    float x, y, z;
};

struct TexCoord
{
    float u, v;
};

struct Normal
{
    float nx, ny, nz;
};

// face has 4 vertices
struct Face
{
    int vIndex[4];
    int tIndex[4];
    int nIndex[4];
};

std::vector<Vertex> vertices;
std::vector<TexCoord> texCoords;
std::vector<Normal> normals;
std::vector<Face> faces;

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
GLuint texture;

void loadTexture(GLuint* texture, char* path){
    *texture = SOIL_load_OGL_texture(path,
                                     SOIL_LOAD_AUTO,
                                     SOIL_CREATE_NEW_ID,
                                     SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA
                                    );
    if(*texture == NULL){
        printf("[Texture loader] \"%s\" failed to load!\n", path);
    }
}

void drawTexturedRect(int x, int y, int w, int h, GLuint texture){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);
    glDisable(GL_DEPTH_TEST);
    glBegin(GL_QUADS);
        glColor3f(255,255,255);
        glTexCoord2f(0,0);
        glVertex2f(x,y);
        glTexCoord2f(1,0);
        glVertex2f(x+w,y);
        glTexCoord2f(0,1);
        glVertex2f(x,y+h);
        glTexCoord2f(1,1);
        glVertex2f(x+w,y+h);
        glTexCoord2f(0,1);
        glVertex2f(x,y+h);
    glEnd();
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}


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
        {
            Vertex vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            vertices.push_back(vertex);
        }
        else if (type == "vt")
        {
            TexCoord texCoord;
            iss >> texCoord.u >> texCoord.v;
            texCoords.push_back(texCoord);
        }
        else if (type == "vn")
        {
            Normal normal;
            iss >> normal.nx >> normal.ny >> normal.nz;
            normals.push_back(normal);
        }
        else if (type == "f")
        {
            Face face;
            char slash;
            for (int i = 0; i < 4; ++i)
            {
                iss >> face.vIndex[i] >> slash >> face.tIndex[i] >> slash >> face.nIndex[i];
            }
            faces.push_back(face);
        }
    }

    file.close();
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

    glTranslatef(0.0f, -7.5f, -30.0f);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    glColor3f(1.0f, 1.0f, 1.0f);

    loadTexture(&texture ,"Texture.jpg");
    drawTexturedRect(25,25,1024,1024,texture);
    // glBindTexture(GL_TEXTURE_2D, textureID);

    glBegin(GL_QUADS);
    for (const Face &face : faces)
    {
        for (int i = 0; i < 4; ++i)
        {
            int vIndex = face.vIndex[i] - 1; // OBJ file indices start from 1
            int nIndex = face.nIndex[i] - 1;
            int tIndex = face.tIndex[i] - 1; // Texture index

            glNormal3f(normals[nIndex].nx, normals[nIndex].ny, normals[nIndex].nz);
            glTexCoord2f(texCoords[tIndex].u, texCoords[tIndex].v); // Set texture coordinates
            glVertex3f(vertices[vIndex].x, vertices[vIndex].y, vertices[vIndex].z);
        }
    }
    glEnd();

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
    loadOBJ("Character.obj");

    glutReshapeFunc(reshape);
    glutKeyboardFunc(SpecialKeys);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}