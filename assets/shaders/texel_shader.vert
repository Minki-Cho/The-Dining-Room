#version 450 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;

layout(location = 1) out vec2 vTextureCoordinates;

uniform mat3 uModelToNDC;
uniform vec2 uFrameSize;
uniform vec2 uTexelPos;

void main()
{
    //vTextureCoordinates = ((aVertexPosition + 1) / 2) * uFrameSize + uTexelPos;

    vTextureCoordinates = (aVertexPosition * uFrameSize) + uTexelPos;

    gl_Position = vec4(vec2(uModelToNDC * vec3(aVertexPosition, 1.f)), 0.0, 1.0);
}