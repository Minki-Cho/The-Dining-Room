#pragma once
#include <vector>

#include "vec2.h"

#include "../Engine/Texture.h"
#include "../Engine/Component.h"

class Kitchen : public Component
{
public:
    void Add(const std::filesystem::path& texturePath);
    void Unload();
    void Draw();
    vec2 Size();
private:
    struct ParallaxInfo
    {
        Texture* texturePtr;
    };
    std::vector<ParallaxInfo> texture;
    vec2 startPos{ 0,0 };
};
