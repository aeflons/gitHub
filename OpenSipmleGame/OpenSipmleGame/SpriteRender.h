//
//  SpriteRender.hpp
//  OpenSipmleGame
//
//  Created by yujunzhen on 2018/8/16.
//  Copyright © 2018年 yujunzhen. All rights reserved.
//

#ifndef SpriteRender_h
#define SpriteRender_h

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Texture2D.h"
#include "Shader.h"

class SpriteRender {
    
    
public:
    SpriteRender(Shader &shader);
    ~SpriteRender();
    void DrawSprite(Texture2D &texture,glm::vec2 position, glm::vec2 size = glm::vec2(10,10), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f));
private:
    Shader shader;
    GLuint quedVao;
    void initRenderData();
    
};

#endif /* SpriteRender_hpp */
