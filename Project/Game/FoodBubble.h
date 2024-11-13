#pragma once
#include <vector>

#include "vec2.h"
#include "FoodType.h"
#include "../Engine/Component.h"
#include "../Engine/Texture.h"

class FoodBubble : public Component
{
public:
    FoodBubble();
    void Add(const std::filesystem::path& texturePath);
    void Unload();
    void Draw(vec2 _position, FoodType m_type, FoodType s_type);
    vec2 Size();
private:
    struct FoodInfo
    {
        Texture* texturePtr;
    };
    std::vector<FoodInfo> texture;
};
