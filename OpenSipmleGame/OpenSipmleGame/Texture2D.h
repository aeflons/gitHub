//
//  Texture2D.hpp
//  OpenSipmleGame
//
//  Created by yujunzhen on 2018/8/16.
//  Copyright © 2018年 yujunzhen. All rights reserved.
//

#ifndef Texture2D_h
#define Texture2D_h

#include <stdio.h>
#include <GL/glew.h>
class Texture2D
{
public:
    GLuint ID;
    GLuint Width,Height;
    GLuint Internal_Format;
    GLuint Image_Format;
    GLuint Wrap_S;
    GLuint Wrap_T;
    GLuint Wrap_R;
    GLuint Filter_Min;
    GLuint Filter_Max;
    Texture2D();
    void Generate (GLuint width, GLuint height, unsigned char *data);
    void Bind() const;
    
};
#endif /* Texture2D_hpp */
