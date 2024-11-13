#pragma once
#include <vector>

#include "vec2.h"

#include "../Engine/Texture.h"
#include "../Engine/Component.h"

class HighLight : public Component
{
public:
    void Add();
    void Unload();
    void SetPos(vec2 position);
    void Draw();
    vec2 Size();
    void SetIsDrawing(bool check);
    bool GetIsDraw();
private:
    Texture* texture;
    vec2 Pos{ 0,0 };
    bool IsDraw = false;
};
