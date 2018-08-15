//
//  Shader.hpp
//  OpenSipmleGame
//
//  Created by yujunzhen on 2018/8/15.
//  Copyright © 2018年 yujunzhen. All rights reserved.
//

#ifndef Shader_h
#define Shader_h

#include <stdio.h>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
class Shader {
    
    
public:
    GLuint ID;
    Shader() {};
    Shader &use();
    void Compile(const GLchar *vertexSource, const GLchar *fragmentSource, const GLchar *geometrySource = nullptr);
    void SetFloat (const GLchar *name,GLfloat value, GLboolean useShader = false);
    void SetInt (const GLchar *name, GLint value, GLboolean useShader = false);
    void SetVector2f (const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
    void SetVector2f (const GLchar *name, glm::vec2 &value, GLboolean useShader = false);
    void SetVector3f (const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
    void SetVector3f (const GLchar *name, glm::vec3 &value, GLboolean useShader = false);
    void SetVector4f (const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
    void SetVector4f (const GLchar *name, glm::vec4 &value, GLboolean useShader = false);
    void SetMatrix4 (const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);
private:
    void checkCompileErrors(GLuint object, std::string type);
};

#endif /* Shader_hpp */
