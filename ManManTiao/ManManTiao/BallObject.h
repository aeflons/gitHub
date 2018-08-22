//
//  BallObject.h
//  ManManTiao
//
//  Created by yujunzhen on 2018/8/22.
//  Copyright © 2018年 yujunzhen. All rights reserved.
//

#ifndef BallObject_h
#define BallObject_h
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "GameObject.h"
#include <unistd.h>

#include <vector>
class BallObject : public GameObject
{
public:
    GLfloat Radius;
    GLboolean Stuck;
    BallObject();
    BallObject(vmath::vec2 pos, GLfloat raduis, vmath::vec2 velocity, Texture2D sprite);
    vmath::vec2 move(GLfloat dt, GLuint window_width);
    void Reset(vmath::vec2 position,vmath::vec2 velocity);
};
#endif /* BallObject_h */
