//
//  main.cpp
//  Opengl_Mac08_Light
//
//  Created by yujunzhen on 2018/8/2.
//  Copyright © 2018年 yujunzhen. All rights reserved.
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

GLuint vao,vbo;
GLuint lightVao,lightVbo;
GLuint program, LightPorgram;
void Init(){
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    };
    ShaderInfo shaders[] = {{GL_VERTEX_SHADER, "cube.vert"},{GL_FRAGMENT_SHADER, "cube.frag"},{GL_NONE, NULL}};
     ShaderInfo shadersLight[] = {{GL_VERTEX_SHADER, "cubeLight.vert"},{GL_FRAGMENT_SHADER, "cubeLight.frag"},{GL_NONE, NULL}};
    program = LoadShaders(shaders);
    LightPorgram = LoadShaders(shadersLight);
    glUseProgram(program);
    glUseProgram(LightPorgram);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,  sizeof(vertices), vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),(GLvoid *)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    glGenVertexArrays(1, &lightVao);
    glBindVertexArray(lightVao);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),(GLvoid *)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

}
void Display(){
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLint objectColorLoc = glGetUniformLocation(program, "objectColor");
    GLint lightColorLoc  = glGetUniformLocation(program, "lightColor");
    glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
    glUniform3f(lightColorLoc,  1.0f, 0.5f, 1.0f);

    // Create camera transformations
    vmath::mat4 view = vmath::mat4::identity();

    vmath::mat4 projection = vmath::mat4::identity();
    // Get the uniform locations
    GLint modelLoc = glGetUniformLocation(program, "model");
    GLint viewLoc  = glGetUniformLocation(program,  "view");
    GLint projLoc  = glGetUniformLocation(program,  "projection");
    // Pass the matrices to the shader
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE,view);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE,projection);

    // Draw the container (using container's vertex attributes)
    glBindVertexArray(vao);
    vmath::mat4 model = vmath::mat4::identity();
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    // Also draw the lamp object, again binding the appropriate shader

    // Get location objects for the matrices on the lamp shader (these could be different on a different shader)
//    modelLoc = glGetUniformLocation(LightPorgram, "model");
//    viewLoc  = glGetUniformLocation(LightPorgram, "view");
//    projLoc  = glGetUniformLocation(LightPorgram, "projection");
//    // Set matrices
//    glUniformMatrix4fv(viewLoc, 1, GL_FALSE,view);
//    glUniformMatrix4fv(projLoc, 1, GL_FALSE,projection);
//    model = vmath::translate(0.5f, 0.5f, 0.5f) * model;
//    model = vmath::scale(vmath::vec3(3.0f)) * model; // Make it a smaller cube
//    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model);
//    // Draw the light object (using light's vertex attributes)
//    glBindVertexArray(lightVao);
//    glDrawArrays(GL_TRIANGLES, 0, 36);
//    glBindVertexArray(0);
    glutSwapBuffers();
     glutPostRedisplay();
}

int main(int argc, char *argv[]){
    glfwInit();
    glutInit(&argc, (char**)argv);
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE | GLUT_STENCIL  );
    glutInitWindowSize(512, 512);
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
    
    Init();
    
    glutDisplayFunc(Display);
    
    glutMainLoop();
    return 0;
}
