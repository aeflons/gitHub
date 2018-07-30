//
//  nextMain.cpp
//  OpenglMac_06
//
//  Created by yujunzhen on 2018/7/27.
//  Copyright © 2018年 yujunzhen. All rights reserved.
//

#include <iostream>
#include "vgl.h"
#include "LoadShaders.h"
#include "vmath.h"
#include <GL/glew.h>
#include "vermilion.h"
#include <GLUT/GLUT.h>
#include "SOIL.h"
#include "vapp.h"
#include "vutils.h"
#include "vbm.h"
#include <time.h>
using namespace std;


float aspect;
GLuint skybox_prog;
GLuint object_prog;
GLuint vao;

GLuint cube_vbo;
GLuint cube_element_buffer;

GLuint tex;
GLint skybox_rotate_loc;

GLint object_mat_mvp_loc;
GLint object_mat_mv_loc;

VBObject object;

void Init()
{
    skybox_prog = glCreateProgram();

    static const char skybox_shader_vs[] =
    "#version 410 core\n"
    "\n"
    "layout (location = 0) in vec3 in_position;\n"
    "\n"
    "out vec3 tex_coord;\n"
    "\n"
    "uniform mat4 tc_rotate;\n"
    "\n"
    "void main(void)\n"
    "{\n"
    "    gl_Position = tc_rotate * vec4(in_position, 1.0);\n"
    "    tex_coord = in_position;\n"
    "}\n"
    ;

    static const char skybox_shader_fs[] =
    "#version 410 core\n"
    "\n"
    "in vec3 tex_coord;\n"
    "\n"
    "layout (location = 0) out vec4 color;\n"
    "\n"
    "uniform samplerCube tex;\n"
    "\n"
    "void main(void)\n"
    "{\n"
    "    color = texture(tex, tex_coord);\n"
    "}\n"
    ;

    vglAttachShaderSource(skybox_prog, GL_VERTEX_SHADER, skybox_shader_vs);
    vglAttachShaderSource(skybox_prog, GL_FRAGMENT_SHADER, skybox_shader_fs);

    glLinkProgram(skybox_prog);

    static const char object_shader_vs[] =
    "#version 410 core\n"
    "\n"
    "layout (location = 0) in vec4 in_position;\n"
    "layout (location = 1) in vec3 in_normal;\n"
    "\n"
    "out vec3 vs_fs_normal;\n"
    "out vec3 vs_fs_position;\n"
    "\n"
    "uniform mat4 mat_mvp;\n"
    "uniform mat4 mat_mv;\n"
    "\n"
    "void main(void)\n"
    "{\n"
    "    gl_Position = mat_mvp * in_position;\n"
    "    vs_fs_normal = mat3(mat_mv) * in_normal;\n"
    "    vs_fs_position = (mat_mv * in_position).xyz;\n"
    "}\n"
    ;
    static const char object_shader_fs[] =
    "#version 410 core\n"
    "\n"
    "in vec3 vs_fs_normal;\n"
    "in vec3 vs_fs_position;\n"
    "\n"
    "layout (location = 0) out vec4 color;\n"
    "\n"
    "uniform samplerCube tex;\n"
    "\n"
    "void main(void)\n"
    "{\n"
    "    vec3 tc =  reflect(vs_fs_position, normalize(vs_fs_normal));\n"
    "    color =  texture(tex, tc);\n"
    "}\n"
    ;

    object_prog = glCreateProgram();

    vglAttachShaderSource(object_prog, GL_VERTEX_SHADER, object_shader_vs);
    vglAttachShaderSource(object_prog, GL_FRAGMENT_SHADER, object_shader_fs);

    glLinkProgram(object_prog);

    glGenBuffers(1, &cube_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, cube_vbo);

    static const GLfloat cube_vertices[] =
    {
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f,  1.0f,  1.0f
    };

    static const GLushort cube_indices[] =
    {
        0, 1, 2, 3, 6, 7, 4, 5,         // First strip
        2, 6, 0, 4, 1, 5, 3, 7          // Second strip
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &cube_element_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube_element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

    skybox_rotate_loc = glGetUniformLocation(skybox_prog, "tc_rotate");
    object_mat_mvp_loc = glGetUniformLocation(object_prog, "mat_mvp");
    object_mat_mv_loc = glGetUniformLocation(object_prog, "mat_mv");

    vglImageData image;

    tex = vglLoadTexture("TantolundenCube.dds", 0, &image);

    GLenum e;

    e = glGetError();

    vglUnloadImage(&image);

    object.LoadFromVBM("unit_cube.vbm", 0, 1, 2);

}
unsigned long GetTickCount()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC,&ts);
    return (ts.tv_sec * 1000 + ts.tv_nsec/(1000*1000) );
}
void Display(){
    static const unsigned long start_time = GetTickCount();
    float t = float((GetTickCount() - start_time)) / float(0x3FFF);
    static const vmath::vec3 X(1.0f, 0.0f, 0.0f);
    static const vmath::vec3 Y(0.0f, 1.0f, 0.0f);
    static const vmath::vec3 Z(0.0f, 0.0f, 1.0f);

    vmath::mat4 tc_matrix(vmath::mat4::identity());

    glClearColor(0.0f, 0.25f, 0.3f, 1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_CULL_FACE);
    glUseProgram(skybox_prog);

    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    //glDisable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    tc_matrix = vmath::rotate(45.0f, Y);// * vmath::rotate(22.0f, Z);
    tc_matrix = vmath::perspective(35.0f, 1.0f / aspect, 0.1f, 100.0f) * tc_matrix;

    glUniformMatrix4fv(skybox_rotate_loc, 1, GL_FALSE, tc_matrix);
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube_element_buffer);

    glDrawElements(GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_SHORT, NULL);
    glDrawElements(GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_SHORT, BUFFER_OFFSET(8 * sizeof(GLushort)));

    glUseProgram(object_prog);

    tc_matrix = vmath::translate(vmath::vec3(0.0f, 0.0f, -4.0f)) *
    vmath::rotate(80.0f * 3.0f * t, Y) * vmath::rotate(70.0f * 3.0f * t, Z);

    glUniformMatrix4fv(object_mat_mv_loc, 1, GL_FALSE, tc_matrix);
    tc_matrix = vmath::perspective(35.0f, 1.0f / aspect, 0.1f, 100.0f) * tc_matrix;
    glUniformMatrix4fv(object_mat_mvp_loc, 1, GL_FALSE, tc_matrix);

    glClear(GL_DEPTH_BUFFER_BIT);

    object.Render();
}
int main(int argc, char*argv[])
{
    glutInit(&argc, (char**)argv);
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA  | GLUT_DOUBLE | GLUT_MULTISAMPLE | GLUT_STENCIL);
    glutInitWindowSize(512, 512);
    glutCreateWindow(argv[0]);
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();

    if (GLEW_OK != err) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    if (GLEW_VERSION_4_1) {
        std::cout << "Yay! OpenGL 4.1 is supported!" << std::endl;
    }

    Init();

    glutDisplayFunc(Display);

    glutMainLoop();

    return 0;
}

