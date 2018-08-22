//
//  ResourceManager.cpp
//  OpenSipmleGame
//
//  Created by yujunzhen on 2018/8/16.
//  Copyright © 2018年 yujunzhen. All rights reserved.
//

#include "ResourceManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "SOIL.h"
std::map< std::string, Texture2D> ResouceManager::Texture;
std::map< std::string, Shader> ResouceManager::Shaders;

Shader ResouceManager::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name){
    
    Shaders[name] = LoadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}

Shader ResouceManager::GetShader(std::string name){
    return Shaders[name];
}
Texture2D ResouceManager::LoadTexture(const GLchar *file, GLboolean alpha, std::string name){
    Texture[name] = LoadTextureFromFile(file, alpha);
    return Texture[name];
}
Texture2D ResouceManager::GetTexture(std::string name){
    return Texture[name];
}

void ResouceManager::Clear(){
    for (auto iter : Shaders) {
        glDeleteProgram(iter.second.ID);
    }
    for (auto iter : Texture) {
        glDeleteTextures(1, &iter.second.ID);
    }
}

Shader ResouceManager::LoadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile){
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try {
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderSteam, fShaderstream;
        vShaderSteam << vertexShaderFile.rdbuf();
        fShaderstream << fragmentShaderFile.rdbuf();
        vertexShaderFile.close();
        fragmentShaderFile.close();
        vertexCode = vShaderSteam.str();
        fragmentCode = fShaderstream.str();
        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
        
    } catch (std::exception e) {
        std::cout << "error: shader: failed to read shader files" << std::endl;
    }
    const GLchar * vshadercode = vertexCode.c_str();
    const GLchar *fshadercode = fragmentCode.c_str();
    const GLchar *gshadercode = geometryCode.c_str();
    
    Shader shader;
    shader.Compile(vshadercode, fshadercode, gshadercode != nullptr ? gshadercode : nullptr);
    return shader;
}

Texture2D ResouceManager::LoadTextureFromFile(const GLchar *file, GLboolean alpha){
    Texture2D texture;
    if (alpha) {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
        
    }
    int width, height;
    unsigned char *image = SOIL_load_image(file, &width, &height, 0, alpha ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
    texture.Generate(width, height, image);
    SOIL_free_image_data(image);
    return texture;    
}
