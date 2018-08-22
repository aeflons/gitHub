 //
//  game.cpp
//  OpenSipmleGame
//
//  Created [1] yujunzhen on 2018/8/15.
//  Copyright © 2018年 yujunzhen. All rights reserved.
//

#include "game.h"
#include "GameObject.h"
#include <math.h>
SpriteRender  *Renderer;
GameObject    *Player;
BallObject    *Ball;
// 初始化球的速度
const vmath::vec2 INITIAL_BALL_VELOCITY(0.05,- 0.1);
// 球的半径
const GLfloat BALL_RADIUS = 12.5f;

enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};
typedef std::tuple<GLboolean, Direction, vmath::vec2> Collision;
Game::Game(GLuint width, GLuint height){
    this->Width = width;
    this->Height = height;
}
Game::~Game(){
    delete Renderer;
    delete Player;
}
void Game:: Init(){
    ResouceManager::LoadShader("sprite.vert", "sprite.frag", nullptr, "sprite");
    // Configure shaders
    vmath::mat4 projection = vmath::ortho(0.0f, 1.0, 1.0, 0.0f, -1.0f, 1.0f);
    //ResouceManager::GetShader("sprite").use().SetInt("image", 0);
    //ResouceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // Load textures
    ResouceManager::LoadTexture("background.jpg", GL_TRUE, "background");
    ResouceManager::LoadTexture("block.jpg", GL_TRUE, "block");
    ResouceManager::LoadTexture("block_solid.jpg", GL_TRUE, "block_soild");
    ResouceManager::LoadTexture("paddle.jpg", GL_TRUE, "paddle");
    ResouceManager::LoadTexture("sprite.jpg", GL_TRUE, "face");

    // Set render-specific controls
    Shader shader = ResouceManager::GetShader("sprite");
    Renderer = new SpriteRender(shader);
    GameLevel one;
    one.Load("level1", this->Width, this->Height * 0.5);
    this->levels.push_back(one);
    this->level = 0;
    vmath::vec2 playerPos = vmath::vec2(0.5 - PLAYER_SIZE[0] / 2 , 1 - PLAYER_SIZE[1]);
    Player = new GameObject(playerPos,PLAYER_SIZE,ResouceManager::GetTexture("paddle"));
    vmath::vec2 balllPos = playerPos + vmath::vec2(PLAYER_SIZE[0] / 2 - BALL_RADIUS / 800, -BALL_RADIUS / 800 * 2);
    Ball = new BallObject(balllPos, BALL_RADIUS / 800, INITIAL_BALL_VELOCITY, ResouceManager::GetTexture("face"));
}
void Game::Update(GLfloat dt){
    Ball->move(dt, 1);
    this->DoCollisions();
}
void Game:: ProcessInput(GLfloat dt){
    if (this->state == GAME_ACTIVE)
    {
        GLfloat velocity = PLAYER_VELOCITY ;
        // 移动玩家挡板
        if (this->keys['a'])
        {
            if (Player->Position[0] >= 0)
            {
                Player->Position[0] -= velocity;
                if (Ball->Stuck)
                    Ball->Position[0] -= velocity;
            }
            this->keys['a'] = false;
        }
        if (this->keys['d'])
        {
            if (Player->Position[0] <= this->Width - Player->Size[0])
            {
                Player->Position[0] += velocity;
                if (Ball->Stuck)
                    Ball->Position[0] += velocity;
            }
            this->keys['d'] = false;

        }
        if (this->keys[' '])
            Ball->Stuck = false;
    }
}

void Game:: Render(){
   
    this->levels[this->level].Draw(*Renderer);
    Player->draw(*Renderer);
    Ball->draw(*Renderer);
    Texture2D texture = ResouceManager::GetTexture("background");
    
    Renderer->DrawSprite(texture, vmath::vec2(0, 0), vmath::vec2(1, 1), 0.0f, vmath::vec4(1.0f));
}

Direction VectorDirection(vmath::vec2 target)
{
    vmath::vec2 compass[] = {
        vmath::vec2(0.0f, 1.0f),  // 上
        vmath::vec2(1.0f, 0.0f),  // 右
        vmath::vec2(0.0f, -1.0f), // 下
        vmath::vec2(-1.0f, 0.0f)  // 左
    };
    GLfloat max = 0.0f;
    GLuint best_match = -1;
    for (GLuint i = 0; i < 4; i++)
    {
        GLfloat dot_product = vmath::dot(vmath::normalize(target), compass[i]);
        if (dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }
    return (Direction)best_match;
}
Collision CheckCollision(BallObject &one, GameObject &two) // AABB - AABB collision
{
    // x轴方向碰撞？
//    bool collisionX = one.Position[0] + one.Size[0] >= two.Position[0] &&
//    two.Position[0] + two.Size[0] >= one.Position[0];
//    // y轴方向碰撞？
//    bool collisionY = one.Position[1] + one.Size[1] >= two.Position[1] &&
//    two.Position[1] + two.Size[1] >= one.Position[1];
//    // 只有两个轴向都有碰撞时才碰撞
//    if (collisionX && collisionY) {
//        std::cout<<"ss"<< std::endl;
//    }
//    return collisionX && collisionY;
    vmath::vec2 center = vmath::vec2(one.Position + one.Size / 2);
    // 计算AABB的信息（中心、半边长）
    vmath::vec2 aabb_half_extents = vmath:: vec2(two.Size / 2);
    vmath::vec2 aabb_center = vmath::vec2(two.Position + two.Size / 2);
    // 获取两个中心的差矢量
    vmath::vec2 difference = center - aabb_center;
    vmath::vec2 clamped = vmath::clamp(difference, -aabb_half_extents, aabb_half_extents);
    // AABB_center加上clamped这样就得到了碰撞箱上距离圆最近的点closest
    vmath::vec2 closest = aabb_center + clamped;
    // 获得圆心center和最近点closest的矢量并判断是否 length <= radius
    difference = closest - center;
    if (vmath::length(difference) <= one.Radius){
        return std::make_tuple(GL_TRUE,VectorDirection(difference),difference);
    }else{
        return std::make_tuple(GL_FALSE,UP,vmath::vec2(0.0f,0.0f));
    }
}
void Game:: DoCollisions(){
    for (GameObject &box : this->levels[level].Bricks) {
        if (!box.Destroyed) {
            Collision collision = CheckCollision(*Ball, box);
            if (std::get<0>(collision)) {
                if (!box.Destroyed) {
                    box.Destroyed = GL_TRUE;
                    Direction dir = std::get<1>(collision);
                    vmath::vec2 diff_vector = std::get<2>(collision);
                    if (dir == LEFT || dir == RIGHT) {
                        Ball->Velocity[0] = -Ball->Velocity[0]; // 反转水平速度
                        // 重定位
                        GLfloat penetration = Ball->Radius - abs(diff_vector[0]);
                        if (dir == LEFT)
                            Ball->Position[0] += penetration; // 将球右移
                        else
                            Ball->Position[0] -= penetration; // 将球左移
                    }else{
                        Ball->Velocity[1] = -Ball->Velocity[1]; // 反转垂直速度
                        // 重定位
                        GLfloat penetration = Ball->Radius - abs(diff_vector[1]);
                        if (dir == UP)
                            Ball->Position[1] -= penetration; // 将球上移
                        else
                            Ball->Position[1] += penetration; // 将球下移
                    }
                }
            }
        }
    }
    Collision result = CheckCollision(*Ball, *Player);
    if (!Ball->Stuck && std::get<0>(result))
    {
        // 检查碰到了挡板的哪个位置，并根据碰到哪个位置来改变速度
        GLfloat centerBoard = Player->Position[0] + Player->Size[0] / 2;
        GLfloat distance = (Ball->Position[0] + Ball->Radius) - centerBoard;
        GLfloat percentage = distance / (Player->Size[0] / 2);
        // 依据结果移动
        GLfloat strength = 2.0f;
        vmath::vec2 oldVelocity = Ball->Velocity;
        Ball->Velocity[0] = INITIAL_BALL_VELOCITY[0] * percentage * strength;
        Ball->Velocity[1] = -Ball->Velocity[1];
        Ball->Velocity = vmath::normalize(Ball->Velocity) * vmath::length(oldVelocity);
    } 
}
