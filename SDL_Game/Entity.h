#pragma once
#include "RenderWindow.h"
#include <unordered_map>
#include "Texture.h"
#include "AnimationManager.h"

enum State
{
	Idle,
	Idle1,
	Idle2,
	Idle3,
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
	bool removed = false;
	Rect atkBox;
	
	Rect OFFSET;
	std::unordered_map<State, Animation> animations;
	std::vector<Entity*> Entities;

	bool IsOnGround();
	void UpdateGravity();
	void UpdateAnimation();
	void DrawRectTransform(Rect r);

public:	
	Vector size;
	Vector pos;
	Texture tex;

	AnimationManager animationManger;	
	Vector center_pos;
	State current;
	Vector velocity = Vector::zero();
	Rect rect;
	Rect old_rect;
	bool backDrop = false;
	bool isHurt = false;
	float damageTaken = 10;
	bool isOnGround;
	float gravity;
	float moveSpeed;
	float jump;
	float rotate;
	float damage;
	float attackFrame = 0;

	Entity();

	virtual void Update();
	virtual void Draw();

	void add(Entity* entity);
	void Collision(std::string direction);
	void SetCollision(float _left, float _top, float _right, float _bottom);
	void DrawAnimateGroup();
	void removeFromTree();
	bool isRemoved();
	bool isAttacking();
	Rect getAtkBox();
	Vector GetPos();
	Rect GravityRect();
	Vector GetCenter();
};

//extern std::vector<Entity*> Collisions;
extern std::vector<Rect> Collisions;

