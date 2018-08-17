//
//  main.cpp
//  OpenSipmleGame
//
//  Created by yujunzhen on 2018/8/15.
//  Copyright © 2018年 yujunzhen. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "game.h"
#include "ResourceManager.h"
#include "LoadShaders.h"
// GLFW function declerations
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// The Width of the screen
const GLuint SCREEN_WIDTH = 800;
// The height of the screen
const GLuint SCREEN_HEIGHT = 600;

Game Breakout(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc, char *argv[]){
    
    if (!glfwInit())    // ≥ı ºªØglfwø‚
    {
        std::cout << "Error::GLFW could not initialize GLFW!" << std::endl;
        return -1;
    }
    std::cout << "Start OpenGL core profile version 3.3" << std::endl;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT,
                                          "Demo of Skybox(wrong result)", NULL, NULL);
    if (!window)
    {
        std::cout << "Error::GLFW could not create winddow!" << std::endl;
        glfwTerminate();
        std::system("pause");
        return -1;
    }
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();
    glGetError();
    glfwSetKeyCallback(window, key_callback);
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //Breakout.Init();
    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;
    
    GLuint VBO,quedVao;
    GLfloat vertices[] = {
        // Pos      // Tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };
//    Shader shader = ResouceManager::LoadShader("sprite.vert", "sprite.frag", nullptr,"sprite");
//    shader.use();
    GLuint program;
    ShaderInfo shaders[] = {{GL_VERTEX_SHADER,"sprite.vert"},{GL_FRAGMENT_SHADER,"sprite.frag"},{GL_NONE, NULL}};
    program = LoadShaders(shaders);
    glGenVertexArrays(1, &quedVao);
    glBindVertexArray(quedVao);
    glGenBuffers(1, &VBO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glUseProgram(program);

    

    while (!glfwWindowShouldClose(window))
    {
        // Calculate delta time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();
        
        //deltaTime = 0.001f;
        // Manage user input
        Breakout.ProcessInput(deltaTime);
        
        // Update Game state
        Breakout.Update(deltaTime);
        
        // Render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
       // Breakout.Render();
     
        glBindVertexArray(quedVao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
        glfwSwapBuffers(window);

        
    }
    ResouceManager::Clear();
    
    glfwTerminate();
    return 0;
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            Breakout.keys[key] = GL_TRUE;
        else if (action == GLFW_RELEASE)
            Breakout.keys[key] = GL_FALSE;
    }
}
