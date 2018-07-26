//
//  nextMain.cpp
//  MacOpenGL_04
//
//  Created by yujunzhen on 2018/7/20.
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
#include <unistd.h>
#define USE_PRIMITIVE_RESTART (0)
using namespace vmath;
GLint render_model_matrix_loc;
GLint render_projection_matrix_loc;
float aspect = 1.0;
GLuint ebo[2];
GLuint vao[2];
GLuint vbo[2];
//static const GLfloat cube_positions[] = {
//    -2.0f, -2.0f, -1.0f, 1.0f,
//    -1.0f, -1.0f,  1.0f, 1.0f,
//    -2.0f,  2.0f, -1.0f, 1.0f,
//    -1.0f,  1.0f,  1.0f, 1.0f,
//     2.0f, -2.0f, -1.0f, 1.0f,
//     1.0f, -1.0f,  1.0f, 1.0f,
//     2.0f,  2.0f, -1.0f, 1.0f,
//     1.0f,  1.0f,  1.0f, 1.0f
//};

static const GLfloat cube_positions[] = {
    -1.0f, -1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f,  1.0f, 1.0f,
    -1.0f,  1.0f, -1.0f, 1.0f,
    -1.0f,  1.0f,  1.0f, 1.0f,
    1.0f, -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f,  1.0f, 1.0f,
    1.0f,  1.0f, -1.0f, 1.0f,
    1.0f,  1.0f,  1.0f, 1.0f
};
static const GLfloat cube_colors[] =
{
    1.0f,  1.0f,  1.0f, 1.0f,
    1.0f,  1.0f,  0.0f, 1.0f,
    1.0f,  0.0f,  1.0f, 1.0f,
    1.0f,  0.0f,  0.0f, 1.0f,
    0.0f,  1.0f,  1.0f, 1.0f,
    0.0f,  1.0f,  0.0f, 1.0f,
    0.0f,  0.0f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f, 1.0f
};
static const GLushort cube_indices[] = {
  0, 1, 2, 3, 6, 7, 4, 5,
  0xFFFF,
  2, 6, 0, 4, 1, 5, 3, 7
};

//static const GLfloat cube_positions[] = {
//    -1.0f, -1.0f, 0.0f, 1.0f,
//    1.0f, -1.0f, 0.0f, 1.0f,
//    -1.0f, 1.0f, 0.0f, 1.0f,
//    -1.0f, -1.0f, 0.0f, 1.0f,
//};
//static const GLfloat cube_colors[] =
//{
//    1.0f, 1.0f, 1.0f, 1.0f,
//    1.0f, 1.0f, 0.0f, 1.0f,
//    1.0f, 0.0f, 1.0f, 1.0f,
//    0.0f, 1.0f, 1.0f, 1.0f
//};
//static const GLushort cube_indices[] = {
//    0, 1, 2
//};
void init(){
    ShaderInfo shaders[] =
    {
        { GL_VERTEX_SHADER, "primitive_restart.vert" },
        { GL_FRAGMENT_SHADER, "primitive_restart.frag" },
        { GL_NONE, NULL }
    };
    GLuint program = LoadShaders(shaders);
    glUseProgram(program);
    
    //寻找着色器中对应uniform数据的索引
    render_model_matrix_loc = glGetUniformLocation(program, "model_matrix");
    render_projection_matrix_loc = glGetUniformLocation(program, "projection_matrix");
    
    glGenBuffers(1,ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(cube_indices),cube_indices,GL_STATIC_DRAW);
    
    glGenVertexArrays(1,vao);
    glBindVertexArray(vao[0]);
    
    glGenBuffers(1,vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo[0]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(cube_positions) + sizeof(cube_colors),NULL, GL_STATIC_DRAW);
    
    glBufferSubData(GL_ARRAY_BUFFER,0, sizeof(cube_positions),cube_positions);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(cube_positions), sizeof(cube_colors), cube_colors);
    GLuint vl = glGetAttribLocation(program, "position");
    GLuint cl = glGetAttribLocation(program, "color");
    glVertexAttribPointer(vl, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribPointer(cl, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)sizeof(cube_positions));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}

void display(){
    //使能功能
    vmath::mat4 model_matrix;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    vmath::mat4 projection_matrix(vmath::frustum(-1.0f, 1.0f, -aspect, aspect, 1.0f, 500.0f));
    glUniformMatrix4fv(render_projection_matrix_loc, 1, GL_FALSE, projection_matrix);
    glBindVertexArray(vao[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
    model_matrix = vmath::translate(-1.0f, 0.0f, -5.0f);
    glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, model_matrix);
    //glDrawArrays(GL_TRIANGLE_STRIP, 0, 8);
    
#if USE_PRIMITIVE_RESTART
    glEnable(GL_PRIMITIVE_RESTART);
    glPrimitiveRestartIndex(0xFFFF);
    glDrawElements(GL_TRIANGLE_STRIP, 17, GL_UNSIGNED_SHORT, NULL);
#else
    glDrawElements(GL_TRIANGLE_FAN, 8, GL_UNSIGNED_SHORT, NULL);
    glDrawElements(GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_SHORT, (const char *)(9 * sizeof(GLushort)));

    
#endif
    //解除绑定
    glBindVertexArray(0);
    
    glutSwapBuffers();
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
    
}
