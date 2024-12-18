#version 450 core

layout (location=0) in  vec2 aVertexPosition;
layout (location=1) in  vec4 aVertexColor;
layout (location=0) out vec4 vColor;

uniform mat3 uModelToNDC;
uniform vec2 pos_vtx;

void main() {
  gl_Position = vec4(vec2(uModelToNDC * vec3(aVertexPosition, 1.f)), 
                     0.0, 1.0);
  vColor = aVertexColor;
}