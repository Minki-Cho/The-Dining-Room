#pragma once

#include "..\Engine\Texture.h" 
#include "..\Engine\Component.h"

class Double_Event : public Component
{
public:
    Double_Event();

    void Update(double dt) override;
    void Draw();
    bool GetIsEvent() { return isEvent;  }
    void SetIsEvent(bool isevent) { isEvent = isevent; }
    void Unload();
private:

    Texture Event_texture;
    vec2 startPos{ 45,405 };
    bool isEvent = false;;
};