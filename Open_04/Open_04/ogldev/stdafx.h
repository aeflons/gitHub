// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <wchar.h>
#include <iostream>
#include <fstream>
#include <string.h>
#ifdef WIN32
#include <Windows.h>
#endif
// #include "stdafx.h"


// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�

// glew��չ��
#include <gl/glew.h>
#pragma comment(lib, "glew32.lib")
// freeGLUT���ڿ�
//#include <freeglut.h>
// �Զ���3d������
#include "ogldev_math_3d.h"
// �Զ��幤�ߺ���
#include "ogldev_util.h"
// ������
#include "ogldev_pipeline.h"
// AntTweakBar.lib
#include "ogldev_glut_backend.h"
#include "ogldev_camera.h"

//#include <sys/time.h>
