#pragma once
#include <vector>

#include "GameObjectTypes.h"  // GameObjectType
#include "mat3.h"
#include "Table.h"
#include "Food.h"
#include "Counter.h"

#include "../Engine/GameObject.h"
#include "../Engine/Engine.h"
#include "../Engine/Input.h"
#include "../Engine/Texture.h"

class Guest : public GameObject
{
public:
	Guest(std::vector<Table*>& table);
	~Guest();
	void Update(double dt) override;
	bool CanCollideWith(GameObjectType objectBType) override;
	void ResolveCollision(GameObject* objectB) override;
	void Draw(mat3<float> displayMatrix);
	void SetIsGetFood();
	void SetIsRightMenu();
	void SetCounter(Counter* c) { counter = c; };
	bool GetIsGetFood();
	bool GetIsPaying();
	bool GetIsColideCounter();
	bool GetIsRightMenu();
	bool GetCheck1() { return check[0]; };
	bool GetCheck2() { return check[1]; };
	GameObjectType GetObjectType() override { return GameObjectType::Guest; }
	std::string GetObjectTypeName() override { return "Guest"; }
	bool drawMoney{ false };
	bool finishedPaying = false;

	GLShader shader;
	GLVertexArray gaugeShape;
	void CreateChangingGaugeQuad();
	void DrawGauge(vec2 startPos);
	bool isTable{ false };
private:
	int hair;
	int cloth;
	int shoes;
	Sprite* image;
	Texture* angry_texture = new Texture{ "assets/images/characters/angry.png", false };
	std::vector<Sprite*> images;
	struct Stars
	{
		Texture* texturePtr;
	};
	std::vector<Stars> star_texture;

	int animNumber = 0;

	double frequency;
	bool isDrawing{ true };
	bool isAppear{ true };
	bool drawMenu{ false };
	bool drawAngry{ false };
	bool isColideWorkBenches{ false };
	bool isColideCounter{ false };
	Food* mainFood;
	Food* sideFood;
	Food* drawMainFood;
	Food* drawSideFood;
	Counter* counter;
	bool isGetFood{ false };
	bool isWaiting{ false };
	bool isPaying{ false };
	bool isRightMenu{ false };
	bool isCollide_player{ false };
	bool check[2]{ false, false };

	double timer = 0;
	static constexpr double speed = 100.0f;

	const vec2& GetPosition() const;

	std::vector<Table*> tableList = {};

	class StateMoving : public State
	{
		static constexpr double limit = 950.0;
	public:
		virtual void Enter([[maybe_unused]] GameObject* object) override;
		virtual void Update(GameObject* object, [[maybe_unused]] double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "Moving"; }
	};

	class StateWaiting : public State
	{
		static constexpr double limit = 950.0;
		double timer;
	public:
		virtual void Enter([[maybe_unused]] GameObject* object) override;
		virtual void Update(GameObject* object, [[maybe_unused]] double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "Waiting"; }
	};

	class StateTable : public State
	{
	public:
		virtual void Enter([[maybe_unused]] GameObject* object) override;
		virtual void Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "Idle"; }
	};

	//class StateTable_before : public State
	//{
	//	float temp = 0;
	//	bool check1 = false;
	//	bool check2 = false;
	//	double timer = 0;
	//public:
	//	virtual void Enter([[maybe_unused]] GameObject* object) override;
	//	virtual void Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) override;
	//	virtual void TestForExit(GameObject* object) override;
	//	std::string GetName() override { return "Beforer table"; }
	//};

	class StatePaying : public State
	{
		static constexpr double limit = 950.0;
		double timer = 0;
	public:
		virtual void Enter([[maybe_unused]] GameObject* object) override;
		virtual void Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "Paying"; }
		//bool finishedPaying = false;
	};

	class StateCleanUp : public State
	{
		static constexpr double limit = 950.0;
		InputKey Push = InputKey::Keyboard::Space;
		double timer = 0;
		int count_space = 0;
	public:
		virtual void Enter([[maybe_unused]] GameObject* object) override;
		virtual void Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "CleanUp"; }
		bool isone = false;
		bool istwo = false;
	};

	//class StateLeaveStore : public State
	//{
	//	static constexpr double limit = 950.0;
	//public:
	//	virtual void Enter([[maybe_unused]] GameObject* object) override;
	//	virtual void Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) override;
	//	virtual void TestForExit(GameObject* object) override;
	//	std::string GetName() override { return "Leave the store"; }
	//};

	struct BubbleFoodInfo
	{
		Texture* texturePtr;
	};
	std::vector<BubbleFoodInfo> texture;
	StateTable stateIdle_table;
	//StateTable_before stateTableBefore;
	StateMoving stateMoving;
	StateWaiting stateWaiting;
	StatePaying statePaying;
	StateCleanUp stateCleanUp;
	/*StateLeaveStore stateLeaveStore;*/

	bool isLettuce = false;
	bool isCheeze = false;
};