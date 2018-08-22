//
//  main.cpp
//  ManManTiao
//
//  Created by yujunzhen on 2018/8/20.
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
#include "stb_image.h"
#include <GLFW/glfw3.h>
#include <time.h>
#include <unistd.h>

#include "filesystem.h"
#include "game.h"
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

// camera
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
Game Breakout(SCR_WIDTH, SCR_WIDTH);

bool firstMouse = true;
GLuint vao,vbo;
GLuint program;
// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float vertices[] = {
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f
};
void Init(){
//    ShaderInfo shaders[] = {{GL_VERTEX_SHADER,"sprite.vert"},{GL_FRAGMENT_SHADER,"sprite.frag"},{GL_NONE,NULL}};
//    program = LoadShaders(shaders);
//    glUseProgram(program);
//    glGenVertexArrays(1, &vao);
//    glBindVertexArray(vao);
//
//    glGenBuffers(1,&vbo);
//    glBindBuffer(GL_ARRAY_BUFFER,vbo);
//    glBufferData(GL_ARRAY_BUFFER,  sizeof(vertices), vertices,GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//
//    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,  4 * sizeof(float),(GLvoid *)0);
//
//    glBindVertexArray(0);
    Breakout.Init();
}
void Display(){
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    Breakout.ProcessInput(deltaTime);
    
    // Update Game state
    Breakout.Update(deltaTime);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    vmath::mat4 model = vmath::mat4::identity();
//
//    glBindVertexArray(vao);
//
//    glDrawArrays(GL_TRIANGLES, 0, 6);
//    glBindVertexArray(0);
    Breakout.Render();
   glutSwapBuffers();
    glutPostRedisplay();
    
}

void mouse_callback(int button, int state, int xpos, int ypos)
{
    
}
void SpacialKeyBoardFunc(int key, int width, int height){
    switch (key) {
        case GLUT_KEY_UP:
            
            break;
        case GLUT_KEY_DOWN:
            
            break;
        case GLUT_KEY_LEFT:
            
            break;
        case GLUT_KEY_RIGHT:
            
            break;
            
        default:
            break;
    }
}
void keyBoardUpFunc(unsigned char key, int x, int y){
    
    //Breakout.keys[key] = GL_FALSE;

}
void keyBoardFunc(unsigned char key, int x, int y){
    Breakout.keys[key] = GL_TRUE;

}
int main(int argc, char *argv[]){
    glfwInit();
    glutInit(&argc, (char**)argv);
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA  | GLUT_DOUBLE | GLUT_MULTISAMPLE | GLUT_STENCIL );
    glutInitWindowSize(SCR_WIDTH, SCR_HEIGHT);
    glutCreateWindow(argv[0]);
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    glEnable(GL_DEPTH_TEST);
    glutSpecialFunc(&SpacialKeyBoardFunc);
    glutKeyboardUpFunc(keyBoardUpFunc);
    glutKeyboardFunc(keyBoardFunc);
    glutMouseFunc(&mouse_callback);
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
