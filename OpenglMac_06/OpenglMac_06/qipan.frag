
#version 330

layout(location = 0) in vec3 VertColor;
layout(location = 1) in vec2 TextCoord;

uniform sampler2D tex;

out vec4 color;


void main()
{
    color = texture(tex, TextCoord);
}
