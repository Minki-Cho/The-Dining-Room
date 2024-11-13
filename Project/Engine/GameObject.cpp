#include "GameObject.h" //GameObject
#include "Collision.h" //GetGOComponent
#include "ShowCollision.h" //GetGSComponent
#include "Engine.h" //GetGSComponent

GameObject::GameObject() : currState(nullptr), rotation(0), updateMatrix(false) {}

GameObject::GameObject(vec2 position) : GameObject(position, 0, { 1, 1 }) {}

GameObject::GameObject(vec2 position, double rotation, vec2 scale)
    : velocity{ 0,0 }, position(position), updateMatrix(true),
    scale(scale), rotation(rotation), currState(&state_nothing) {}

GameObject::~GameObject()
{
    components.Clear();
}

void GameObject::Update(double dt)
{
    currState->Update(this, dt);
    if (velocity.x != 0 || velocity.y != 0)
    {
        UpdatePosition(velocity * static_cast<float>(dt));
    }
    UpdateGOComponents(dt);
    currState->TestForExit(this);
}

void GameObject::Draw(mat3<float> cameraMatrix)
{
    Sprite* spritePtr = GetGOComponent<Sprite>();
    if (spritePtr != nullptr)
    {
        spritePtr->Draw(cameraMatrix * GetMatrix());
    }
    if (Engine::GetGSComponent<ShowCollision>() != nullptr)
    {
        if (Engine::GetGSComponent<ShowCollision>()->IsEnabled() == true)
        {
            if (GetGOComponent<Collision>() != nullptr)
                GetGOComponent<Collision>()->Draw(cameraMatrix);
        }
    }
}

const mat3<float>& GameObject::GetMatrix()
{
    if (updateMatrix == true)
    {
        objectMatrix = mat3<float>::build_translation(position) * mat3<float>::build_rotation(static_cast<float>(rotation)) * mat3<float>::build_scale(scale);
        updateMatrix = false;
    }
    return objectMatrix;
}

const vec2& GameObject::GetPosition() const { return position; }

const vec2& GameObject::GetVelocity() const { return velocity; }

const vec2& GameObject::GetScale() const { return scale; }

double GameObject::GetRotation() const { return rotation; };

void GameObject::SetPosition(vec2 newPosition)
{
    position = newPosition;
    updateMatrix = true;
}

bool GameObject::GetDestroyed()
{
    return shouldDestroyed;
}

void GameObject::SetDestroyed(bool b)
{
    shouldDestroyed = b;
}

bool GameObject::CanCollideWith(GameObjectType)
{
    return false;
}

bool GameObject::DoesCollideWith(GameObject* objectB)
{
    if (GetGOComponent<Collision>() != nullptr && objectB->GetGOComponent<Collision>() != nullptr)
    {
        return GetGOComponent<Collision>()->DoesCollideWith(objectB);
    }
    return false;
}

bool GameObject::DoesCollideWith(vec2 point)
{
    if (GetGOComponent<Collision>() != nullptr)
    {
        return GetGOComponent<Collision>()->DoesCollideWith(point);
    }
    return false;
}

void GameObject::ResolveCollision(GameObject*)
{
    Engine::GetLogger().LogError("This function should not be called!");
}

void GameObject::UpdatePosition(vec2 adjustPosition)
{
    position += adjustPosition;
    updateMatrix = true;
}

void GameObject::SetVelocity(vec2 newVelocity)
{
    velocity = newVelocity;
}

void GameObject::UpdateVelocity(vec2 adjustPosition)
{
    velocity += adjustPosition;
    updateMatrix = true;
}

void GameObject::SetScale(vec2 newScale)
{
    scale = newScale;
}

void GameObject::SetRotation(double newRotationAmount)
{
    rotation = newRotationAmount;
}

void GameObject::UpdateRotation(double newRotationAmount)
{
    rotation += newRotationAmount;
    updateMatrix = true;
}

void GameObject::ChangeState(State* newState) {
    currState = newState;
    currState->Enter(this);
}