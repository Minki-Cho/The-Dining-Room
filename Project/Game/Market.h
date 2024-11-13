#pragma once

#include "../Engine/Component.h"
#include "../Engine/Input.h"
#include "../Engine/Texture.h"
#include "../Engine/Button.h"


class Market : public Component
{
public:
    Market();

    void Draw();
    void Update(double dt) override;
    void Unload();

    bool GetIngredientDraw() { return ingredient_draw; }
    bool GetSideMenuDraw() { return sidemenu_draw; }
    bool GetSkillDraw() { return skill_draw; }

    void SetIngredientDraw(bool setDraw) { setDraw = ingredient_draw; }
    void SetSideMenuDraw(bool setDraw) { setDraw = sidemenu_draw; }
    void SetSkillDraw(bool setDraw) { setDraw = skill_draw; }

    bool GetIsDraw() { return Isdraw; }
    void SetDraw(bool type) { type = Isdraw; };

private:

    Texture BackGround;

    std::vector<Button*> buttons;

    bool Isdraw = false;

    bool ingredient_draw;
    bool sidemenu_draw;
    bool skill_draw;

};