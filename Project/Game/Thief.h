#pragma once
#include <vector>

#include "GameObjectTypes.h"  // GameObjectType
#include "mat3.h"

#include "../Engine/GameObject.h"
#include "../Engine/Texture.h"
#include "../Engine/Input.h"
#include "vec2.h"

class Thief : public GameObject
{
public:
	Thief(vec2 _startPos);
	~Thief();
	void Update(double dt) override;
	bool CanCollideWith(GameObjectType objectBType) override;
	void ResolveCollision(GameObject* objectB) override;
	void Draw(mat3<float> displayMatrix);

	GameObjectType GetObjectType() override { return GameObjectType::Thief; }
	std::string GetObjectTypeName() override { return "Thief"; }
	bool steal_money = false;
private:
	// other privite things...
	vec2 startPos;
	int animNumber = 0;
	static constexpr double speed = 200.0f;
	Texture* texturePtr;
	double timer=0;
private:

	class StateRunning_Right : public State
	{
		double limit = 950.0;
		InputKey Push = InputKey::Keyboard::Space;
		double timer = 0;
		bool moving_one_end = false;
	public:
		virtual void Enter([[maybe_unused]] GameObject* object) override;
		virtual void Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "Running"; }
	};
	class StateRunning_Up : public State
	{
		double limit = 500.0;
		InputKey Push = InputKey::Keyboard::Space;
		double timer = 0;
		bool change_animation = false;
		bool moving_two_end = false;
	public:
		virtual void Enter([[maybe_unused]] GameObject* object) override;
		virtual void Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "Running"; }
	};
	class StateRunning_Right2: public State
	{
		double limit = 500.0;
		InputKey Push = InputKey::Keyboard::Space;
		double timer = 0;
		bool change_animation = false;
		bool moving_two_end = false;
	public:
		virtual void Enter([[maybe_unused]] GameObject* object) override;
		virtual void Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "Running"; }
	};
	class StateRunning_Down : public State
	{
		double timer = 0.f;
		bool moving_two_end = false;
	public:
		virtual void Enter([[maybe_unused]] GameObject* object) override;
		virtual void Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "Running"; }
	};
	class StateSteal : public State
	{
		double limit = 500.0;
		double timer = 0.f;
		bool moving_two_end = false;
	public:
		virtual void Enter([[maybe_unused]] GameObject* object) override;
		virtual void Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "Steal"; }
	};
	class StateSteal_Left : public State
	{
		bool moving_two_end = false;
	public:
		virtual void Enter([[maybe_unused]] GameObject* object) override;
		virtual void Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "Steal"; }
	};

	StateRunning_Right staterunning_right;
	StateRunning_Up    staterunning_up;
	StateRunning_Right2 staterunning_right2;
	StateRunning_Down staterunning_down;
	StateSteal statesteal;
	StateSteal_Left statesteal_left;

};