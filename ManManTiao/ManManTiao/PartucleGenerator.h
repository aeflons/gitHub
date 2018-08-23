//
//  PartucleGenerator.hpp
//  ManManTiao
//
//  Created by yujunzhen on 2018/8/23.
//  Copyright © 2018年 yujunzhen. All rights reserved.
//

#ifndef PartucleGenerator_h
#define PartucleGenerator_h

#include <stdio.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Texture2D.h"
#include "Shader.h"
#include "vmath.h"
#include "GameObject.h"
#include <vector>
struct Partucle{
    vmath::vec2 Position, Velocity;
    vmath::vec2 Size,offset;
    vmath::vec4 Color;
    GLfloat Life;
    Partucle() : Position(0.0f),Velocity(0.0f), Color(1.0f), Life(0.0f){}
};
class PartucleGenerator
{
public:
    PartucleGenerator(Shader shader, Texture2D texture, GLuint amout);
    void Update (GLfloat dt, GameObject &object, GLuint newPritules, vmath::vec2 offset = vmath::vec2(0.0f,0.0f));
    void Draw();
private:
    std::vector<Partucle> partucles;
    Shader shader;
    GLuint amout;
    Texture2D texture;
    GLuint VAO;
    void init();
    GLuint firstUnusedParticle();
    void respawnPartucle(Partucle &partucle, GameObject &object, vmath::vec2 offset = vmath::vec2(0.0f,0.0f));
};
#endif /* PartucleGenerator_hpp */
