#pragma once
#include <vector>

#include "vec2.h"
#include "../Engine/Component.h"
#include "../Engine/Texture.h"

class CleanUp : public Component
{
public:
    CleanUp();
    void Unload();
    void Draw(vec2 _position);
    vec2 Size();
private:
    struct FoodInfo
    {
        Texture* texturePtr;
    };
    std::vector<FoodInfo> texture;
};
