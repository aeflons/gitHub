//
//  Shader.cpp
//  OpenSipmleGame
//
//  Created by yujunzhen on 2018/8/15.
//  Copyright © 2018年 yujunzhen. All rights reserved.
//

#include "Shader.h"
#include <iostream>
Shader &Shader::use(){
    glUseProgram(this->ID);
    return *this;
};
void Shader::Compile(const GLchar *vertexSource, const GLchar *fragmentSource, const GLchar *geometrySource){
    
    GLuint sVertex, sFragment, gShader = 0;
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSource, NULL);
    glCompileShader(sVertex);
    checkCompileErrors(sVertex, "vertex");
    
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment,1,&fragmentSource, NULL);
    glCompileShader(sFragment);
    checkCompileErrors(sFragment, "fragment");
    
    if (geometrySource != nullptr) {
//        gShader = glCreateShader(GL_GEOMETRY_SHADER);
//        glShaderSource(gShader,1,&geometrySource, NULL);
//        glCompileShader(gShader);
//        checkCompileErrors(gShader, "fragment");
    }
    this->ID = glCreateProgram();
    glAttachShader(this->ID, sVertex);
    glAttachShader(this->ID, sFragment);
    if (geometrySource != nullptr) {
        //glAttachShader(this->ID, gShader);
    }
    glLinkProgram(this->ID);
    checkCompileErrors(this->ID, "program");
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if (geometrySource != nullptr) {
       // glDeleteShader(gShader);
    }
    
};
void Shader::SetInt(const GLchar *name, GLint value,GLboolean useShader){
    if (useShader) {
        this->use();
    }
    glUniform1i(glGetUniformLocation(this->ID, name), value);
}
void Shader::SetFloat(const GLchar *name, GLfloat value,GLboolean useShader){
    if (useShader) {
        this->use();
    }
    glUniform1f(glGetUniformLocation(this->ID,name), value);
}
void Shader::SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader){
    if (useShader) {
        this->use();
    }
    glUniform2f(glGetUniformLocation(this->ID,name),x, y);
}
void Shader::SetVector2f(const GLchar *name, vmath::vec2 &value, GLboolean useShader){
    if (useShader) {
        this->use();
    }
    glUniform2f(glGetUniformLocation(this->ID,name),value[0],value[1]);
}
void Shader::SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader){
    if (useShader) {
        this->use();
    }
    glUniform3f(glGetUniformLocation(this->ID,name),x, y, z);
}
void Shader::SetVector3f(const GLchar *name, vmath::vec3 &value, GLboolean useShader){
    if (useShader) {
        this->use();
    }
    glUniform3f(glGetUniformLocation(this->ID,name),value[0], value[1], value[2]);

}

void Shader::SetVector4f(const GLchar *name, vmath::vec4 &value, GLboolean useShader){
    if (useShader) {
        this->use();
    }
    glUniform4f(glGetUniformLocation(this->ID,name),value[0], value[1], value[2], value[3]);

}
void Shader::SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader){
    if (useShader) {
        this->use();
    }
    glUniform4f(glGetUniformLocation(this->ID,name),x, y, z, w);

}
void Shader::SetMatrix4(const GLchar *name, vmath::mat4 matrix, GLboolean useShader){
    if (useShader) {
        this->use();
    }
    glUniformMatrix4fv(glGetUniformLocation(this->ID,name),1,GL_FALSE, matrix);
}
void Shader::checkCompileErrors(GLuint object, std::string type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "program")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
            << infoLog << "\n -- --------------------------------------------------- -- "
            << std::endl;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
            << infoLog << "\n -- --------------------------------------------------- -- "
            << std::endl;
        }
    }
}

