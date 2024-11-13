#pragma once

#include "..\Engine\Texture.h" 
#include "..\Engine\Component.h"
#include "..\Engine/Input.h"

class Number : public Component
{
public:
    Number();
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
    std::vector<Numbers> redTexture;
    vec2 startPos{ 350,615 };

    long int number{26};
    /*int vol_num{};*/
    InputKey cheat;
};