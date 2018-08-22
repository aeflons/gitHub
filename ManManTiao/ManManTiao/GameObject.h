//
//  GameObject.hpp
//  ManManTiao
//
//  Created by yujunzhen on 2018/8/20.
//  Copyright © 2018年 yujunzhen. All rights reserved.
//

#ifndef GameObject_h
#define GameObject_h

#include <stdio.h>
#include "vmath.h"
#include <GL/glew.h>
#include "Texture2D.h"
#include "SpriteRender.h"
#include "ResourceManager.h"
class GameObject
{
public:
    vmath::vec2 Position,Size,Velocity;
    vmath::vec4 Color;
    GLfloat Rotation;
    GLboolean IsSolid;
    GLboolean Destroyed;
    Texture2D Sprite;
    GameObject() : Position(0, 0), Size(1, 1), Velocity(0.0f), Color(1.0f), Rotation(0.0f), Sprite(), IsSolid(false), Destroyed(false) {};
    GameObject(vmath::vec2 pos,vmath::vec2 size, Texture2D sprite, vmath::vec4 color = vmath::vec4(1.0f), vmath::vec2 velocity = vmath::vec2(0.0f,0.0f));
    virtual void draw(SpriteRender &renderer);
};
#endif /* GameObject_hpp */
