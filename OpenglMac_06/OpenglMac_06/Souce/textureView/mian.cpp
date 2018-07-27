//
//  nextMian.cpp
//  OpenglMac_06
//
//  Created by yujunzhen on 2018/7/27.
//  Copyright © 2018年 yujunzhen. All rights reserved.
//

#include <iostream>


#include "vgl.h"
#include "LoadShaders.h"
#include "vmath.h"
#include <GL/glew.h>
#include "vermilion.h"
#include <GLUT/GLUT.h>
#include "SOIL.h"

using namespace std;


struct Vertex
{
    GLfloat position[3];
    GLfloat TexCoord[2];
};

Vertex Verts[] = {
    { { -0.9f,0.9f,0.0f },{ 0.0f,1.0f } },
    { { -0.9f,0.3f,0.0f },{ 0.0f,0.0f } },
    { { -0.3f,0.9f,0.0f },{ 1.0f,1.0f } },
    { { -0.3f,0.3f,0.0f },{ 1.0f,0.0f } },
    
    //{ { -0.3f,0.9f,0.0f },{ 0.0f,1.0f } },
    //{ { -0.3f,0.3f,0.0f },{ 0.0f,0.0f } },
    //{ { 0.3f,0.9f,0.0f },{ 1.0f,1.0f } },
    //{ { 0.3f,0.3f,0.0f },{ 1.0f,0.0f } },
    
    //{ { 0.3f,0.9f,0.0f },{ 0.0f,1.0f } },
    //{ { 0.3f,0.3f,0.0f },{ 0.0f,0.0f } },
    //{ { 0.9f,0.9f,0.0f },{ 1.0f,1.0f } },
    //{ { 0.9f,0.3f,0.0f },{ 1.0f,0.0f } },
    
    //{ { -0.9f,0.3f,0.0f },{ 0.0f,1.0f } },
    //{ { -0.9f,-0.3f,0.0f },{ 0.0f,0.0f } },
    //{ { -0.3f,0.3f,0.0f },{ 1.0f,1.0f } },
    //{ { -0.3f,-0.3f,0.0f },{ 1.0f,0.0f } },
    
    //{ { -0.3f,0.3f,0.0f },{ 0.0f,1.0f } },
    //{ { -0.3f,-0.3f,0.0f },{ 0.0f,0.0f } },
    //{ { 0.3f,0.3f,0.0f },{ 1.0f,1.0f } },
    //{ { 0.3f,-0.3f,0.0f },{ 1.0f,0.0f } },
    
    
    //{ { 0.3f,0.3f,0.0f },{ 0.0f,1.0f } },
    //{ { 0.3f,-0.3f,0.0f },{ 0.0f,0.0f } },
    //{ { 0.9f,0.3f,0.0f },{ 1.0f,1.0f } },
    //{ { 0.9f,-0.3f,0.0f },{ 1.0f,0.0f } },
    
    //{ { -0.9f,-0.3f,0.0f },{ 0.0f,1.0f } },
    //{ { -0.9f,-0.9f,0.0f },{ 0.0f,0.0f } },
    //{ { -0.3f,-0.3f,0.0f },{ 1.0f,1.0f } },
    //{ { -0.3f,-0.9f,0.0f },{ 1.0f,0.0f } },
    
    //{ { -0.3f,-0.3f,0.0f },{ 0.0f,1.0f } },
    //{ { -0.3f,-0.9f,0.0f },{ 0.0f,0.0f } },
    //{ { 0.3f,-0.3f,0.0f },{ 1.0f,1.0f } },
    //{ { 0.3f,-0.9f,0.0f },{ 1.0f,0.0f } },
    
    //{ { 0.3f,-0.3f,0.0f },{ 0.0f,1.0f } },
    //{ { 0.3f,-0.9f,0.0f },{ 0.0f,0.0f } },
    //{ { 0.9f,-0.3f,0.0f },{ 1.0f,1.0f } },
    //{ { 0.9f,-0.9f,0.0f },{ 1.0f,0.0f } },
};

GLuint Program = 0;

GLuint vert;
GLuint vbo;

GLuint tex;

GLuint texCube;
GLuint texPanel[6];

void Init()
{
    ShaderInfo si[] = { { GL_VERTEX_SHADER, "TextureView.vert" },{ GL_FRAGMENT_SHADER, "TextureView.frag" },{ GL_NONE, NULL } };
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
   
    float texData[] = { 1.0, 0.0, 0.0, 1.0,
        0.0, 1.0, 0.0, 1.0,
        0.0, 0.0, 1.0, 1.0,
        1.0, 1.0 ,0.0, 1.0 };
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexStorage2D(GL_TEXTURE_2D, 2, GL_RGBA8, 2, 2);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 2, 2, GL_RGBA, GL_FLOAT, texData);
    
    GLenum e;
    
    //glGenTextures(1, texPanel);
    //glTextureView(texPanel[0], GL_TEXTURE_2D, tex, GL_RGBA8, 0, 1, 0, 1);
    //e = glGetError();
    //glActiveTexture(GL_TEXTURE2);
    //glBindTexture(GL_TEXTURE_2D, texPanel[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
//    vglImageData image;
//    texCube = vglLoadTexture("test.dds", 0, &image);
//
//    glTexParameteri(image.target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//
//    vglUnloadImage(&image);
    
    int width, height;
    unsigned char* image1 = SOIL_load_image("wood.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image1);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image1);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
    glUseProgram(Program);

}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBindVertexArray(vert);
    
    vmath::mat4 ModelView = vmath::mat4::identity();
    
    
    //ModelView = vmath::scale(3.0f, 3.0f, 0.0f) * ModelView;
    
    for (int i = 0; i< 1; ++i)
    {
        for (int j = 0; j < 1; j++)
        {
            ModelView = vmath::translate(0.63f*i, -0.63f*j, 0.0f);
            glUniformMatrix4fv(1, 1, GL_FALSE, ModelView);
            //            glActiveTexture(GL_TEXTURE2);
            //            glBindTexture(GL_TEXTURE_2D, texPanel);
            glUniform1i(0, 0);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        }
    }
    
    glutSwapBuffers();
    
    glutPostRedisplay();
    
}



int main(int argc, char*argv[])
{
    glutInit(&argc, (char**)argv);
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA  | GLUT_DOUBLE | GLUT_MULTISAMPLE | GLUT_STENCIL);
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
