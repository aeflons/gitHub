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
#include "vgl.h"
#include "vmath.h"

GLuint Program;
GLuint vert;
GLuint ubo;
void init(){
    ShaderInfo shaders[] = {{GL_VERTEX_SHADER,"UniformBlock.v"},{GL_FRAGMENT_SHADER,"UniformBlock.g"},{GL_NONE,NULL}};
    Program = LoadShaders(shaders);
    
    glGenVertexArrays(1,&vert);
    glBindVertexArray(vert);
    GLuint b,n[3] = { 0, 1, 2};
    glGenBuffers(1,&b);
    glBindBuffer(GL_ARRAY_BUFFER,b);
    glBufferData(GL_ARRAY_BUFFER,sizeof(n),n,GL_STATIC_DRAW);
    
    GLint in = glGetAttribLocation(Program,"n");
    glEnableVertexAttribArray(in);
    glVertexAttribIPointer( in, 1, GL_UNSIGNED_INT, 0, BUFFER_OFFSET(0));
    
    GLint uboSize = 0;
    ubo = glGetUniformBlockIndex(Program,"Vertice");
    glGetActiveUniformBlockiv(Program,ubo,GL_UNIFORM_BLOCK_DATA_SIZE,&uboSize);
    struct sData {
        GLfloat v[3][4];
        GLfloat color[4];
    }
    Data = {{{-0.9f, -0.9f, 0.0f, 1.0f}, { 0.9f, -0.9f, 0.0f, 1.0f}, { 0.0f, 0.9f, 0.0f, 1.0f}},{0.2f, 0.7f, 1.0f, 1.0f}};
        
    char *name[] = {"v", "color"};
    
    GLuint Index[2];
    GLint offset[2];
    glGetUniformIndices(Program,2,name,Index);
    glGetActiveUniformsiv(Program,2,Index,GL_UNIFORM_OFFSET, offset);
    if (uboSize != sizeof(Data) ||) {
        <#statements#>
    }

    
    
}
