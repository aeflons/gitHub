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
enum GameState{
    GAME_ACTIVE,
    GAME_MENU,
    GMAE_WIN
};
class Game {
    
    
public:
    GameState state;
    GLboolean   keys[1024];
    GLuint      Width, Height;
    Game(GLuint widht,GLuint height);
    ~Game();
    void Init();
    void ProcessInput(GLfloat dt);
    void Update(GLfloat dt);
    void Render();
    
};
#endif /* game_h */
