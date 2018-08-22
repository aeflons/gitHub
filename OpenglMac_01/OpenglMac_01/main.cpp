//
//  main.m
//  OpenglMac_01
//
//  Created by yujunzhen on 2018/7/16.
//  Copyright © 2018年 yujunzhen. All rights reserved.
//


#include <stdio.h>
#include <iostream>

#include <GL/glew.h>
#include <GLUT/GLUT.h>
#include "LoadShaders.h"

#define BUFFER_OFFSET(x)  ((const void*) (x))

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;

//void init(void)
//{
//    glGenVertexArrays(NumVAOs, VAOs);
//    glBindVertexArray(VAOs[Triangles]);
//
//    GLfloat vertices[NumVertices][2] = {
//        { -0.90, -0.90 },
//        {  0.85, -0.90 },
//        { -0.90,  0.85 },
//        {  0.90, -0.85 },
//        {  0.90,  0.90 },
//        { -0.85,  0.90 }
//    };
//
//    glGenBuffers(NumBuffers, Buffers);
//    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    ShaderInfo shaders[] = {
//        { GL_VERTEX_SHADER, "triangles.vert"},
//        { GL_FRAGMENT_SHADER, "triangles.frag"},
//        { GL_NONE, NULL }
//    };
//  GLuint  program = LoadShaders(shaders);
//    glUseProgram(program);
//
//    GLuint pos = glGetAttribLocation(program, "vPosition");
//    glVertexAttribPointer(pos, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
//    glEnableVertexAttribArray(pos);
//}

void init(){ //带颜色
    struct VertexData {
        GLubyte color[4];
        GLfloat position[4];
    };
    
        glGenVertexArrays(NumVAOs, VAOs);
        glBindVertexArray(VAOs[Triangles]);
    
//        VertexData vertices[NumVertices] = {
//            {{255,   0,   0, 255},  { -0.90, -0.90 }},
//            {{  0, 255,   0, 255},  {  0.85, -0.90 }},
//            {{  0,   0, 0, 255},  { -0.90,  0.85 }},
//            {{ 0,  10,  10, 255},  {  0.90, -0.85 }},
//            {{0, 100, 100, 255},  {  0.90,  0.90 }},
//            {{0, 0, 255, 255},  { -0.85,  0.90 }}
//        };
    GLfloat vertices[] = {
        // Pos      // Tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };
        glGenBuffers(NumBuffers, Buffers);
        glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
        ShaderInfo shaders[] = {
            {GL_VERTEX_SHADER,"sprite.vert"},
            {GL_FRAGMENT_SHADER,"sprite.frag"},
            {GL_NONE, NULL}};
    
      GLuint  program = LoadShaders(shaders);
        glUseProgram(program);
    
    
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    
        glEnableVertexAttribArray(0);
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBindVertexArray(VAOs[Triangles]);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);
//    glutSwapBuffers();
//    glutPostRedisplay();
    glFlush();
}

int main(int argc, const char * argv[])
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
    
    init();
    
    glutDisplayFunc(display);
    
    glutMainLoop();
    
}


