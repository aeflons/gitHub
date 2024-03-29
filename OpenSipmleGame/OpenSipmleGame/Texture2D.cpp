//
//  Texture2D.cpp
//  OpenSipmleGame
//
//  Created by yujunzhen on 2018/8/16.
//  Copyright © 2018年 yujunzhen. All rights reserved.
//

#include "Texture2D.h"
Texture2D::Texture2D():Width(0),Height(0), Internal_Format(GL_RGB),Image_Format(GL_RGB),Wrap_S(GL_REPEAT),Wrap_T(GL_REPEAT),Wrap_R(GL_REPEAT), Filter_Min(GL_LINEAR), Filter_Max(GL_LINEAR){
    glGenTextures(1, &this->ID);
}

void Texture2D::Generate(GLuint width, GLuint height, unsigned char *data){
    
    this->Width = width;
    this->Height = height;
    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, Width, Height, 0, this->Image_Format, GL_UNSIGNED_BYTE, data);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind() const{
    glBindTexture(GL_TEXTURE_2D, this->ID);
}
