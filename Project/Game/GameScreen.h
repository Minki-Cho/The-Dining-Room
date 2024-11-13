#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Texture.h"
#include <array>
struct rect3;

class GameScreen : public Component
{
public:
    GameScreen();
    void Add(const std::filesystem::path& texturePath);
    void Unload();
    void Draw();
    vec2 Size();
    vec2 GetMapPos(int x, int y);
private:
    Texture* texturePtr;
    const vec2 startPos = vec2{ 169,15 };

    std::array<std::array<vec2, 12>, 23> map;
    
    vec2 tile;
};
