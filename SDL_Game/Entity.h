#pragma once
#include "RenderWindow.h"
#include <unordered_map>
#include "Texture.h"
#include "AnimationManager.h"
#include "SoundManager.h"

enum State
{
	Idle,
	Idle1,
	Idle2,
	Idle3,
	Walk,
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
	bool changeLevel = false;
	bool removed = false;
	bool breakLoop = false;
protected:
	int texture_width;
	int texture_height;	
	float getHitJump = 250;
	float scale = 1;
	float score = 0;
	Rect atkBox;	
	Rect OFFSET;
	std::unordered_map<int, Animation> animations;
	std::vector<Entity*> Entities;
	
	void Loop() { breakLoop = false; }	
	void BreakLoop() { breakLoop = true; }
	bool IsOnGround();
	void ChangeLevel();
	void UpdateGravity();
	void UpdateAnimation(const float& dt);
	

public:	
	Vector size;
	Vector pos;
	Texture tex;

	Entity* parent = nullptr;
	AnimationManager animationManger;	
	Vector center_pos;
	State current;
	Vector velocity = Vector::zero();
	Rect rect;
	Rect old_rect;
	bool backDrop = false;
	bool isHurt = false;
	bool isOnGround;
	float gravity;
	float moveSpeed;
	float jump;
	float rotate;
	float damage;
	float attackFrame = 0;
	float damageTaken;
	double beingAttackTime = 0;
	float hp;
	float currentHp;
	int hurtDirection;
	

	virtual ~Entity() = default;

	virtual void Update(const float& dt);
	virtual void Draw();

	float AttackStepTime(Entity entity);
	Entity add(Entity* entity);
	void freeEntities();
	void freeAnimations();
	void add_NoPoitner(Entity& entity);
	void Collision(std::string direction);
	void SetCollision(float _left, float _top, float _right, float _bottom);
	void DrawAnimateGroup();
	void removeFromTree();
	void setRemove();
	bool isRemoved();
	bool isAttacking();
	bool isChangLevel();
	void DrawRectTransform(Rect r);
	void DrawFillRectTransform(Rect r);
	void DrawFillRectStatic(Rect r);
	void DrawRectStatic(Rect r);
	void beingAttacked(const Entity& entity, const float& dt);
	void beingHurt();
	bool IsBreakLoop();
	Rect getAtkBox();
	Vector GetPos();
	Rect GravityRect();
	Vector GetCenter();
};

//extern std::vector<Entity*> Collisions;
extern std::vector<Rect> Collisions;

