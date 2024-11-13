#version 450 core

layout(location = 1) in vec2 vTextureCoordinates;

layout(location = 0) out vec4 fFragClr;

uniform sampler2D uTex2d;

void main()
{
    vec4 texture_color = vec4(1);

    texture_color = texture(uTex2d, vTextureCoordinates);

    fFragClr = texture_color;
}