//
//  main.cpp
//  OpenGL_Mac08_Light2
//
//  Created by 于军振 on 2018/8/5.
//  Copyright © 2018年 Alfons. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "vgl.h"
#include "LoadShaders.h"
#include "vmath.h"
#include <GL/glew.h>
#include "vermilion.h"
#include <GLUT/GLUT.h>
#include "SOIL.h"
#include <GLFW/glfw3.h>
#include <time.h>
#include <unistd.h>
using namespace std;

char *ShaderVert =
" #version 410 core \n"
" uniform mat4 matModel;\n"
" uniform mat4 matPorjectView;\n"

" uniform vec3 LightPosition;\n"
" uniform vec3 EyeDirection;\n"
" uniform float Attionuation;\n"

" \n"
" layout(location = 0) in vec4 vVertPos;\n"
" layout(location = 1) in vec4 vVertColor;\n"
" layout(location = 2) in vec3 vVertNormal;\n"
" \n"
" out vec4 color;\n"
" out vec3 Normal;\n"
" out vec4 Pos;\n"
" \n"
" out vec3 LightDir;\n"
" out vec3 HalfVector;\n"
" out float Ationuat;\n"
" \n"
" \n"
" void main()\n"
" {\n"
"     Pos = (matModel * vVertPos);\n"
"     LightDir = vec3(Pos.xyz) - LightPosition;\n"
"     float Len = length(LightDir);\n"
"     LightDir = LightDir/Len;\n"

"     HalfVector = EyeDirection - LightDir;\n"

"     Ationuat = 1/(1.0f+Attionuation*Len*Len);\n"
"     \n"

"     gl_Position = matPorjectView * Pos;\n"
"     color = vVertColor;\n"
"     mat4 matNoral =  transpose(inverse(matModel));\n"
"     Normal = normalize((matNoral * vec4(vVertNormal, 0.0)).xyz);\n"
" }\n"
" \n"
;

char *ShaderFrag =
"#version 410 core \n"
" \n"
" uniform vec4 Ambient;\n"

" uniform vec3 LightColor;\n"
" uniform float Shininess;\n"
" uniform float Strength;\n"

" in vec4 color;\n"
" in vec3 Normal;\n"
" in vec4 Pos;\n"

" in vec3 LightDir;\n"
" in vec3 HalfVector;\n"
" in float Ationuat;\n"

" out vec4 FragColor;\n"
" \n"
" void main()\n"
" {\n"
"     float diffuse = max(0.0f, -1*dot(Normal, LightDir)) *0.5;\n"
"     float specular = max(0.0f, 1*dot(Normal, HalfVector));\n"
"     if(diffuse <= 0.00001)\n"
"         specular = 0.0f;\n"
"     else\n"
"         specular = pow(specular, Shininess);\n"

"     vec4 scatteredLight = Ambient + vec4(LightColor * diffuse*Ationuat, 0.0); \n"
"     vec4 ReflectLight = vec4(LightColor*specular*Strength*Ationuat, 0.0);\n"
"     ;\n"
"     FragColor = min(color*scatteredLight+ReflectLight, vec4(1.0));\n"
"     \n"
" }\n"
" \n"
;


float Vertices[] = {
    //top
    -1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,

    //bottom
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

    //front
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f, -1.0f,  1.0f,

    //back
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

    //left
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,

    //right
    1.0f,  1.0f,  1.0f,
    1.0f, -1.0f,  1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

};

float vNormal[] = {
    //top
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,

    //bottom
    0.0f,  -1.0f,  0.0f,
    0.0f,  -1.0f,  0.0f,
    0.0f,  -1.0f,  0.0f,
    0.0f,  -1.0f,  0.0f,

    //front
    0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  1.0f,

    //back
    0.0f,  0.0f,  -1.0f,
    0.0f,  0.0f,  -1.0f,
    0.0f,  0.0f,  -1.0f,
    0.0f,  0.0f,  -1.0f,

    //left
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,

    //right
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
};


float color[] = {

    //top
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,

    //bottom
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,

    //front
    0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  1.0f,

    //back
    1.0f,  0.0f,  1.0f,
    1.0f,  0.0f,  1.0f,
    1.0f,  0.0f,  1.0f,
    1.0f,  0.0f,  1.0f,

    //left
    1.0f,  1.0f,  0.0f,
    1.0f,  1.0f,  0.0f,
    1.0f,  1.0f,  0.0f,
    1.0f,  1.0f,  0.0f,

    //right
    0.0f,  1.0f,  1.0f,
    0.0f,  1.0f,  1.0f,
    0.0f,  1.0f,  1.0f,
    0.0f,  1.0f,  1.0f,
};

GLuint Program;

GLuint verts;
GLuint vBo;
GLuint vCo;
GLuint vNo;

GLuint CreateShader(GLenum Type, const char* sorce)
{
    GLuint shader;
    shader = glCreateShader(Type);

    glShaderSource(shader, 1, &sorce, NULL);
    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (0 == status)
    {
        char log[1000] = { 0 };
        GLint len = 0;
        glGetShaderInfoLog(shader, sizeof(log), &len, log);
        cout << Type << ": " << log << endl;
        return -1;
    }
    return shader;
}

GLuint ULocModel;
GLuint ULocPorjView;

void init()
{
    Program = glCreateProgram();

    GLuint Shaders;
    Shaders = CreateShader(GL_VERTEX_SHADER, ShaderVert);
    glAttachShader(Program, Shaders);
    glDeleteShader(Shaders);
    Shaders = CreateShader(GL_FRAGMENT_SHADER, ShaderFrag);
    glAttachShader(Program, Shaders);
    glDeleteShader(Shaders);
    glLinkProgram(Program);

    glGenVertexArrays(1, &verts);
    glBindVertexArray(verts);
    glGenBuffers(1, &vBo);
    glBindBuffer(GL_ARRAY_BUFFER, vBo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);
    glGenBuffers(1, &vCo);
    glBindBuffer(GL_ARRAY_BUFFER, vCo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(1);
    glGenBuffers(1, &vNo);
    glBindBuffer(GL_ARRAY_BUFFER, vNo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vNormal), vNormal, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(2);


    ULocModel = glGetUniformLocation(Program, "matModel");
    ULocPorjView = glGetUniformLocation(Program, "matPorjectView");



    glClearColor(0.1f, 0.2f, 0.1f, 1.0f);

}
int GetTickCount(){
    return (int)glfwGetTime();
}
void display()
{
    static unsigned int Time = GetTickCount();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    vmath::mat4 modle = vmath::mat4::identity();
    vmath::mat4 ProjView = vmath::mat4::identity();

    modle *= vmath::scale(0.2f, 0.2f, 0.2f);

    unsigned int timeNow = GetTickCount();
    float dt = float((timeNow - Time)) / 10.0f;
    modle *= vmath::rotate(45.0f*dt, vmath::vec3(1.0f, 0.0f, 0.0f));
    modle *= vmath::rotate(45.0f*dt, vmath::vec3(0.0f, 1.0f, 0.0f));
    modle *= vmath::rotate(45.0f*dt, vmath::vec3(0.0f, 0.0f, 1.0f));

    glUseProgram(Program);
    glUniformMatrix4fv(ULocModel, 1, GL_FALSE, modle);
    glUniformMatrix4fv(ULocPorjView, 1, GL_FALSE, ProjView);

    vmath::vec4 Ambient = vmath::vec4(0.2f, 0.2f, 0.2f, 1.0f);
    glUniform4fv(glGetUniformLocation(Program, "Ambient"), 1, Ambient);

    vmath::vec3 LightColor(0.9, 0.9, 0.9);
    vmath::vec3 LightPosition(0.0, 2.0, 0.0);
    glUniform3fv(glGetUniformLocation(Program, "LightColor"), 1, LightColor);
    glUniform3fv(glGetUniformLocation(Program, "LightPosition"), 1, LightPosition);
    glUniform1f(glGetUniformLocation(Program, "Shininess"), 2.0f);
    glUniform1f(glGetUniformLocation(Program, "Strength"), 0.9f);

    vmath::vec3 Eye(0.5f, 1.5f, -1.0f);
    glUniform3fv(glGetUniformLocation(Program, "EyeDirection"), 1, Eye);
    glUniform1f(glGetUniformLocation(Program, "Attionuation"), 1.0);


    //glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    glBindVertexArray(verts);

    static const GLint First[] = {0, 4, 8, 12, 16, 20};
    static const GLsizei Count[] = { 4, 4, 4, 4, 4, 4 };
    glMultiDrawArrays(GL_TRIANGLE_STRIP, First, Count, 6);

    glutSwapBuffers();
}

void idle()
{
    static  int Time = GetTickCount();
    unsigned int timeNow = GetTickCount();

    if (timeNow - Time > 1)
    {
        Time = timeNow;
        glutPostRedisplay();
    }
}


int main(int argc, char *argv[])
{
    glfwInit();
    glutInit(&argc, (char**)argv);
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE | GLUT_STENCIL  );
    glutInitWindowSize(600, 600);
    glutCreateWindow(argv[0]);
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    glEnable(GL_DEPTH_TEST);
    if (GLEW_OK != err) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    if (GLEW_VERSION_4_1) {
        std::cout << "Yay! OpenGL 4.1 is supported!" << std::endl;
    }

    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
