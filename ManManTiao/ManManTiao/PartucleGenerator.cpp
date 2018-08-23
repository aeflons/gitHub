//
//  PartucleGenerator.cpp
//  ManManTiao
//
//  Created by yujunzhen on 2018/8/23.
//  Copyright © 2018年 yujunzhen. All rights reserved.
//

#include "PartucleGenerator.h"
PartucleGenerator::PartucleGenerator(Shader shader, Texture2D texture, GLuint amout){
    this->shader = shader;
    this->texture =texture;
    this->amout =amout;
    this->init();
}
void PartucleGenerator::Update(GLfloat dt, GameObject &object, GLuint newPritules,vmath::vec2 offset){
    for (int i = 0 ; i < newPritules; i++) {
        int unusePartucle = this->firstUnusedParticle();
        this->respawnPartucle(this->partucles[unusePartucle], object,offset);
    }
    for (int i = 0; i < this->amout; i++) {
        Partucle &p = this->partucles[i];
        p.Life -= dt * 3;
        if (p.Life > 0.0f) {
            p.Position -= p.Velocity * dt * 3;
            p.Color[3] -= dt * 2.5;
        }
    }
}

void PartucleGenerator::Draw(){
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    this-> shader.use();
//    this->shader.SetVector2f("offset", partucle.Position);
//    this->shader.SetVector4f("color", partucle.Color);
//    Partucle partucle = this->partucles[0];
//    vmath::mat4 projection = vmath::ortho(0.0f, 1.0, 1.0, 0.0f, -1.0f, 1.0f);
//
//
//    this->shader.SetMatrix4("projection", projection);
//    vmath::mat4 model = vmath::mat4::identity();
//    model *= vmath::translate(vmath::vec3(partucle.Position, 0.0f));  // First translate
//
//    model *= vmath::scale(vmath::vec3(partucle.Size, 1.0f)); // Last scale
//
//    this->shader.SetMatrix4("model", model);
//    this->shader.SetVector2f("offset", partucle.Position);
//    this->shader.SetVector4f("color", partucle.Color);
//    this->texture.Bind();
//    glBindVertexArray(VAO);
//    glDrawArrays(GL_TRIANGLES, 0, 6);
//    glBindVertexArray(0);
    for (Partucle partucle : this->partucles) {
        if (partucle.Life > 0.0f) {
//            this->shader.SetVector2f("offset", partucle.Position);
//            this->shader.SetVector4f("color", partucle.Color);
//            this->texture.Bind();
//            glBindVertexArray(VAO);
//            glDrawArrays(GL_TRIANGLES, 0, 6);
//            glBindVertexArray(0);
            vmath::mat4 projection = vmath::ortho(0.0f, 1.0, 1.0, 0.0f, -1.0f, 1.0f);
            
            
            this->shader.SetMatrix4("projection", projection);
            vmath::mat4 model = vmath::mat4::identity();
            model *= vmath::translate(vmath::vec3(partucle.Position, 0.0f));  // First translate
            
            model *= vmath::scale(vmath::vec3(partucle.Size, 1.0f)); // Last scale
            
            this->shader.SetMatrix4("model", model);
            this->shader.SetVector2f("offset", partucle.offset);
            this->shader.SetVector4f("color", partucle.Color);
            this->texture.Bind();
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }
    }
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void PartucleGenerator::init(){
    GLuint VBO;
    GLfloat verices[] = {
        // Pos      // Tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.00f, 0.0f,
        0.0f, 0.0f, 0.00f, 0.00f,
        //
        0.0f, 1.0f,  0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f,1.0f, 0.0f, 
    };
    glGenVertexArrays(1,&this->VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(verices), verices, GL_STATIC_DRAW);
    glVertexAttribPointer(0,4, GL_FLOAT,GL_FALSE, 4 * sizeof(GLfloat), (void*)(0));
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    for (GLuint i = 0; i < this->amout; ++i)
        this->partucles.push_back(Partucle());
}
GLuint lastUserdParticle = 0;
GLuint PartucleGenerator::firstUnusedParticle(){
    for (GLuint i = 0; i < this->amout; i++) {
        if (this->partucles[i].Life <= 0.0f) {
            lastUserdParticle = i;
            return i;
        }
    }
    for (GLuint i = 0; i<lastUserdParticle; i++) {
        if (this->partucles[i].Life <= 0.0f) {
            lastUserdParticle = i;
            return i;
        }
    }
    lastUserdParticle = 0;
    
    return 0;
}
void PartucleGenerator::respawnPartucle(Partucle &partucle, GameObject &object,vmath::vec2 offset){
    GLfloat random = ((rand() % 100) - 50) / 800.0f;
    GLfloat rColor = 0.5 + ((rand() % 100) / 100.0f);
    partucle.offset = vmath::vec2(random);
    partucle.Position = object.Position;
    partucle.Color = vmath::vec4(rColor, rColor, rColor, 1.0f);
    partucle.Life = 1.0f;
    partucle.Size = object.Size;
    partucle.Velocity = object.Velocity * 0.1f;
}
