#version 410 core
in vec2 TexCoord;
uniform sampler2D OurTextture1;
uniform sampler2D OurTextture2;
out vec4 color;
void main(void){
    color = mix(texture(OurTextture1,TexCoord),texture(OurTextture2,TexCoord),0.5);
}
