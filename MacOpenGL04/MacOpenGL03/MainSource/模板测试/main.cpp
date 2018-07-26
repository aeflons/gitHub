//
//  main.cpp
//  MacOpenGL_04
//
//  Created by yujunzhen on 2018/7/24.
//  Copyright © 2018年 Alfons. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "vapp.h"
#include "vutils.h"
#include "LoadShaders.h"
#include "vmath.h"

#include <GL/glew.h>
#include <GLUT/GLUT.h>


using namespace std;
struct Vertex
{
    GLubyte color[4];
    GLfloat position[2];
};
Vertex verts[3] = {
    {{255, 0, 0, 255},{0.0f, 0.9f}},
    {{0, 255, 0, 255}, { -0.9f, -0.9f}},
    {{0, 0, 255, 255}, {0.9f, -0.9f}}
    
};

float VertsNone[3][2] = {{0.0f, 0.4f},
    { -0.4f , -0.4f},
    { 0.4f, -0.4f},
};
GLuint Program = 0;
GLuint vert;
GLuint vbo;
GLuint vertNone;
GLuint vboNone;
void init(){
    ShaderInfo shaders[] = { {GL_VERTEX_SHADER, "keypress.vert"},{ GL_FRAGMENT_SHADER, "keypress.frag"},{ GL_NONE, NULL}};
    Program = LoadShaders(shaders);
    glGenVertexArrays(1, &vert);
    glBindVertexArray(vert);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(verts),verts, GL_STATIC_DRAW);
    glVertexAttribPointer(0,4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex),BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,2,GL_FLOAT, GL_TRUE,sizeof(Vertex),BUFFER_OFFSET(sizeof(verts->color)));
    glEnableVertexAttribArray(1);
    
    glGenVertexArrays(1, &vertNone);
    glBindVertexArray(vertNone);
    glGenBuffers(1, &vboNone);
    glBindBuffer(GL_ARRAY_BUFFER, vboNone);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertsNone),VertsNone, GL_STATIC_DRAW);
    glDisableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(1);
    glUseProgram(Program);
    glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
    glClearStencil(0x0);
    
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glEnable(GL_STENCIL_TEST);
    glBindVertexArray(vertNone);
    glStencilFunc(GL_ALWAYS, 0x1, 0x1);
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    
    glBindVertexArray(vbo);
    glStencilFunc(GL_NOTEQUAL, 0x1, 0x1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    //解除绑定
    glBindVertexArray(0);
    
    glutSwapBuffers();
    glutPostRedisplay();
}












int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA);
    glutInitWindowSize(600, 600);
    glewExperimental = GL_TRUE;
    
    glutCreateWindow(argv[0]);
    
    if (glewInit()) {
        std::cout << " Unable to initialize GLEW..." << std::endl;
        return 1;
    }
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

