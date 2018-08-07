//
//  nextMain.cpp
//  Opengl_Mac_Light03
//
//  Created by yujunzhen on 2018/8/6.
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
GLuint vao,vbo;
GLuint lightVao,lightVbo;
GLuint program, LightPorgram;
const GLuint WIDTH = 800, HEIGHT = 600;
Camera camera(vmath::vec3(0.0f, 0.0f, 10.0f));
GLfloat deltaTime = 0.0f;    // Time between current frame and last frame
GLfloat lastFrame = 0.0f;      // Time of last frame
GLfloat lastX  =  WIDTH  / 2.0;
GLfloat lastY  =  HEIGHT / 2.0;
bool keys[1024];
vmath::vec3 lightPos(1.2f, 1.0f, 2.0f);

void Init(){
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    ShaderInfo shaders[] = {{GL_VERTEX_SHADER,"materuals.vert"},{GL_FRAGMENT_SHADER,"materuals.frag"},{GL_NONE,NULL}};
    ShaderInfo shadersLight[] = {{GL_VERTEX_SHADER,"lamp.vert"},{GL_FRAGMENT_SHADER,"lamp.frag"},{GL_NONE,NULL}};
    program = LoadShaders(shaders);
    LightPorgram = LoadShaders(shadersLight);
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,  sizeof(vertices), vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),(GLvoid *)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),(GLvoid *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    
    glGenVertexArrays(1, &lightVao);
    glBindVertexArray(lightVao);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),(GLvoid *)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    
}
void do_movement()
{
    
}
void Display(){
    GLfloat currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    
    // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
    do_movement();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(program);
    GLint lightPosLoc    = glGetUniformLocation(program, "light.position");
    GLint viewPosLoc     = glGetUniformLocation(program, "viewPos");
    glUniform3f(lightPosLoc,    lightPos[0], lightPos[1], lightPos[2]);
    glUniform3f(viewPosLoc,     camera.Position[0], camera.Position[1], camera.Position[2]);
    // Set lights properties
        glUniform3f(glGetUniformLocation(program, "light.ambient"),  1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(program, "light.diffuse"),  1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(program, "light.specular"), 1.0f, 1.0f, 1.0f);
        // Set material properties
        glUniform3f(glGetUniformLocation(program, "material.ambient"),   0.0f, 0.1f, 0.06f);
        glUniform3f(glGetUniformLocation(program, "material.diffuse"),  0.0f, 0.50980392f, 0.50980392f);
        glUniform3f(glGetUniformLocation(program, "material.specular"),  0.50196078f, 0.50196078f, 0.50196078f); // Specular doesn't have full effect on this object's material
        glUniform1f(glGetUniformLocation(program, "material.shininess"), 32.0f);
//    vmath::vec3 lightColor;
//    lightColor[0] = sin(glfwGetTime() * 2.0f);
//    lightColor[1] = sin(glfwGetTime() * 0.7f);
//    lightColor[2] = sin(glfwGetTime() * 1.3f);
//    lightColor[0] = sin(2.0f);
//    lightColor[1] = sin(0.7f);
//    lightColor[2] = sin(1.3f);
//    vmath::vec3 diffuseColor = lightColor * vmath::vec3(0.5f); // Decrease the influence
//    vmath::vec3 ambientColor = diffuseColor * vmath::vec3(0.2f); // Low influence
//    glUseProgram(program);
//    glUniform3f(glGetUniformLocation(program, "light.ambient"),  ambientColor[0], ambientColor[1], ambientColor[2]);
//    glUniform3f(glGetUniformLocation(program, "light.diffuse"),  diffuseColor[0], diffuseColor[1], diffuseColor[2]);
//    glUniform3f(glGetUniformLocation(program, "light.specular"), 1.0f, 1.0f, 1.0f);
//    // Set material properties
//    glUniform3f(glGetUniformLocation(program, "material.ambient"),   1.0f, 0.5f, 0.31f);
//    glUniform3f(glGetUniformLocation(program, "material.diffuse"),   1.0f, 0.8f, 0.31f);
//    glUniform3f(glGetUniformLocation(program, "material.specular"),  0.5f, 1.5f, 0.5f); // Specular doesn't have full effect on this object's material
//    glUniform1f(glGetUniformLocation(program, "material.shininess"), 32.0f);
    
    // Create camera transformations
    vmath::mat4 view = vmath::mat4::identity();
    view = camera.GetViewMatrix();
    vmath::mat4 projection = vmath::perspective(camera.Zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
    // Get the uniform locations
    GLint modelLoc = glGetUniformLocation(program, "model");
    GLint viewLoc  = glGetUniformLocation(program,  "view");
    GLint projLoc  = glGetUniformLocation(program,  "projection");
    // Pass the matrices to the shader
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, projection);
    
    // Draw the container (using container's vertex attributes)
    glBindVertexArray(vao);
    vmath::mat4 model = vmath::mat4::identity();
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    // Also draw the lamp object, again binding the appropriate shader
    
    // Get location objects for the matrices on the lamp shader (these could be different on a different shader)
    glUseProgram(LightPorgram);

    modelLoc = glGetUniformLocation(LightPorgram, "model");
    viewLoc  = glGetUniformLocation(LightPorgram, "view");
    projLoc  = glGetUniformLocation(LightPorgram, "projection");
    // Set matrices

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE,view);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE,projection);

    model = model * vmath::translate(1.5f, 0.5f, 1.0f) ;
    model = model * vmath::scale(vmath::vec3(0.2f)) ; // Make it a smaller cube

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model);
    // Draw the light object (using light's vertex attributes)
    glBindVertexArray(lightVao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glutSwapBuffers();
    glutPostRedisplay();
}

void SpacialKeyBoardFunc(int key, int width, int height){
    switch (key) {
        case GLUT_KEY_UP:
            camera.ProcessKeyboard(FORWARD, deltaTime);
            
            break;
        case GLUT_KEY_DOWN:
            camera.ProcessKeyboard(BACKWARD, deltaTime);
            
            break;
        case GLUT_KEY_LEFT:
            camera.ProcessKeyboard(LEFT, deltaTime);
            
            break;
        case GLUT_KEY_RIGHT:
            camera.ProcessKeyboard(RIGHT, deltaTime);
            
            break;
            
        default:
            break;
    }
    // Camera controls
    
}
bool firstMouse = true;
void mouse_callback(int button, int state, int xpos, int ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xpos;
    lastY = ypos;
    
    camera.ProcessMouseMovement(xoffset, yoffset);
}




int main(int argc, char *argv[]){
    glfwInit();
    glutInit(&argc, (char**)argv);
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE | GLUT_STENCIL  );
    glutInitWindowSize(WIDTH, HEIGHT);
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
