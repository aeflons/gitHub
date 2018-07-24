#version 410 core
sample in vec4 color;
out vec4 fColor;

void
main()
{
    //Color = {1.0, 0.5, 0.2, 1.0};
    fColor = color;
}
