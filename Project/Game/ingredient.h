#pragma once

#include "../Engine/Component.h"
#include "../Engine/Input.h"
#include "../Engine/Texture.h"
#include "../Engine/Button.h"

class ingredient : public Component
{
public:
    ingredient();

    void Draw();
    void Update(double dt) override;
    void Unload();
    bool GetisLettuceClicked() { return isbuyLettuceClicked; }
    bool GetisTomatoClicked() { return isbuyTomatoClicked; }
    bool GetisCheeseeClicked() { return isbuyCheeseClicked; }
    bool GetIsDraw() { return IngredientsDraw; }
    void SetDraw(bool type) { type = IngredientsDraw; };

private:

    Texture BackGround;
    Button buylettuce, buytomato ,buycheese, ingredients;

    std::vector<Texture> Merchandise;

    bool IngredientsDraw = true;

    bool IsindredientsClicked;

    bool isbuyLettuceClicked;
    bool isbuyCheeseClicked;
    bool isbuyTomatoClicked;
};