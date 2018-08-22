//
//  GameObject.cpp
//  ManManTiao
//
//  Created by yujunzhen on 2018/8/20.
//  Copyright © 2018年 yujunzhen. All rights reserved.
//

#include "GameObject.h"
//GameObject::GameObject() : Position(0,0),Size(1,1), Velocity(0.0f), Color(1.0f),Rotation(0.0f),Sprite(),IsSoild(false), Destoryed(false) {}



GameObject::GameObject(vmath::vec2 pos,vmath::vec2 size, Texture2D sprite, vmath::vec4 color, vmath::vec2 velocity) : Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f),Sprite(sprite),IsSolid(false), Destroyed(false){
    
    
}

void GameObject::draw(SpriteRender &renderer)
{
    renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}
