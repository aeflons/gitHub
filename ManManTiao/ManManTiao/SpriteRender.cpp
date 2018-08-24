//
//  SpriteRender.cpp
//  OpenSipmleGame
//
//  Created by yujunzhen on 2018/8/16.
//  Copyright © 2018年 yujunzhen. All rights reserved.
//

#include "SpriteRender.h"
SpriteRender::SpriteRender(Shader shader)
{
    this->shader = shader;
    this->initRenderData();
}

SpriteRender::~SpriteRender()
{
    glDeleteVertexArrays(1, &this->quedVao);
}

void SpriteRender::DrawSprite(Texture2D &texture, vmath::vec2 position, vmath::vec2 size, GLfloat rotate, vmath::vec4 color)
{
    // Prepare transformations
    this->shader.use();
    vmath::mat4 model = vmath::mat4::identity();
    model *= vmath::translate(vmath::vec3(position, 0.0f));  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
    
//    model *= vmath::translate(vmath::vec3(0.5f * size[0], 0.5f * size[1], 0.0f)); // Move origin of rotation to center of quad
//    //model *= vmath::rotate(rotate, vmath::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
//    model *= vmath::translate(vmath::vec3(-0.5f * size[0], -0.5f * size[1], 0.0f)); // Move origin back
    
    model *= vmath::scale(vmath::vec3(size, 1.0f)); // Last scale
    
    this->shader.SetMatrix4("model", model);
    vmath::mat4 projection = vmath::ortho(0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 1.0f);
    //ResouceManager::GetShader("sprite").use().SetInt("image", 0);
    this->shader.SetMatrix4("projection", projection);
    // Render textured quad
    this->shader.SetVector4f("spriteColor", color);
    
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

  
    glBindVertexArray(this->quedVao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
    glBindVertexArray(0);
}

void SpriteRender::initRenderData()
{
    GLuint VAO,VBO;
//    GLfloat vertices[] = {
//        // Pos      // Tex
//        0.0f, 1.0f, 0.96f, 0.04f,
//        1.0f, 0.0f, 0.04f, 0.96f,
//        0.0f, 0.0f, 0.04f, 0.04f,
////
//        0.0f, 1.0f, 0.96f, 0.04f,
//        1.0f, 1.0f, 0.96f, 0.96f,
//        1.0f, 0.0f, 0.04f, 0.96f
//    };
    GLfloat vertices[] = {
        // Pos      // Tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.00f, 0.0f,
        0.0f, 0.0f, 0.00f, 0.00f,
        //
        0.0f, 1.0f,  0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f,1.0f, 0.0f,
    };

    glGenVertexArrays(1, &this->quedVao);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quedVao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
