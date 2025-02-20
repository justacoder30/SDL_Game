#pragma once
#include "Rect.h"
#include "Vector.h"

class Camera
{
private:
	Rect size;
	Vector window_size;
	Vector pos;
	void CaculateWindowSize();
public:
	Rect rect;
	Vector current_pos;
	Vector previous_pos;
	Vector* dst_pos;
	float speed = 0.05;

	Camera();
	Camera(float w, float h);
	void SetCamera(Vector _windowSize);
	void FollowEnity(Vector* _pos);
	void Update();
};

