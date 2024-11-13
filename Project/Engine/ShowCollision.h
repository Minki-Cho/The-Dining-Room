#pragma once
#include "Input.h" //showCollisionKey
#include "Component.h" //Component inheritance

class ShowCollision : public Component {
public:
    ShowCollision(InputKey::Keyboard keyToUse);
    void Update(double) override;
    bool IsEnabled();
private:
    bool enabled;
    InputKey showCollisionKey;
};