#pragma once

#include "../Engine/Component.h"
#include "../Engine/Input.h"
#include "../Engine/Texture.h"
#include "../Engine/Button.h"

class SideMenu : public Component
{
public:
    SideMenu();

    void Draw();
    void Update(double dt) override;
    void Unload();
    bool GetisIcecreamClicked() { return isbuyIcecreamClicked; }
    bool GetIsDraw() { return SideMenuDraw; }
    void SetDraw(bool type) { type = SideMenuDraw; };

private:

    Texture BackGround;
    Button buyIcecream, sidemenu;

    std::vector<Texture> Merchandise;

    bool SideMenuDraw;

    bool IssidemenuClicked;

    bool isbuyIcecreamClicked;
};