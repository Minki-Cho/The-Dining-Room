#pragma once
#include "vec2.h"
#include "mat3.h"
#include "GameObjectTypes.h"
#include "Food.h"
#include "CharacterAnim.h"

#include "../Engine/Input.h"
#include "../Engine/Sprite.h"
#include "../Engine/GameObject.h"
#include "../Engine/Texture.h"
#include "../Engine/fmod-sound.h"

static float speed;

class Player : public GameObject
{
public:
    Player(vec2 _startPos);
    ~Player() override;
    void Update(double dt) override;
    void Draw(mat3<float> TransformMatrix);
    bool CanCollideWith(GameObjectType objectBType) override;
    void ResolveCollision(GameObject* objectB) override;
    GameObjectType GetObjectType() override { return GameObjectType::Player; }
    std::string GetObjectTypeName() override { return "Player"; }

    const vec2& GetPosition() const;
    bool& GetIsOnTask();
    Food& GetFood();
    bool IsFoodOnHand();
    void SetToStartPosition();
    void SetFood(Food& _food);
    void SetFoodToNull();
    void SetIsSuccess();
    void SetLastOrder(FoodType _type);
    void SetCanDelivery(bool b);
    bool& GetIsSuccess();
    bool GetCanDelivery();
    FoodType& GetLastOrder();
    bool GetCanMove();
    

private:
    InputKey Up, Down, Left, Right, Space, Shift;
    float timer {0};
    float Cooltimer{3.f};
    bool CooltimeActive{ false };
    vec2 startPos;
    Food* food;
    bool isOnTask;
    CharacterAnim direction = CharacterAnim::None_F;
    bool isSuccess{ false };
    bool canDelivery{ false };
    FoodType lastOrder{ FoodType::None };
    bool canMove{ true };

    //for skill
    bool UsingDash = false;

    class StateIdle : public State
    {
    public:
        virtual void Enter([[maybe_unused]] GameObject* object) override;
        virtual void Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) override;
        virtual void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Idle"; }
    };

    class StateMovingLeft : public State
    {
    public:
        virtual void Enter([[maybe_unused]] GameObject* object) override;
        virtual void Update(GameObject* object, [[maybe_unused]] double dt) override;
        virtual void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Moving"; }
    };

    class StateMovingRight : public State
    {
    public:
        virtual void Enter([[maybe_unused]] GameObject* object) override;
        virtual void Update(GameObject* object, [[maybe_unused]] double dt) override;
        virtual void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Moving"; }
    };

    class StateMovingUp : public State
    {
    public:
        virtual void Enter([[maybe_unused]] GameObject* object) override;
        virtual void Update(GameObject* object, [[maybe_unused]] double dt) override;
        virtual void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Moving"; }
    };

    class StateMovingDown : public State
    {
    public:
        virtual void Enter([[maybe_unused]] GameObject* object) override;
        virtual void Update(GameObject* object, [[maybe_unused]] double dt) override;
        virtual void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Moving"; }
    };

    StateIdle stateIdle;
    StateMovingLeft stateMovingLeft;
    StateMovingRight stateMovingRight;
    StateMovingUp stateMovingUp;
    StateMovingDown stateMovingDown;
};