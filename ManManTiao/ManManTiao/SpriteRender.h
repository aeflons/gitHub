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
#include "Texture2D.h"
#include "Shader.h"
#include "vmath.h"
class SpriteRender {
    
    
public:
    SpriteRender(Shader shader);
    ~SpriteRender();
    void DrawSprite(Texture2D &texture,vmath::vec2 position, vmath::vec2 size = vmath::vec2(10,10), GLfloat rotate = 0.0f, vmath::vec4 color = vmath::vec4(0.0f));
private:
    Shader shader;
    GLuint quedVao;
    void initRenderData();
    
};

#endif /* SpriteRender_hpp */
