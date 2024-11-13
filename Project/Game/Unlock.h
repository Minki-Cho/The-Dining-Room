#pragma once

#include "..\Engine\Component.h"
#include "../Engine/Texture.h"

class Unlock : public Component
{
public:
    Unlock();
    void Load(const std::filesystem::path& texturePath);

    void Update(double dt) override;
    void Draw();

    //ingredients
    bool GetLettuce() { return isLettuce; }
    bool GetTomato() { return isTomato; }
    bool GetCheese() { return isCheese; }

    void SetLettuce(bool status) { isLettuce = status; }
    void SetTomato(bool status) { isTomato = status; }
    void SetCheese(bool status) { isCheese = status; }
    
    bool GetUnlockLettuce() { return UnlockLettuce; }
    bool GetUnlockTomato() { return UnlockTomato; }
    bool GetUnlockCheese() { return UnlockCheese; }

    //side menu
    bool GetIcecream() { return isIcecream; }
    void SetSideMenu(bool status) { isIcecream = status; }
    bool GetUnlockIcecream() { return UnlockIcecream; }

    //skills
    bool GetDash() { return isDash; }
    void SetDash(bool status) { isDash = status; }
    bool GetUnlockDash() { return UnlockDash; }
    
private:
    //ingredients
    bool isLettuce = false;
    bool isTomato = false;
    bool isCheese = false;
    
    bool LettuceLocked = true; //Lettuce with locker
    bool TomatoLocked = true; //Tomato with locker
    bool CheeseLocked = true; //Cheese with locker
    
    bool UnlockLettuce = false; // Lettuce without locker
    bool UnlockTomato = false; // Tomato without locker
    bool UnlockCheese = false; // Cheese without locker

    //side menu
    bool isIcecream = false;
    bool IcecreamLocked = true; // Icecream with locker    
    bool UnlockIcecream = false; // Icecream without locker
    
    //skills
    bool isDash = false;
    bool DashLocked = true; //Dash with locker
    bool UnlockDash; // Dash without locker

    struct ParallaxInfo
    {
        Texture* texturePtr;
    };
    std::vector<ParallaxInfo> texture;
};