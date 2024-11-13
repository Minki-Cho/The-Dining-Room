#pragma once

#include "..\Engine\Texture.h" 
#include "..\Engine\Component.h"

class Days : public Component
{
public:
    void Add();
    void Unload();
    void Update(double dt) override;
    void Draw();
    void UpdateNumber(int num);
    void SetNumber(int num);
    bool Broke();
    int  GetNumber();
private:
    struct Numbers
    {
        Texture* texturePtr;
        int which_number;
    };
    std::vector<Numbers> texture;
    vec2 startPos{ 40,605 };
    unsigned long int number{ 1 };
};