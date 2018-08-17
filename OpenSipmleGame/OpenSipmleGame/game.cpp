//
//  game.cpp
//  OpenSipmleGame
//
//  Created by yujunzhen on 2018/8/15.
//  Copyright © 2018年 yujunzhen. All rights reserved.
//

#include "game.h"
SpriteRender  *Renderer;
Game::Game(GLuint width, GLuint height){
    
}
Game::~Game(){
    delete Renderer;
}
void Game:: Init(){
    ResouceManager::LoadShader("sprite.vert", "sprite.frag", nullptr, "sprite");
    // Configure shaders
//    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
//    //ResouceManager::GetShader("sprite").use().SetInt("image", 0);
//    //ResouceManager::GetShader("sprite").SetMatrix4("projection", projection);
//    // Load textures
//    ResouceManager::LoadTexture("sprite.png", GL_TRUE, "face");
    // Set render-specific controls
    Shader shader = ResouceManager::GetShader("sprite");
    Renderer = new SpriteRender(shader);
}
void Game::Update(GLfloat dt){
    
}
void Game:: ProcessInput(GLfloat dt){
    
}

void Game:: Render(){
    Texture2D texture = ResouceManager::GetTexture("face");
    Renderer->DrawSprite(texture, glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));

}
