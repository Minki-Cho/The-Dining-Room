#pragma once
#include <GLShader.h>
#include <GLTexture.h>
#include <GLVertexArray.h>

#include "vec2.h"
#include "mat3.h"

class Texture
{
public:
    Texture() {};
    Texture(GLTexture SDLImage);
    Texture(const std::filesystem::path& filePath, bool enableTexel);
    void Load(const std::filesystem::path& filePath);
    void Draw(mat3<float> displayMatrix);
    void Draw(mat3<float> displayMatrix, vec2 texelPos, vec2 frameSize);
    vec2 GetSize();
    void CreateFullscreenQuad();

private:
    GLVertexArray fullscreenQuad;
    GLShader      shader[2];
    GLTexture     image;

    bool enableTexel{ false };
};