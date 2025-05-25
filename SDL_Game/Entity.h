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
	Hurt,
	Attack,
	Attack1,
	Attack2,
	Attack3,
	Death,
	RunAttack,
	Defend,
	Protect,
};

class Entity
{
private:
protected:
	int texture_width;
	int texture_height;
	Texture tex;
	Rect OFFSET;
	std::unordered_map<State, Animation> animations;

	bool IsOnGround();
	void UpdateGravity();
	void UpdateAnimation();

public:	
	AnimationManager animationManger;	
	Vector center_pos;
	State current;
	Vector velocity = Vector::zero();
	Rect rect;
	Rect old_rect;
	bool isOnGround;
	float gravity;
	float moveSpeed;
	float jump;
	float rotate;
	float damage;

	Entity();

	virtual void Update();
	virtual void Draw();

	void Collision(std::string direction);
	void SetCollision(float _left, float _top, float _right, float _bottom);
	Vector GetPos();
	Rect GravityRect();
	Vector GetCenter();
};

//extern std::vector<Entity*> Collisions;
extern std::vector<Rect> Collisions;

