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
	DoubleAttack,
	Hurt,
};

class Entity
{
private:
protected:
	int texture_width;
	int texture_height;
	Texture tex;
	Rect OFFSET;
	std::unordered_map<std::string, Animation> animations;	

	bool IsFalling();
	void UpdateGravity();

public:	
	AnimationManager animationManger;	
	Vector velocity;
	Rect rect;
	Rect old_rect;
	float gravity;
	float speed;
	float jump;
	bool falling;

	Entity();

	virtual void Update();
	virtual void Draw();

	void Collision(std::string direction);
	void SetCollision(float _top, float _bottom, float _left, float _right);
	Vector GetPos();
	Rect GravityRect();
	Vector GetCenter();
};

extern std::vector<Entity*> Collisions;

