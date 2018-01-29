//
//  main.cpp
//  OpenGl_02
//
//  Created by yujunzhen on 2018/1/23.
//  Copyright © 2018年 yujunzhen. All rights reserved.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ogldev_math_3d.h"

#include <GLUT/GLUT.h>
GLuint VBO;
/* 渲染回调函数*/

static void RenderScenceCB(){
    glClear(GL_COLOR_BUFFER_BIT);//清空缓存器
    glEnableVertexAttribArray(0);//开启顶点属性
    glBindBuffer(GL_ARRAY_BUFFER,VBO);//绑定GL_ARRAY_BUFFER缓冲器
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);//告诉管线怎样解析buffer中的数据
    glDrawArrays(GL_POINT, 0, 1);//开始绘制图形
    glDisableClientState(0);//禁用顶点数据
    glutSwapBuffers();//交换后缓存
}
/*
 创建顶点缓冲器*/
static void CreateVertexBuffer(){
    Vector3f Vertices[1];
    Vertices[0] = Vector3f(1.0f, 0.0f, 0.0f);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(Vertices),Vertices,GL_STATIC_DRAW);
}
int main(int argc,  char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("第二个窗户");
    glutDisplayFunc(RenderScenceCB);
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        return 1;
    }
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    CreateVertexBuffer();
    glutMainLoop();
    
    
    return 0;
}

