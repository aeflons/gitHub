//
//  nextMian.cpp
//  OpenglMac_06
//
//  Created by yujunzhen on 2018/7/26.
//  Copyright © 2018年 yujunzhen. All rights reserved.
//

#include <stdio.h>
#include <iostream>

#include <GL/glew.h>
#include "LoadShaders.h"
#include "vgl.h"
#include "vmath.h"
#include <GLUT/GLUT.h>
using namespace std;

struct Vertex
{
    GLfloat position[3];
    GLfloat TexCoord[2];
};

Vertex Verts[] = {
    { {-0.8f,-0.8f,0.0f},{0.0f,0.0f}},
    { { 0.2f,-0.8f,0.0f },{ 1.0f,0.0f } },
    { { -0.8f,0.2f,0.0f },{ 0.0f,1.0f } },
    { { 0.2f,0.2f,0.0f },{ 1.0f,1.0f } }, };

GLuint Program = 0;

GLuint vert;
GLuint vbo;

GLuint tex;

GLuint texCopy;
GLuint vertCopy;
GLuint vboCopy;

Vertex VertsCopy[] = {
    { {0.22f,0.22f,0.0f},{0.0f,0.0f}},
    { { 0.8f,0.22f,0.0f },{ 1.0f,0.0f } },
    { { 0.22f,0.8f,0.0f },{ 0.0f,1.0f } },
    { { 0.8f,0.8f,0.0f },{ 1.0f,1.0f } }, };

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
    
    glGenVertexArrays(1, &vertCopy);
    glBindVertexArray(vertCopy);
    glGenBuffers(1, &vboCopy);
    glBindBuffer(GL_ARRAY_BUFFER, vboCopy);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertsCopy), VertsCopy, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(sizeof(Verts->position)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    
    float texData[] = {1.0, 1.0, 0.0, 1.0,
        1.0, 0.0, 1.0, 1.0,
        0.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 0.0, 1.0,
        1.0, 0.0, 1.0, 1.0,
        0.0, 1.0 ,0.0, 1.0};
    
  unsigned  char  texture_data[] = {
        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF
    };
    GLuint PiexlUnpack;
    glGenBuffers(1, &PiexlUnpack);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, PiexlUnpack);
    glBufferData(GL_PIXEL_UNPACK_BUFFER, sizeof(texData), texData, GL_STATIC_DRAW);
    
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, 2, 2);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 2, 2, GL_RGBA, GL_FLOAT, NULL);// π”√GL_PIXEL_UNPACK_BUFFER…Ë÷√Œ∆¿Ìª∫¥Ê
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
    glUseProgram(Program);
}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBindVertexArray(vert);
    glUniform1i(0, 0);//…Ë÷√Œ∆¿Ìµ•‘™0Œ™≤…—˘∆˜÷–µƒ÷µ°£
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);//ªÊ÷∆Õº–Œ
    
    static bool IsCopytoTex = true;
    if (IsCopytoTex)
    {
        IsCopytoTex = false;
        glGenTextures(1, &texCopy);
        glActiveTexture(GL_TEXTURE1);// π”√Œ∆¿Ìµ•‘™1…Ë÷√Œ∆¿Ì
        glBindTexture(GL_TEXTURE_2D, texCopy);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, 200, 200);
        glCopyTexSubImage2D(GL_TEXTURE_2D, 0,0, 0, 0, 0, 200, 200);//¥”µ±«∞÷°ª∫¥Ê÷–øΩ±¥Œ∆¿Ì ÈºÆ
        //glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 0, 0, 300, 300, 0);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
    }
    else
    {
        glBindVertexArray(vertCopy);
        glUniform1i(0, 1);// π”√øΩ±¥…˙≥…µƒŒ∆¿Ì ˝æ›°£
        
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
    glutSwapBuffers();
    
    glutPostRedisplay();

}


int main(int argc, char *argv[]){
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
