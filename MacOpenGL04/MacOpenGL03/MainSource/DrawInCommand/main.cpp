//
//  main.cpp
//  MacOpenGL_04
//
//  Created by yujunzhen on 2018/7/19.
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

using namespace vmath;
GLint render_model_matrix_loc;
GLint render_projection_matrix_loc;
float aspect = 1.0;

static const GLfloat vertex_positions[] =
{
    -1.0f, -1.0f, 0.0f, 1.0f,
    1.0f, -1.0f, 0.0f, 1.0f,
    -1.0f, 1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 0.0f, 1.0f,
};
// 颜色数组
static const GLfloat vertex_colors[] =
{
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f
};
//索引数组
static const GLushort vertex_indices[] =
{
    0, 1, 2
};


GLuint ebo[2];
GLuint vao[2];
GLuint vbo[2];

void init(){
    ShaderInfo shaders[] =
    {
        { GL_VERTEX_SHADER, "primitive_restart.vert" },
        { GL_FRAGMENT_SHADER, "primitive_restart.frag" },
        { GL_NONE, NULL }
    };
    
    //例程中给的ShaderInfo竟然与自己定义的不兼容，为了方便起见，这里仍然调用了例1.1的shader相关文件
    GLuint program = LoadShaders(shaders);
    glUseProgram(program);
    
    //寻找着色器中对应uniform数据的索引
    render_model_matrix_loc = glGetUniformLocation(program, "model_matrix");
    render_projection_matrix_loc = glGetUniformLocation(program, "projection_matrix");
    
    //将索引数组绑定到GL_ELEMENT_ARRAY_BUFFER
    glGenBuffers(1, ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indices), vertex_indices, GL_STATIC_DRAW);
    // 设置顶点缓存，将顶点和颜色都存放到了顶点缓存
    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions) + sizeof(vertex_colors), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex_positions), vertex_positions);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertex_positions), sizeof(vertex_colors), vertex_colors);
    GLuint vl = 0, cl = 0;
    vl = glGetAttribLocation(program,"position");
    cl = glGetAttribLocation(program, "color");
    //第一个参数0对应了顶点着色器中的layout (location = 0)参数
    glVertexAttribPointer(vl, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    //第一个参数1对应了顶点着色器中的layout (location = 1)参数
    glVertexAttribPointer(cl, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)sizeof(vertex_positions));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
void
display(void)
{
    vmath::mat4 model_matrix;
    
    //使能功能
    glEnable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //设置投影矩阵和平移矩阵，后面课程应该会有深入讲解
    //设置投影矩阵，只需执行一次
    vmath::mat4 projection_matrix(vmath::frustum(-1.0f, 1.0f, -aspect, aspect, 1.0f, 500.0f));
    glUniformMatrix4fv(render_projection_matrix_loc, 1, GL_FALSE, projection_matrix);
    
    // 为绘制设定缓存
    glBindVertexArray(vao[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
    
    // 设置平移矩阵，传递给顶点shader，并绘制图形
    model_matrix = vmath::translate(-3.0f, 0.0f, -5.0f);
    //这里第二个参数应为1，原程序给的是4，坑爹。。。下同
    glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, model_matrix);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    // DrawElements形式的设置平移矩阵，传递给顶点shader，并绘制图形
    model_matrix = vmath::translate(-1.0f, 0.0f, -5.0f);
    glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, model_matrix);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL);
    
    // DrawElementsBaseVertex形式的设置平移矩阵，传递给顶点shader，并绘制图形
    model_matrix = vmath::translate(1.0f, 0.0f, -5.0f);
    glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, model_matrix);
    glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL, 1);
    
    // DrawArraysInstanced形式的设置平移矩阵，传递给顶点shader，并绘制图形
    model_matrix = vmath::translate(3.0f, 0.0f, -5.0f);
    glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, model_matrix);
    glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, 1);
    
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
