#version 410 core

layout(location = 0) in vec2 TexCoord;

uniform sampler2D tex;

out vec4 fColor;

void main()
{
	fColor = texture(tex, TexCoord);
}

