//
//  main.cpp
//  OpenglMac_09High
//
//  Created by 于军振 on 2018/8/12.
//  Copyright © 2018年 Alfons. All rights reserved.
//

#include <stdio.h>
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
#include "stb_image.h"
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
  GLuint skyVao,skyVbo;
// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float vertices[] = {
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
float skyboxVertices[] = {
    // positions
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    
    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
    
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    
    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
    
    -1.0f,  1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,
    
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f,  1.0f
};
vector<std::string> faces
{
    "right.jpg",
    "left.jpg",
    "top.jpg",
    "bottom.jpg",
    "front.jpg",
    "back.jpg"
};

// load models
// -----------
void Init(){
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,  sizeof(vertices), vertices,GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,  5* sizeof(float),(GLvoid *)0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,  5* sizeof(float),(GLvoid *)(3 * sizeof(float)));
    glBindVertexArray(0);
  
    glGenVertexArrays(1,&skyVao);
    glBindVertexArray(skyVao);
    glGenBuffers(1, &skyVbo);
    glBindBuffer(GL_ARRAY_BUFFER,skyVbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(skyboxVertices),skyboxVertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3 * sizeof(float),(GLvoid *)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}
unsigned int loadCubemap(vector<std::string> faces);
unsigned int loadTexture(char const * path);
void Display(){
    static    Shader ourShader("cube.vert", "cube.frag");
    static    Shader skyShader("sky.vert", "sky.frag");

    //static  Model ourModel(FileSystem::getPath(""));
    unsigned int cubemapTexture = loadCubemap(faces);
    unsigned int cubeTexture = loadTexture("container.jpg");
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // don't forget to enable shader before setting uniforms
    ourShader.use();
    ourShader.setInt("texture1", 0);
    skyShader.use();
    skyShader.setInt("skybox", 0);
    // view/projection transformations
    ourShader.use();
    vmath::mat4 projection = vmath::perspective(vmath::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    vmath::mat4 view = camera.GetViewMatrix();
    ourShader.setMat4("projection", projection);
    view *= vmath::rotate(0.5f, 0.0f, 1.0f, 0.0f);
    ourShader.setMat4("view", view);

    // render the loaded model
    vmath::mat4 model = vmath::mat4::identity();
    // translate it down so it's at the center of the scene
    model *= vmath::scale(0.2f, 0.2f, 0.2f);    // it's a bit too big for our scene, so scale it down
    ourShader.setMat4("model", model);
    //ourModel.Draw(ourShader);
    glBindVertexArray(vao);
    //glActiveTexture(GL_TEXTURE0);
   // glBindTexture(GL_TEXTURE_2D, cubeTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    //    glBindVertexArray(vao);
    //    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
    skyShader.use();
    view = camera.GetViewMatrix(); // remove translation from the view matrix
    //view *= vmath::rotate(currentFrame, 0.0f, 1.0f, 0.0f);
    skyShader.setMat4("view", view);
    skyShader.setMat4("projection", projection);
    // skybox cube
    glBindVertexArray(skyVao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS); // set depth function back to default


    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glutSwapBuffers();
    glutPostRedisplay();
    sleep(1);

}

void mouse_callback(int button, int state, int xpos, int ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    
    lastX = xpos;
    lastY = ypos;
    
    camera.ProcessMouseMovement(xoffset, yoffset);
    //camera.ProcessMouseScroll(yoffset);

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
unsigned int loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    
    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;
        
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }
    
    return textureID;
}
unsigned int loadCubemap(vector<std::string> faces){
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
    int width, height,nrChannels;
    for (int i = 0; i < faces.size(); i++) {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }else{
            std::cout <<"Cubemap texture failed to load at path:" << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    return texture;
}
