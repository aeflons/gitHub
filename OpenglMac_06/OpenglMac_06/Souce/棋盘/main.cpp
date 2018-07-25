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
GLuint base_prog;
GLuint vao;

GLuint quad_vbo;

GLuint tex;

GLuint pro;
GLuint Vertex;

GLuint vbo;
GLuint cmdbo;
GLuint ebo;
//void init(){
//    base_prog = glCreateProgram();
//    static const char quad_shader_vs[] =
//    "#version 330 core\n"
//    "\n"
//    "layout (location = 0) in vec2 in_position;\n"
//    "layout (location = 1) in vec2 in_tex_coord;\n"
//    "\n"
//    "out vec2 tex_coord;\n"
//    "\n"
//    "void main(void)\n"
//    "{\n"
//    "    gl_Position = vec4(in_position, 0.5, 1.0);\n"
//    "    tex_coord = in_tex_coord;\n"
//    "}\n"
//    ;
//
//    static const char quad_shader_fs[] =
//    "#version 330 core\n"
//    "\n"
//    "in vec2 tex_coord;\n"
//    "\n"
//    "layout (location = 0) out vec4 color;\n"
//    "\n"
//    "uniform sampler2D tex;\n"
//    "\n"
//    "void main(void)\n"
//    "{\n"
//    "    color = texture(tex, tex_coord);\n"
//    "}\n"
//    ;
//    static const GLfloat quad_data[] =
//    {
//        -0.75f, -0.75f,
//        0.75f, -0.75f,
//        0.75f, 0.75f,
//        -0.75f, 0.75f,
//
//        0.0f, 0.0f,
//        4.0f, 0.0f,
//        4.0f, 4.0f,
//        0.0f, 4.0f
//    };
//    vglAttachShaderSource(base_prog, GL_VERTEX_SHADER, quad_shader_vs);
//    vglAttachShaderSource(base_prog, GL_FRAGMENT_SHADER, quad_shader_fs);
//    glLinkProgram(base_prog);
//    glUseProgram(base_prog);
//    glGenBuffers(1, &quad_vbo);
//    glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_data), quad_data,GL_STATIC_DRAW);
//
//    glGenVertexArrays(1, &vao);
//    glBindVertexArray(vao);
//    glVertexAttribIPointer(0, 2, GL_FLOAT, GL_FALSE, BUFFER_OFFSET(0));
//    glVertexAttribIPointer(1, 2, GL_FLOAT, GL_FALSE, BUFFER_OFFSET(8 * sizeof(float)));
//    glEnableVertexAttribArray(0);
//    glEnableVertexAttribArray(1);
//
//
//    glGenTextures(1, &tex);
//    glBindTexture(GL_TEXTURE_2D, tex);
//    glTexStorage2D(GL_TEXTURE_2D, 4, GL_RGBA8, 8, 0);
//    static const unsigned char  texture_data[] = {
//        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
//        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
//        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
//        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
//        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
//        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
//        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
//        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF
//    };
//
//    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 8, 8, GL_RED, GL_UNSIGNED_BYTE, texture_data);
//    static const GLint swizzles[] = { GL_RED, GL_RED, GL_RED, GL_ONE};
//    glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzles);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//
//    glGenerateMipmap(GL_TEXTURE_2D);
//}
//
 ShaderInfo shaders[] = {{GL_VERTEX_SHADER,"qipan.vert"},{GL_FRAGMENT_SHADER,"qipan.frag"},{GL_NONE,NULL}};
void init(){
    
    
    //ShaderInfo shaders[] = {{GL_VERTEX_SHADER,"qipan.vert"},{GL_FRAGMENT_SHADER,"qipan.frag"},{GL_NONE,NULL}};
    pro = LoadShaders(shaders);
    
    static const unsigned char  texture_data[] = {
        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF
    };
    // Section1 准备顶点数据
    // 指定顶点属性数据 顶点位置 颜色 纹理
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,0.0f, 0.0f,  // 0
        0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,1.0f, 0.0f,  // 1
        0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f,1.0f, 1.0f,  // 2
        -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f,0.0f, 1.0f   // 3
    };
    GLushort indices[] = {
        0, 1, 2,  // 第一个三角形
        0, 2, 3   // 第二个三角形
    };
    // 创建缓存对象
    glUseProgram(pro);
    // Step1: 创建并绑定VAO对象
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    // Step2: 创建并绑定VBO 对象 传送数据
    glGenBuffers(1, &quad_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Step3: 创建并绑定EBO 对象 传送数据
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // Step4: 指定解析方式  并启用顶点属性
    // 顶点位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          8 * sizeof(GL_FLOAT), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // 顶点颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                          8 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);
    // 顶点纹理坐标
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                          8 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(2);
     //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // 注意不要解除EBO绑定
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    
    
    // Section3 准备纹理对象
    // Step1 创建并绑定纹理对象
    
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    // Step2 设定wrap参数
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    // Step3 设定filter参数
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
//                    GL_LINEAR_MIPMAP_LINEAR); // 为MipMap设定filter方法
    // Step4 加载纹理
    
    
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 8, 8, GL_RED, GL_UNSIGNED_BYTE, texture_data);
    static const GLint swizzles[] = { GL_RED, GL_RED, GL_RED, GL_ONE };
    glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzles);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glGenerateMipmap(GL_TEXTURE_2D);
    // Step5 释放纹理图片资源
    glBindTexture(GL_TEXTURE_2D, 0);
    
}
void display(){
    
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // 这里填写场景绘制代码
    glBindVertexArray(vao);
    
    // 启用纹理单元 绑定纹理对象
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);
    GLuint lfe = glGetAttribLocation(shaders[0].shader, "color");
    glUniform1i(glGetUniformLocation(shaders[1].shader, "tex"), 0); // 设置纹理单元为0号
    // 使用索引绘制
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
    glBindVertexArray(0);
    
    glutSwapBuffers();
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

