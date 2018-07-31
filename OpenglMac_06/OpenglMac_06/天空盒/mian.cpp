//
//  nextMain.cpp
//  OpenglMac_06
//
//  Created by yujunzhen on 2018/7/27.
//  Copyright © 2018年 yujunzhen. All rights reserved.
//

#include <iostream>
#include "vgl.h"
#include "LoadShaders.h"
#include "vmath.h"
#include <GL/glew.h>
#include "vermilion.h"
#include <GLUT/GLUT.h>
#include "SOIL.h"
#include "vapp.h"
#include "vutils.h"
#include "vbm.h"
#include <time.h>
// “˝»ÎGLEWø‚ ∂®“Âæ≤Ã¨¡¥Ω”

// “˝»ÎGLFWø‚
#include <GLFW/glfw3.h>
// “˝»ÎSOILø‚
// “˝»ÎGLMø‚
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <cstdlib>
// ∞¸∫¨◊≈…´∆˜º”‘ÿø‚
#include "shader.h"
// ∞¸∫¨œ‡ª˙øÿ÷∆∏®÷˙¿‡
#include "camera.h"
// ∞¸∫¨Œ∆¿Ìº”‘ÿ¿‡
#include "texture.h"

// º¸≈Ãªÿµ˜∫Ø ˝‘≠–Õ…˘√˜
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
//  Û±Í“∆∂Øªÿµ˜∫Ø ˝‘≠–Õ…˘√˜
void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);
//  Û±Íπˆ¬÷ªÿµ˜∫Ø ˝‘≠–Õ…˘√˜
void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// ≥°æ∞÷–“∆∂Ø
void do_movement();

// ∂®“Â≥Ã–Ú≥£¡ø
const int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;

GLfloat lastX = WINDOW_WIDTH , lastY = WINDOW_HEIGHT ;
bool firstMouseMove = true;
bool keyPressedStatus[1024]; // ∞¥º¸«Èøˆº«¬º
GLfloat deltaTime = 0.0f; // µ±«∞÷°∫Õ…œ“ª÷°µƒ ±º‰≤Ó
GLfloat lastFrame = 0.0f; // …œ“ª÷° ±º‰
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

int main(int argc, char** argv)
{
    
    if (!glfwInit())    // ≥ı ºªØglfwø‚
    {
        std::cout << "Error::GLFW could not initialize GLFW!" << std::endl;
        return -1;
    }
    // ø™∆ÙOpenGL 3.3 core profile
    std::cout << "Start OpenGL core profile version 3.3" << std::endl;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    // ¥¥Ω®¥∞ø⁄
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
                                          "Demo of Skybox(wrong result)", NULL, NULL);
    if (!window)
    {
        std::cout << "Error::GLFW could not create winddow!" << std::endl;
        glfwTerminate();
        std::system("pause");
        return -1;
    }
    // ¥¥Ω®µƒ¥∞ø⁄µƒcontext÷∏∂®Œ™µ±«∞context
    glfwMakeContextCurrent(window);
    
    // ◊¢≤·¥∞ø⁄º¸≈Ã ¬º˛ªÿµ˜∫Ø ˝
    glfwSetKeyCallback(window, key_callback);
    // ◊¢≤· Û±Í ¬º˛ªÿµ˜∫Ø ˝
    glfwSetCursorPosCallback(window, mouse_move_callback);
    // ◊¢≤· Û±Íπˆ¬÷ ¬º˛ªÿµ˜∫Ø ˝
    glfwSetScrollCallback(window, mouse_scroll_callback);
    //  Û±Í≤∂ªÒ Õ£¡Ù‘⁄≥Ã–Úƒ⁄
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // ≥ı ºªØGLEW ªÒ»°OpenGL∫Ø ˝
    glewExperimental = GL_TRUE; // »√glewªÒ»°À˘”–Õÿ’π∫Ø ˝
    GLenum status = glewInit();
    if (status != GLEW_OK)
    {
        std::cout << "Error::GLEW glew version:" << glewGetString(GLEW_VERSION)
        << " error string:" << glewGetErrorString(status) << std::endl;
        glfwTerminate();
        std::system("pause");
        return -1;
    }
    
    // …Ë÷√ ”ø⁄≤Œ ˝
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    
    //Section1 ∂•µ„ Ù–‘ ˝æ›
    // ÷∏∂®¡¢∑ΩÃÂ∂•µ„ Ù–‘ ˝æ› ∂•µ„Œª÷√ Œ∆¿Ì
    GLfloat cubeVertices[] = {
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,    // A
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,    // B
        0.5f, 0.5f, 0.5f,1.0f, 1.0f,    // C
        0.5f, 0.5f, 0.5f,1.0f, 1.0f,    // C
        -0.5f, 0.5f, 0.5f,0.0f, 1.0f,    // D
        -0.5f, -0.5f, 0.5f,0.0f, 0.0f,    // A
        
        
        -0.5f, -0.5f, -0.5f,0.0f, 0.0f,    // E
        -0.5f, 0.5f, -0.5f,0.0, 1.0f,   // H
        0.5f, 0.5f, -0.5f,1.0f, 1.0f,    // G
        0.5f, 0.5f, -0.5f,1.0f, 1.0f,    // G
        0.5f, -0.5f, -0.5f,1.0f, 0.0f,    // F
        -0.5f, -0.5f, -0.5f,0.0f, 0.0f,    // E
        
        -0.5f, 0.5f, 0.5f,0.0f, 1.0f,    // D
        -0.5f, 0.5f, -0.5f,1.0, 1.0f,   // H
        -0.5f, -0.5f, -0.5f,1.0f, 0.0f,    // E
        -0.5f, -0.5f, -0.5f,1.0f, 0.0f,    // E
        -0.5f, -0.5f, 0.5f,0.0f, 0.0f,    // A
        -0.5f, 0.5f, 0.5f,0.0f, 1.0f,    // D
        
        0.5f, -0.5f, -0.5f,1.0f, 0.0f,    // F
        0.5f, 0.5f, -0.5f,1.0f, 1.0f,    // G
        0.5f, 0.5f, 0.5f,0.0f, 1.0f,    // C
        0.5f, 0.5f, 0.5f,0.0f, 1.0f,    // C
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,    // B
        0.5f, -0.5f, -0.5f,1.0f, 0.0f,    // F
        
        0.5f, 0.5f, -0.5f,1.0f, 1.0f,    // G
        -0.5f, 0.5f, -0.5f,0.0, 1.0f,   // H
        -0.5f, 0.5f, 0.5f,0.0f, 0.0f,    // D
        -0.5f, 0.5f, 0.5f,0.0f, 0.0f,    // D
        0.5f, 0.5f, 0.5f,1.0f, 0.0f,    // C
        0.5f, 0.5f, -0.5f,1.0f, 1.0f,    // G
        
        -0.5f, -0.5f, 0.5f,0.0f, 0.0f,    // A
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,// E
        0.5f, -0.5f, -0.5f,1.0f, 1.0f,    // F
        0.5f, -0.5f, -0.5f,1.0f, 1.0f,    // F
        0.5f, -0.5f, 0.5f,1.0f, 0.0f,    // B
        -0.5f, -0.5f, 0.5f,0.0f, 0.0f,    // A
    };
    // ÷∏∂®∞¸Œß∫–µƒ∂•µ„ Ù–‘ Œª÷√
    GLfloat skyboxVertices[] = {
        // ±≥√Ê
        -1.0f, 1.0f, -1.0f,        // A
        -1.0f, -1.0f, -1.0f,    // B
        1.0f, -1.0f, -1.0f,        // C
        1.0f, -1.0f, -1.0f,        // C
        1.0f, 1.0f, -1.0f,        // D
        -1.0f, 1.0f, -1.0f,        // A
        
        // ◊Û≤‡√Ê
        -1.0f, -1.0f, 1.0f,        // E
        -1.0f, -1.0f, -1.0f,    // B
        -1.0f, 1.0f, -1.0f,        // A
        -1.0f, 1.0f, -1.0f,        // A
        -1.0f, 1.0f, 1.0f,        // F
        -1.0f, -1.0f, 1.0f,        // E
        
        // ”“≤‡√Ê
        1.0f, -1.0f, -1.0f,        // C
        1.0f, -1.0f, 1.0f,        // G
        1.0f, 1.0f, 1.0f,        // H
        1.0f, 1.0f, 1.0f,        // H
        1.0f, 1.0f, -1.0f,        // D
        1.0f, -1.0f, -1.0f,        // C
        
        // ’˝√Ê
        -1.0f, -1.0f, 1.0f,  // E
        -1.0f, 1.0f, 1.0f,  // F
        1.0f, 1.0f, 1.0f,  // H
        1.0f, 1.0f, 1.0f,  // H
        1.0f, -1.0f, 1.0f,  // G
        -1.0f, -1.0f, 1.0f,  // E
        
        // ∂•√Ê
        -1.0f, 1.0f, -1.0f,  // A
        1.0f, 1.0f, -1.0f,  // D
        1.0f, 1.0f, 1.0f,  // H
        1.0f, 1.0f, 1.0f,  // H
        -1.0f, 1.0f, 1.0f,  // F
        -1.0f, 1.0f, -1.0f,  // A
        
        // µ◊√Ê
        -1.0f, -1.0f, -1.0f,  // B
        -1.0f, -1.0f, 1.0f,   // E
        1.0f, -1.0f, 1.0f,    // G
        1.0f, -1.0f, 1.0f,    // G
        1.0f, -1.0f, -1.0f,   // C
        -1.0f, -1.0f, -1.0f,  // B
    };
    
    
    // Section2 ◊º±∏ª∫¥Ê∂‘œÛ
    GLuint cubeVAOId, cubeVBOId;
    glGenVertexArrays(1, &cubeVAOId);
    glGenBuffers(1, &cubeVBOId);
    glBindVertexArray(cubeVAOId);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBOId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    // ∂•µ„Œª÷√ ˝æ›
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          5 * sizeof(GL_FLOAT), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // ∂•µ„Œ∆¿Ì ˝æ›
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
                          5 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    
    GLuint skyBoxVAOId, skyBoxVBOId;
    glGenVertexArrays(1, &skyBoxVAOId);
    glGenBuffers(1, &skyBoxVBOId);
    glBindVertexArray(skyBoxVAOId);
    glBindBuffer(GL_ARRAY_BUFFER, skyBoxVBOId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
    // ∂•µ„Œª÷√ ˝æ›
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          3 * sizeof(GL_FLOAT), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    
    // Section3 º”‘ÿŒ∆¿Ì
    GLuint cubeTextId = TextureHelper::load2DTexture("container.jpg");
    std::vector<const char*> faces;
    //     faces.push_back("../../resources/skyboxes/sky/sky_rt.jpg");
    //     faces.push_back("../../resources/skyboxes/sky/sky_lf.jpg");
    //     faces.push_back("../../resources/skyboxes/sky/sky_up.jpg");
    //     faces.push_back("../../resources/skyboxes/sky/sky_dn.jpg");
    //     faces.push_back("../../resources/skyboxes/sky/sky_bk.jpg");
    //     faces.push_back("../../resources/skyboxes/sky/sky_ft.jpg");
    
    faces.push_back("urbansp_rt.tga");
    faces.push_back("urbansp_lf.tga");
    faces.push_back("urbansp_up.tga");
    faces.push_back("urbansp_dn.tga");
    faces.push_back("urbansp_bk.tga");
    faces.push_back("urbansp_ft.tga");
    GLuint skyBoxTextId = TextureHelper::loadCubeMapTexture(faces);
    // Section4 ◊º±∏◊≈…´∆˜≥Ã–Ú
    Shader shader("scene.vertex", "scene.frag");
    Shader skyBoxShader("skybox.vertex", "skybox.frag");
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    // ø™ º”Œœ∑÷˜—≠ª∑
    while (!glfwWindowShouldClose(window))
    {
        GLfloat currentFrame = (GLfloat)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents(); // ¥¶¿Ì¿˝»Á Û±Í º¸≈Ãµ» ¬º˛
        do_movement(); // ∏˘æ›”√ªß≤Ÿ◊˜«Èøˆ ∏¸–¬œ‡ª˙ Ù–‘
        
        // …Ë÷√colorBuffer—’…´
        glClearColor(0.18f, 0.04f, 0.14f, 1.0f);
        // «Â≥˝colorBuffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // œ»ªÊ÷∆skyBox
        glDepthMask(GL_FALSE); // Ω˚÷π–¥»Î…Ó∂»ª∫≥Â«¯
        skyBoxShader.use();
        glm::mat4 projection = glm::perspective(camera.mouse_zoom,
                                                (GLfloat)(WINDOW_WIDTH) / WINDOW_HEIGHT, 0.1f, 100.0f); // Õ∂”∞æÿ’Û
        glm::mat4 view = glm::mat4(glm::mat3(camera.getViewMatrix())); //  ”±‰ªªæÿ’Û “∆≥˝translate≤ø∑÷
        glUniformMatrix4fv(glGetUniformLocation(skyBoxShader.programId, "projection"),
                           1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(skyBoxShader.programId, "view"),
                           1, GL_FALSE, glm::value_ptr(view));
        
        glBindVertexArray(skyBoxVAOId);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyBoxTextId); // ◊¢“‚∞Û∂®µΩCUBE_MAP
        glUniform1i(glGetUniformLocation(skyBoxShader.programId, "skybox"), 0);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        // ªÊ÷∆∆‰À˚ŒÔÃÂ
        shader.use();
        glDepthMask(GL_TRUE);
        glUniformMatrix4fv(glGetUniformLocation(shader.programId, "projection"),
                           1, GL_FALSE, glm::value_ptr(projection));
        view = camera.getViewMatrix(); //  ”±‰ªªæÿ’Û
        glUniformMatrix4fv(glGetUniformLocation(shader.programId, "view"),
                           1, GL_FALSE, glm::value_ptr(view));
        glm::mat4 model;
        glUniformMatrix4fv(glGetUniformLocation(shader.programId, "model"),
                           1, GL_FALSE, glm::value_ptr(model));
        
        glBindVertexArray(cubeVAOId);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, cubeTextId);
        glUniform1i(glGetUniformLocation(skyBoxShader.programId, "text"), 0);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        glBindVertexArray(0);
        glUseProgram(0);
        glfwSwapBuffers(window); // Ωªªªª∫¥Ê
    }
    //  Õ∑≈◊ ‘¥
    glDeleteVertexArrays(1, &cubeVAOId);
    glDeleteVertexArrays(1, &skyBoxVAOId);
    glDeleteBuffers(1, &cubeVBOId);
    glDeleteBuffers(1, &skyBoxVBOId);
    glfwTerminate();
    return 0;
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            keyPressedStatus[key] = true;
        else if (action == GLFW_RELEASE)
            keyPressedStatus[key] = false;
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE); // πÿ±’¥∞ø⁄
    }
}
void mouse_move_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouseMove) //  ◊¥Œ Û±Í“∆∂Ø
    {
        lastX = xpos;
        lastY = ypos;
        firstMouseMove = false;
    }
    
    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;
    
    lastX = xpos;
    lastY = ypos;
    
    camera.handleMouseMove(xoffset, yoffset);
}
// ”…œ‡ª˙∏®÷˙¿‡¥¶¿Ì Û±Íπˆ¬÷øÿ÷∆
void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.handleMouseScroll(yoffset);
}
// ”…œ‡ª˙∏®÷˙¿‡¥¶¿Ìº¸≈Ãøÿ÷∆
void do_movement()
{
    
    if (keyPressedStatus[GLFW_KEY_W])
        camera.handleKeyPress(FORWARD, deltaTime);
    if (keyPressedStatus[GLFW_KEY_S])
        camera.handleKeyPress(BACKWARD, deltaTime);
    if (keyPressedStatus[GLFW_KEY_A])
        camera.handleKeyPress(LEFT, deltaTime);
    if (keyPressedStatus[GLFW_KEY_D])
        camera.handleKeyPress(RIGHT, deltaTime);
}
