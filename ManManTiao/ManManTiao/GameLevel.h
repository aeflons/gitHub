//
//  GameLevel.hpp
//  ManManTiao
//
//  Created by yujunzhen on 2018/8/20.
//  Copyright © 2018年 yujunzhen. All rights reserved.
//

#ifndef GameLevel_h
#define GameLevel_h

#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "GameObject.h"
#include <unistd.h>

#include <vector>
#include "SpriteRender.h"
class GameLevel{
public:
    std::vector<GameObject> Bricks;
    GameLevel();
    void Load(const char *file, GLuint levelWidth,GLuint levelHeight);
    void Draw(SpriteRender &render);
    GLboolean IsCompleted();
private:
    void init(std::vector<std::vector<GLuint>> tileData,GLuint levelWidth, GLuint levelHeight);
};
#endif /* GameLevel_hpp */
