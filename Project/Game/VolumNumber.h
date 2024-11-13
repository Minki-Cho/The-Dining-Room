#pragma once

#include "..\Engine\Texture.h" 
#include "..\Engine\Component.h"
#include "..\Engine/Input.h"

class Volum_Number : public Component
{
public:
    Volum_Number();
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
    vec2 startPos{ 850,415 };

    long int number{ 0 };

};