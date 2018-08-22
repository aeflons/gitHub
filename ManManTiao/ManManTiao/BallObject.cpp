//
//  BallObject.cpp
//  ManManTiao
//
//  Created by yujunzhen on 2018/8/22.
//  Copyright © 2018年 yujunzhen. All rights reserved.
//

#include "BallObject.h"

BallObject::BallObject() : GameObject(),Radius(12.5f / 800), Stuck(true){}

BallObject:: BallObject(vmath::vec2 pos, GLfloat radius, vmath::vec2 velocity, Texture2D sprite) : GameObject(pos, vmath::vec2(radius * 2),sprite, vmath::vec4(1.0f), velocity), Radius(radius), Stuck(true){};
vmath::vec2 BallObject::move(GLfloat dt, GLuint window_width){
    //如果没有固定到挡板上
    if (!this->Stuck) {
        this->Position += this->Velocity * dt;
        if (this->Position[0] <= 0 ) {
            this->Velocity[0] = -this->Velocity[0];
            this->Position[0] = 0.0f;
        }else if(this->Position[0] + this->Size[0] >= window_width){
            this->Velocity[0] = -this->Velocity[0];
            this->Position[0] = window_width - this->Size[0];
        }
        if (this->Position[1] <= 0 ) {
            this->Velocity[1] = -this->Velocity[1];
            this->Position[1] = 0.0f;
        }
//        if (this->Position[1] >= 1 ) {
//            this->Velocity[1] = -this->Velocity[1];
//            this->Position[1] = window_width - this->Size[1];
//        }
    }
    return this->Position;
}
void BallObject::Reset(vmath::vec2 position, vmath::vec2 velocity)
{
    this->Position = position;
    this->Velocity = velocity;
    this->Stuck = true;
}
