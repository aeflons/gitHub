#version 330 core
layout(location = 0) in vec4 vColor;
layout(location = 1) in vec4 vPos;
out vec4 color;
void
main()
{
    
    gl_Position = vPos;
    color = vColor;
}
//layout(location = 0) in vec4 vPosition;
//void
//main()
//{
//    vec4 p = vPosition;
//    gl_Position = p;
//}
