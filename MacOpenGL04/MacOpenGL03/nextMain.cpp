//
//  nextMain.cpp
//  MacOpenGL_04
//
//  Created by 于军振 on 2018/7/21.
//  Copyright © 2018年 Alfons. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "vapp.h"
#include "vutils.h"
#include "LoadShaders.h"
#include "vmath.h"

#include <GL/glew.h>
#include <GLUT/GLUT.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_3_2_CORE_PROFILE);
    glutInitWindowSize(600, 600);
    glutCreateWindow("多实例");
    glewExperimental = GL_TRUE;
    glewInit();
    glutMainLoop(); 
    return 0;
}
