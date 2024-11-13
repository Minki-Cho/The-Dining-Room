#pragma once

#include "../Engine/Component.h"
#include "../Engine/Input.h"
#include "../Engine/Texture.h"
#include "../Engine/Button.h"

class Skill : public Component
{
public:
    Skill();

    void Update(double dt) override;
    void Draw();
    void Unload();

    bool GetisDashClicked() { return isbuyDashClicked; }

    bool getIsDraw() { return Skilldraw; }
    void SetDraw(bool type) { type = Skilldraw; };

private:

    Texture BackGround;
    Button buydash, skill;

    std::vector<Texture> Merchandise;

    bool Skilldraw;
    bool IsskillClicked;
    bool isbuyDashClicked;
};