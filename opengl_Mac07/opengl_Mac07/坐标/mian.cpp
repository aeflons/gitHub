//
//  nextMain.cpp
//  opengl_Mac07
//
//  Created by yujunzhen on 2018/8/1.
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
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <unistd.h>
GLuint Progrom;
GLuint vao,vbo,ebo;
GLuint texture1,texture2;
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
void Init(){
    ShaderInfo shaders[] = { {GL_VERTEX_SHADER,"cube3D.vert" },{GL_FRAGMENT_SHADER,"cube3D.frag"},{GL_NONE, NULL}};
    Progrom = LoadShaders(shaders);
    glUseProgram(Progrom);
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),(GLvoid *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),(GLvoid *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    int width,height;
    unsigned char *image = SOIL_load_image("wood.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    unsigned char *image1 = SOIL_load_image("img_cheryl.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image1);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image1);
    glBindTexture(GL_TEXTURE_2D, 0);
    
}

void Display(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    // Bind Textures using texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glUniform1i(glGetUniformLocation(Progrom,"OurTextture1"), 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glUniform1i(glGetUniformLocation(Progrom,"OurTextture2"), 1);
        glBindVertexArray(vao);

//    glm::mat4 view;
//    glm::mat4 projection;
//    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
//    projection = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);
//    GLfloat time = glfwGetTime();
    vmath::mat4 view = vmath::mat4::identity();
    vmath::mat4 projection = vmath::mat4::identity();

//
//    GLint modelLoc = glGetUniformLocation(Progrom ,"model");
    GLint viewLoc = glGetUniformLocation(Progrom, "view");
    GLint projLoc = glGetUniformLocation(Progrom, "projection");
    GLint modelLoc = glGetUniformLocation(Progrom, "model");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, projection);
//

        // Calculate the model matrix for each object and pass it to shader before drawing
        GLfloat angle = 20.0f * 2;
       GLfloat time = glfwGetTime();
        vmath::mat4 model = vmath::mat4::identity();
        vmath::vec3 rotate = cubePositions[2];
        model =  vmath::rotate(5 * sinf(time), rotate[0], rotate[1], rotate[2]) * model;
       // model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model);

        glDrawArrays(GL_TRIANGLES, 0, 36);


    glBindVertexArray(0);
    
    // Swap the screen buffers
    glutSwapBuffers();
    glutPostRedisplay();
    //sleep(30);
    
}

int main(int argc, char *argv[]){
    glfwInit();
    glutInit(&argc, (char**)argv);
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA  );
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
