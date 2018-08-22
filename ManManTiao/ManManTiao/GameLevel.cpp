//
//  GameLevel.cpp
//  ManManTiao
//
//  Created by yujunzhen on 2018/8/20.
//  Copyright © 2018年 yujunzhen. All rights reserved.
//

#include "GameLevel.h"
#include <istream>
using namespace std;
GameLevel::GameLevel(){
   
}
void GameLevel::Load(const char *file, GLuint levelWidth,GLuint levelHeight){
    this->Bricks.clear();
    GLuint titleCode;
    GameLevel level;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<GLuint>> tileData;
    if (fstream) {
        while (std::getline(fstream,line)) {
            std::istringstream sstream(line);
            std::vector<GLuint> row;
            while (sstream >> titleCode) {
                cout<<titleCode<<endl;

                row.push_back(titleCode);
            }
            tileData.push_back(row);
        }
        if (tileData.size() > 0) {
            this->init(tileData, levelWidth, levelHeight);
        }
    }
    
}
void GameLevel::init(std::vector<std::vector<GLuint> > tileData, GLuint levelWidth, GLuint levelHeight){
    GLuint height = tileData.size();
    GLuint width = tileData[0].size();
    GLfloat  unit_width = levelWidth / width;
    GLfloat  unit_height = levelHeight / height;
    for (GLuint y = 0; y < height; y++) {
        for (GLuint x = 0 ; x < width; x++) {
         
         
                vmath::vec4 color = vmath::vec4(1.0f);
                if (tileData[y][x] == 0) {
                    color = vmath::vec4(0.0f,0.0f,0.0f,1.0f);
                    continue;

                }
                if (tileData[y][x] == 1) {
                color = vmath::vec4(0.2f,0.4f,1.0f,1.0f);
                }
                if (tileData[y][x] == 2) {
                    color = vmath::vec4(0.2f,0.6f,1.0f,1.0f);
                }
                if (tileData[y][x] == 3) {
                    color = vmath::vec4(0.0f,0.8f,1.0f,1.0f);
                }
                if (tileData[y][x] == 4) {
                    color = vmath::vec4(0.8f,0.8f,1.0f,1.0f);
                }
                if (tileData[y][x] == 5) {
                    color = vmath::vec4(1.0f,0.5f,1.0f,1.0f);
                }
                vmath::vec2 size(1.0 / width  , 1.0 / height * 0.5);
                vmath::vec2 pos(x  * 1.0f / width , y  * 1.0f / height * 0.5);
                GameObject obj(pos,size, ResouceManager::GetTexture("block"), color);
                obj.IsSolid = GL_TRUE;

                this->Bricks.push_back(obj);
            
           
        }
    }
}
void GameLevel::Draw(SpriteRender &render){
    for (GameObject &title : this->Bricks) {
        if (!title.Destroyed) {
            title.draw(render);
        }
    }
}
GLboolean GameLevel::IsCompleted(){
    for (GameObject &title : this->Bricks) {
        if (!title.Destroyed && !title.IsSolid) {
            return GL_FALSE;
        }
    }
    return GL_TRUE;
}
