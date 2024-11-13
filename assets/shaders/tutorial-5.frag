#version 450 core

layout(location = 0) in vec3 vColor;
layout(location = 1) in vec2 vTextureCoordinates;

layout(location = 0) out vec4 fFragClr;

uniform bool uUseInterpolatedColor;
uniform bool uUseProceduralColor;
uniform bool uUseTexture;
uniform float uTileSize;
uniform sampler2D uTex2d;

void main()
{
    vec4 interpolated_color = vec4(1);
    vec4 procedural_color = vec4(1);
    vec4 texture_color = vec4(1);

    if(uUseInterpolatedColor)
        interpolated_color = vec4(vColor, 1.0);

    if(uUseProceduralColor)
    {
        float total = mod(floor(gl_FragCoord.x / uTileSize) + floor(gl_FragCoord.y / uTileSize), 2);
        procedural_color = mix(vec4(1.0,0.0,1.0,1.0),vec4(0.0,0.68,0.94,1.0),total);
    }

    if(uUseTexture)
    texture_color = texture(uTex2d, vTextureCoordinates);

    fFragClr = interpolated_color * procedural_color * texture_color;
}
