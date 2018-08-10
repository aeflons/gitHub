//
//  main.cpp
//  OpenglMac_modelLoad
//
//  Created by yujunzhen on 2018/8/9.
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
#include "Camera.cpp"

#include <assimp/defs.h>
#include "model.h"
#include "shader.h"
#include "filesystem.h"
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(vmath::vec3(0.0f, 0.0f, 50.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
GLuint vao,vbo;
// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;
GLfloat vertices[] = {
    // Positions
    -1.5f, -0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
};
// load models
// -----------
void Init(){
    
}

void Display(){
static    Shader ourShader("1.model_loading.vert", "1.model_loading.frag");
static  Model ourModel(FileSystem::getPath("nanosuit.obj"));

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,  sizeof(vertices), vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,  3* sizeof(GLfloat),(GLvoid *)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    // input
    // -----
    
    // render
    // ------
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // don't forget to enable shader before setting uniforms
    ourShader.use();
    
    // view/projection transformations
    vmath::mat4 projection = vmath::perspective(vmath::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    vmath::mat4 view = camera.GetViewMatrix();
    ourShader.setMat4("projection", projection);
    view *= vmath::rotate(10 *sin(currentFrame), 0.0f, 6.0f, 0.0f);
    ourShader.setMat4("view", view);
    
    // render the loaded model
    vmath::mat4 model = vmath::mat4::identity();
    // translate it down so it's at the center of the scene
    model *= vmath::scale(0.2f, 0.2f, 0.2f);    // it's a bit too big for our scene, so scale it down
    ourShader.setMat4("model", model);
    ourModel.Draw(ourShader);
//    glBindVertexArray(vao);
//    glDrawArrays(GL_TRIANGLES, 0, 3);

    
    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glutSwapBuffers();
    glutPostRedisplay();

}

void mouse_callback(int button, int state, int xpos, int ypos)
{
}
void SpacialKeyBoardFunc(int key, int width, int height){
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
