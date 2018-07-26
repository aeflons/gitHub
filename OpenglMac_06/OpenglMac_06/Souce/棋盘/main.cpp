//
//  main.cpp
//  OpenglMac_06
//
//  Created by yujunzhen on 2018/7/25.
//  Copyright © 2018年 yujunzhen. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include "LoadShaders.h"
#include "vgl.h"
#include "vmath.h"
#include <GLUT/GLUT.h>
#include "SOIL.h"
#include "vapp.h"
#include "vutils.h"
#include "vbm.h"
#include "vermilion.h"

using namespace std;

float aspect;
GLuint vao;

GLuint quad_vbo;

GLuint tex;

GLuint pro;
GLuint Vertex;

GLuint vbo;
GLuint cmdbo;
GLuint ebo;


void init(){
    
    GLfloat quad_data[] =
    {
        0.75f, -0.75f,
        -0.75f, -0.75f,
        -0.75f, 0.75f,
        0.75f, 0.75f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };
    ShaderInfo shaders[] = {{GL_VERTEX_SHADER,"qipan.vert"},{GL_FRAGMENT_SHADER,"qipan.frag"},{GL_NONE,NULL}};
    pro = LoadShaders(shaders);
     glUseProgram(pro);
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &quad_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
    
    
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_data), quad_data, GL_STATIC_DRAW);
    
   
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(8 * sizeof(float)));
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
   
    
//    glGenTextures(1, &tex);
//    glActiveTexture(GL_TEXTURE1);
//    glBindTexture(GL_TEXTURE_2D, tex);
//
//     unsigned char texture_data[] =
//    {
//        0xFF, 0x00, 0xF0, 0x00, 0xFF, 0x00, 0xFF, 0x00,
//        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
//        0xFF, 0x00, 0xFF, 0x00, 0xF0, 0x00, 0xFF, 0x00,
//        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
//        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
//        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
//        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
//        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF
//    };
//
//    glTexStorage2D(GL_TEXTURE_2D, 4, GL_RGBA8, 8, 8);
//    glTexSubImage2D(GL_TEXTURE_2D,
//                    0,
//                    0, 0,
//                    8, 8,
//                    GL_RGBA, GL_UNSIGNED_BYTE,
//                    texture_data);
//
//    int n = glGetError();
//
//    static const GLint swizzles[] = { GL_RED, GL_RED, GL_RED, GL_ONE };
//    glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzles);//RGB∑÷¡ø∂º «”–∫Ï…´∑÷¡ø£¨À˘“‘Œ™∞◊…´
//
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//
//    glGenerateMipmap(GL_TEXTURE_2D);
    
}
void display(){
    
    static const vmath::vec3 X(1.0f, 0.0f, 0.0f);
    static const vmath::vec3 Y(0.0f, 1.0f, 0.0f);
    static const vmath::vec3 Z(0.0f, 0.0f, 1.0f);
    
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
//    glClearDepth(1.0f);
//
//    glUseProgram(pro);
//    glUniform1i(1, 0);
//
//    glActiveTexture(GL_TEXTURE1);
//    glBindTexture(GL_TEXTURE_2D, tex);
    
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
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
    
    init();
    
    glutDisplayFunc(display);
    
    glutMainLoop();
    return 0;
}

