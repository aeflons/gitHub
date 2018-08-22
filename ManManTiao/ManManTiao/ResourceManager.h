//
//  ResourceManager.hpp
//  OpenSipmleGame
//
//  Created by yujunzhen on 2018/8/16.
//  Copyright © 2018年 yujunzhen. All rights reserved.
//

#ifndef ResourceManager_h
#define ResourceManager_h

#include <stdio.h>
#include <GL/glew.h>
#include <string>
#include <map>
#include "Texture2D.h"
#include "Shader.h"
class ResouceManager {
    
    
public:
    static std::map<std::string, Shader> Shaders;
    static std::map<std::string, Texture2D>Texture;
    static Shader LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile,std::string name);
    static Shader GetShader(std::string name);
    static Texture2D LoadTexture(const GLchar *file,GLboolean alpha, std::string name);
    static Texture2D GetTexture(std::string name);
    static void Clear();
private:
    ResouceManager(){};
    static Shader LoadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
    static Texture2D LoadTextureFromFile(const GLchar *file, GLboolean alpha);
};
#endif /* ResourceManager_hpp */
