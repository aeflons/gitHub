#include <iostream>


#include "vgl.h"
#include "LoadShaders.h"
#include "vmath.h"
#include <GL/glew.h>

#include <GLUT/GLUT.h>
using namespace std;


struct Vertex
{
	GLfloat position[3];
	GLfloat TexCoord[2];
};

Vertex Verts[] = {
	{ { -0.8f,-0.8f,0.0f },{ 0.0f,0.0f } },
	{ { 0.2f,-0.8f,0.0f },{ 2.0f,0.0f } },
	{ { -0.8f,0.2f,0.0f },{ 0.0f,2.0f } },
	{ { 0.2f,0.2f,0.0f },{ 2.0f,2.0f } }, };

GLuint Program = 0;

GLuint vert;
GLuint vbo;

GLuint tex;

GLuint texFrame;
GLuint vertFrame;
GLuint vboFrame;
Vertex VertsFrame[] = {
	{ { 0.22f,0.22f,0.0f },{ 0.0f,0.0f } },
	{ { 0.8f,0.22f,0.0f },{ 2.0f,0.0f } },
	{ { 0.22f,0.8f,0.0f },{ 0.0f,2.0f } },
	{ { 0.8f,0.8f,0.0f },{ 2.0f,2.0f } }, };


GLuint Samplers[2];

void Init()
{
	ShaderInfo si[] = { { GL_VERTEX_SHADER, "setData.vert" },{ GL_FRAGMENT_SHADER, "setData.frag" },{ GL_NONE, NULL } };
	Program = LoadShaders(si);

	glGenVertexArrays(1, &vert);
	glBindVertexArray(vert);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Verts), Verts, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(sizeof(Verts->position)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	glGenVertexArrays(1, &vertFrame);
	glBindVertexArray(vertFrame);
	glGenBuffers(1, &vboFrame);
	glBindBuffer(GL_ARRAY_BUFFER, vboFrame);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertsFrame), VertsFrame, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(sizeof(Verts->position)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	float texData[] = { 1.0, 1.0, 0.0, 1.0,
		1.0, 0.0, 1.0, 1.0,
		0.0, 1.0, 1.0, 1.0,
		0.0, 1.0 ,0.0, 1.0 };
	GLuint PiexlUnpack;
	glGenBuffers(1, &PiexlUnpack);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, PiexlUnpack);
	glBufferData(GL_PIXEL_UNPACK_BUFFER, sizeof(texData), texData, GL_STATIC_DRAW);

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexStorage2D(GL_TEXTURE_2D, 2, GL_RGBA8, 2, 2);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 2, 2, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//    glGenSamplers(1, Samplers);
//    glSamplerParameteri(Samplers[0], GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glSamplerParameteri(Samplers[0], GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glSamplerParameteri(Samplers[0], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//    glSamplerParameteri(Samplers[0], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

//    glSamplerParameteri(Samplers[1], GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glSamplerParameteri(Samplers[1], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glSamplerParameteri(Samplers[1], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
//    glSamplerParameterfv(Samplers[1], GL_TEXTURE_BORDER_COLOR, vmath::Tvec4<float>(1.0, 1.0, 1.0, 1.0));
//    glSamplerParameteri(Samplers[1], GL_TEXTURE_WRAP_T, GL_REPEAT);

	glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
	glUseProgram(Program);

}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(vert);
	glBindSampler(0, Samplers[0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


//    glBindVertexArray(vertFrame);
//    glBindSampler(0, Samplers[1]);
//    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glutSwapBuffers();

	glutPostRedisplay();
}


int main(int argc, char*argv[])
{
    glutInit(&argc, (char**)argv);
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA);
    glutInitWindowSize(512, 512);
    glutCreateWindow(argv[0]);
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    
    if (GLEW_VERSION_4_1) {
        std::cout << "Yay! OpenGL 4.1 is supported!" << std::endl;
    }
    
    Init();
    
    glutDisplayFunc(Display);
	glutMainLoop();

	return 0;
}



