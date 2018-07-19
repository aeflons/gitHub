//
//  Main.cpp
//  Open_04
//
//  Created by yujunzhen on 2018/7/9.
//  Copyright © 2018年 yujunzhen. All rights reserved.
//

#include <stdio.h>
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
#include <GLUT/GLUT.h>
//#include "ogldev_util.h"
#include <string.h>
#include "ogldev_math_3d.h"

GLuint VBO;

// 定义要读取的顶点着色器脚本和片断着色器脚本的文件名，作为文件读取路径（这样的话shader.vs和shader.fs文件要放到工程的根目录下，保证下面定义的是这两个文件的文件路径）
const char* pVSFileName = "shadervs.h";
const char* pFSFileName = "shaderfs.h";

static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    // 依然还是绘制一个三角形
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glDisableVertexAttribArray(0);
    
    glutSwapBuffers();
}


static void InitializeGlutCallbacks()
{
    glutDisplayFunc(RenderSceneCB);
}

static void CreateVertexBuffer()
{
    Vector3f Vertices[3];
    Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
    Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
    Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

// 使用shader文本编译shader对象，并绑定shader都想到着色器程序中
static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
    // 根据shader类型参数定义两个shader对象
    GLuint ShaderObj = glCreateShader(ShaderType);
    // 检查是否定义成功
    if (ShaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
        exit(0);
    }
    
    // 定义shader的代码源
    const GLchar* p[1];
    p[0] = pShaderText;
    GLint Lengths[1];
    Lengths[0]= strlen(pShaderText);
    glShaderSource(ShaderObj, 1, p, Lengths);
    glCompileShader(ShaderObj);// 编译shader对象
    
    // 检查和shader相关的错误
    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
//    if (!success) {
//        GLchar InfoLog[1024];
//        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
//        fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
//        exit(1);
//    }
    
    // 将编译好的shader对象绑定到program object程序对象上
    glAttachShader(ShaderProgram, ShaderObj);
}

// 编译着色器函数
static void CompileShaders()
{
    // 创建着色器程序
    GLuint ShaderProgram = glCreateProgram();
    // 检查是否创建成功
    if (ShaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }
    
    
    // 存储着色器文本的字符串缓冲
    string vs, fs;
    // 分别读取着色器文件中的文本到字符串缓冲区
    if (!ReadFile(pVSFileName, vs)) {
        //exit(1);
    };
    if (!ReadFile(pFSFileName, fs)) {
        //exit(1);
    };
    
    // 添加顶点着色器和片段着色器
    AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
    AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);
    
    // 链接shader着色器程序，并检查程序相关错误
    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };
    glLinkProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
    if (Success == 0) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        exit(1);
    }
    
    // 检查验证在当前的管线状态程序是否可以被执行
    glValidateProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
    }
    
    // 设置到管线声明中来使用上面成功建立的shader程序
    glUseProgram(ShaderProgram);
}

// 主函数
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tutorial 04");
    
    InitializeGlutCallbacks();
    
    // 必须在glut初始化后！
    GLenum res = glewInit();
    if (glewIsSupported("GL_VERSION_2_0"))
        printf("Ready for OpenGL 2.0\n");
    else
    {
        printf("OpenGL 2.0 not supported\n");
        exit(1);
    }
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }
    
    printf("GL version: %s\n", glGetString(GL_VERSION));
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    CreateVertexBuffer();
    
    // 编译着色器
    CompileShaders();
    
    glutMainLoop();
    
    return 0;
}
