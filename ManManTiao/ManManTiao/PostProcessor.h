//
//  PostProcessor.hpp
//  ManManTiao
//
//  Created by yujunzhen on 2018/8/24.
//  Copyright © 2018年 yujunzhen. All rights reserved.
//

#ifndef PostProcessor_h
#define PostProcessor_h

#include <stdio.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Texture2D.h"
#include "Shader.h"
#include "vmath.h"
#include "GameObject.h"
#include <vector>

class PostProcessor {
    
    
public:
    Shader PostProcessingShader;
    Texture2D texture;
    GLuint width, height;
    GLboolean confuse, chaos, shake;
    PostProcessor(Shader shader, GLuint width, GLuint height);
    void beginReder();
    void endRender();
    void render(GLfloat time);
private:
    GLuint MSFBO, FBO;
    GLuint VAO, VBO;
    void initRenderData();
};
#endif /* PostProcessor_hpp */
