#pragma once
#include "RenderWindow.h"
#include <unordered_map>
#include "Texture.h"
#include "AnimationManager.h"

enum State
{
	Idle,
	Run,
	Jump,
	Fall,
	Attack,
	Hurt,
};

class CharacterState
{
protected:
	State state;
public:
	virtual ~CharacterState() {}
	virtual void Intput() {}
	virtual void Update() {}
	virtual State GetState() {
		return state;
	}
};

class Entity
{
private:
protected:
	int texture_width;
	int texture_height;
	Rect OFFSET;
	bool falling;

	bool IsFalling();
	void UpdateGravity();

public:
	std::unordered_map<std::string, Animation> animations;
	AnimationManager animationManger;
	Texture tex;
	Vector pos;
	Vector velocity;
	Rect rect;
	Rect old_rect;
	float gravity;
	float speed;
	float jump;

	Entity();

	virtual void Update();
	virtual void Draw();

	void Collision(std::string direction);
	void SetCollision(float _top, float _left, float _bottom, float _right);
	Rect GetRect();
	Rect GravityRect();
	Vector GetCenter();
};

extern std::vector<Entity*> Collisions;

