#pragma once

#include "..\Engine\Texture.h" 
#include "..\Engine\Component.h"
#include "..\Engine\Button.h"

class Result : public Component
{
public:
    Result(long int num1, long int num2);
    void Add();
    void Unload();
    void Update(double dt) override;
    void Draw();
    void SetNum(long day, long money);
    void SetDraw(bool is_Draw);

private:
    struct Numbers
    {
        Texture* texturePtr;
        int which_number;
    };
    std::vector<Numbers> texture;
    std::vector<Numbers> redTexture;

    std::vector<Button*> buttons;

    vec2 startPos1{ 490,445 };
    vec2 startPos2{ 660,335 };

    long int number1, number2;
    bool IsDraw;
};