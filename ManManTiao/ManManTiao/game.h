//
//  game.hpp
//  OpenSipmleGame
//
//  Created by yujunzhen on 2018/8/15.
//  Copyright © 2018年 yujunzhen. All rights reserved.
//

#ifndef game_h
#define game_h

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ResourceManager.h"
#include "SpriteRender.h"
#include "GameLevel.h"
#include "BallObject.h"
enum GameState{
    GAME_ACTIVE,
    GAME_MENU,
    GMAE_WIN
};
const vmath::vec2 PLAYER_SIZE(0.25f, 0.05f);
// Initial velocity of the player paddle
const GLfloat PLAYER_VELOCITY(100.0f / 800);
class Game {
    
    
public:
    GameState state;
    GLboolean   keys[1024];
    GLuint      Width, Height;
    std::vector<GameLevel>levels;
    GLuint       level;
    Game(GLuint widht,GLuint height);
    ~Game();
    void Init();
    void ProcessInput(GLfloat dt);
    void Update(GLfloat dt);
    void Render();
    void DoCollisions();
};
#endif /* game_h */
