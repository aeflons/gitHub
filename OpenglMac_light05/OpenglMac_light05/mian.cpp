//
//  NextMain.cpp
//  OpenglMac_light05
//
//  Created by yujunzhen on 2018/8/7.
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
#include "stb_image.h"
GLuint vao,vbo;
GLuint lightVao,lightVbo,textureMap,textureMap1;
GLuint program, LightPorgram;
const GLuint WIDTH = 800, HEIGHT = 600;
Camera camera(vmath::vec3(0.0f, 0.0f, 5.0f));
GLfloat deltaTime = 0.0f;    // Time between current frame and last frame
GLfloat lastFrame = 0.0f;      // Time of last frame
GLfloat lastX  =  WIDTH  / 2.0;
GLfloat lastY  =  HEIGHT / 2.0;
bool keys[1024];
vmath::vec3 lightPos(1.2f, 4.0f, 10.0f);
unsigned int loadTexture(const char *path);
vmath::vec3 cubePositions[] = {
    vmath::vec3( 0.0f,  0.0f,  0.0f),
    vmath::vec3( 2.0f,  5.0f, -15.0f),
    vmath::vec3(-1.5f, -2.2f, -2.5f),
    vmath::vec3(-3.8f, -2.0f, -12.3f),
    vmath::vec3( 2.4f, -0.4f, -3.5f),
    vmath::vec3(-1.7f,  3.0f, -7.5f),
    vmath::vec3( 1.3f, -2.0f, -2.5f),
    vmath::vec3( 1.5f,  2.0f, -2.5f),
    vmath::vec3( 1.5f,  0.2f, -1.5f),
    vmath::vec3(-1.3f,  1.0f, -1.5f)
};
vmath::vec3 pointLightPositions[] = {
    vmath::vec3( 0.7f,  0.2f,  2.0f),
    vmath::vec3( 2.3f, -3.3f, -4.0f),
    vmath::vec3(-4.0f,  2.0f, -12.0f),
    vmath::vec3( 1.0f,  0.0f, -3.0f)
};
void Init(){
    GLfloat vertices[] = {
        // Positions          // Normals           // Texture Coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
        
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };
    ShaderInfo shaders[] = {{GL_VERTEX_SHADER,"light.vert"},{GL_FRAGMENT_SHADER,"light.frag"},{GL_NONE,NULL}};
    ShaderInfo shadersLight[] = {{GL_VERTEX_SHADER,"lamp.vert"},{GL_FRAGMENT_SHADER,"lamp.frag"},{GL_NONE,NULL}};
    program = LoadShaders(shaders);
    LightPorgram = LoadShaders(shadersLight);
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,  sizeof(vertices), vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),(GLvoid *)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),(GLvoid *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);
    
    glGenVertexArrays(1, &lightVao);
    glBindVertexArray(lightVao);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),(GLvoid *)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    glUseProgram(program);
    
    
    glGenTextures(1, &textureMap);
    int width, height;
    unsigned char* image;
    // Diffuse map
    image = SOIL_load_image("container.png", &width, &height, 0, SOIL_LOAD_RGB);
    glBindTexture(GL_TEXTURE_2D, textureMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // Set texture units
    glUseProgram(program);
    glUniform1i(glGetUniformLocation(program, "material.diffuse"), 0);
    glGenTextures(1, &textureMap1);
    
    
    // Diffuse map
    image = SOIL_load_image("lighting_maps.png", &width, &height, 0, SOIL_LOAD_RGB);
    glBindTexture(GL_TEXTURE_2D, textureMap1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // Set texture units
    glUniform1i(glGetUniformLocation(program, "material.specular"), 1);
}
void Display(){
    GLfloat currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(program);
      glUniform3f(glGetUniformLocation(program, "viewPos"),      camera.Position[0],camera.Position[1],camera.Position[2]);
    glUniform1f(glGetUniformLocation(program, "material.shininess"), 1.0f);

    
    glUniform3f(glGetUniformLocation(program, "dirLight.direction"),  -0.2f, -1.0f, -0.3f);
    glUniform3f(glGetUniformLocation(program, "dirLight.ambient"),  0.05f, 0.05f, 0.05f);
    glUniform3f(glGetUniformLocation(program, "dirLight.diffuse"),  0.4f, 0.4f, 0.4f);
    glUniform3f(glGetUniformLocation(program, "dirLight.specular"),  0.5f, 0.5f, 0.5f);
    
 
    glUniform3f(glGetUniformLocation(program, "pointLights[0].position"),      pointLightPositions[0][0],pointLightPositions[0][1],pointLightPositions[0][2]);
    glUniform3f(glGetUniformLocation(program, "pointLights[0].ambient"),   0.05f, 0.05f, 0.05f);
    glUniform3f(glGetUniformLocation(program, "pointLights[0].diffuse"),   0.8f, 0.8f, 0.8f);
    glUniform3f(glGetUniformLocation(program, "pointLights[0].specular"),   1.0f, 1.0f, 1.0f);
    glUniform1f(glGetUniformLocation(program, "pointLights[0].constant"),   1.0f);
    glUniform1f(glGetUniformLocation(program, "pointLights[0].linear"),   0.09f);
    glUniform1f(glGetUniformLocation(program, "pointLights[0].quadratic"),   0.032f);
    
  
    
    glUniform3f(glGetUniformLocation(program, "pointLights[1].position"),      pointLightPositions[1][0],pointLightPositions[1][1],pointLightPositions[1][2]);
    glUniform3f(glGetUniformLocation(program, "pointLights[1].ambient"),   0.05f, 0.05f, 0.05f);
    glUniform3f(glGetUniformLocation(program, "pointLights[1].diffuse"),   0.8f, 0.8f, 0.8f);
    glUniform3f(glGetUniformLocation(program, "pointLights[1].specular"),   1.0f, 1.0f, 1.0f);
    glUniform1f(glGetUniformLocation(program, "pointLights[1].constant"),   1.0f);
    glUniform1f(glGetUniformLocation(program, "pointLights[1].linear"),   0.09f);
    glUniform1f(glGetUniformLocation(program, "pointLights[1].quadratic"),   0.032f);
    
    glUniform3f(glGetUniformLocation(program, "pointLights[2].position"),      pointLightPositions[2][0],pointLightPositions[2][1],pointLightPositions[2][2]);
    glUniform3f(glGetUniformLocation(program, "pointLights[2].ambient"),   0.05f, 0.05f, 0.05f);
    glUniform3f(glGetUniformLocation(program, "pointLights[2].diffuse"),   0.8f, 0.8f, 0.8f);
    glUniform3f(glGetUniformLocation(program, "pointLights[2].specular"),   1.0f, 1.0f, 1.0f);
    glUniform1f(glGetUniformLocation(program, "pointLights[2].constant"),   1.0f);
    glUniform1f(glGetUniformLocation(program, "pointLights[2].linear"),   0.09f);
    glUniform1f(glGetUniformLocation(program, "pointLights[2].quadratic"),   0.032f);
    
    glUniform3f(glGetUniformLocation(program, "pointLights[3].position"),      pointLightPositions[3][0],pointLightPositions[3][1],pointLightPositions[3][2]);
    glUniform3f(glGetUniformLocation(program, "pointLights[3].ambient"),   0.05f, 0.05f, 0.05f);
    glUniform3f(glGetUniformLocation(program, "pointLights[3].diffuse"),   0.8f, 0.8f, 0.8f);
    glUniform3f(glGetUniformLocation(program, "pointLights[3].specular"),   1.0f, 1.0f, 1.0f);
    glUniform1f(glGetUniformLocation(program, "pointLights[3].constant"),   1.0f);
    glUniform1f(glGetUniformLocation(program, "pointLights[3].linear"),   0.09f);
    glUniform1f(glGetUniformLocation(program, "pointLights[3].quadratic"),   0.032f);
    
     glUniform3f(glGetUniformLocation(program, "spotLight.position"),      camera.Position[0],camera.Position[1],camera.Position[2]);
     glUniform3f(glGetUniformLocation(program, "spotLight.direction"),      camera.Front[0],camera.Front[1],camera.Front[2]);
    glUniform3f(glGetUniformLocation(program, "spotLight.ambient"),   0.0f, 0.0f, 0.0f);
    glUniform3f(glGetUniformLocation(program, "spotLight.diffuse"),   1.0f, 1.0f, 1.0f);
    glUniform3f(glGetUniformLocation(program, "spotLight.specular"),   1.0f, 1.0f, 1.0f);
    glUniform1f(glGetUniformLocation(program, "spotLight.constant"),   1.0f);
    glUniform1f(glGetUniformLocation(program, "spotLight.linear"),   0.09f);
    glUniform1f(glGetUniformLocation(program, "spotLight.quadratic"),   0.032f);
    glUniform1f(glGetUniformLocation(program, "spotLight.cutOff"),cos(12.5 / 180 * M_PI));
    glUniform1f(glGetUniformLocation(program, "spotLight.outerCutOff"), cos(15/ 180 * M_PI));

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
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureMap);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureMap1);
    glBindVertexArray(vao);
    vmath::mat4 model = vmath::mat4::identity();
    for(unsigned int i = 0; i < 10; i++)
    {
        
        model *= vmath::translate(cubePositions[i]);
        float angle = 20.0f * i;
        model *= vmath::rotate(vmath::radians(angle), vmath::vec3(1.0f, 0.3f, 0.5f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model);
        
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
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
