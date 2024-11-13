#pragma once
#include <vector>

#include "vec2.h"

#include "../Engine/Component.h"
#include "../Engine/Texture.h"

class Money : public Component
{
public:
    Money();
    void Add(const std::filesystem::path& texturePath);
    void Unload();
    void Draw(vec2 position);
    vec2 Size();
private:
    struct MoneyInfo
    {
        Texture* texturePtr;
    };
    std::vector<MoneyInfo> texture;
};
