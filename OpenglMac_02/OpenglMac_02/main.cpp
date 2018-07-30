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
    Data = {{{-0.9f, -0.9f, 0.0f, 1.0f}, { 0.9f, -0.9f, 0.0f, 1.0f}, { 0.0f, 0.9f, 0.0f, 1.0f}},{0.2f, 0.0f, 1.0f, 1.0f}};
        
    char *name[] = {"v", "color"};
    
    GLuint Index[2];
    GLint offset[2];
    glGetUniformIndices(Program,2,name,Index);
    glGetActiveUniformsiv(Program,2,Index,GL_UNIFORM_OFFSET, offset);
    if (uboSize != sizeof(Data) || offsetof(sData, v) != offset[0] || offsetof(sData, color) != offset[1]) {
        std::cout << "data not much ..." << std::endl;
        
    }
    glGenBuffers(1, &b);
    glBindBuffer(GL_UNIFORM_BUFFER, b);
    glBufferData(GL_UNIFORM_BUFFER,uboSize,&Data,GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER,ubo,b);
    
    glUseProgram(Program);
    glClearColor(1.0f, 1.0f, 1.2f, 1.0f);
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(vert);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glFlush();
    sleep(30);
}
int main(int argc, char *argv[]){
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
    
    return 0;
}
