#pragma once
#include "Rect.h"
#include "Vector.h"

class Camera
{
private:
	Rect size;
	Vector window_size;
	Vector pos;
	Rect bound;
	Vector anchor = Vector::zero();
	void CaculateWindowSize();
public:
	Rect visibleWoldRect;
	Rect rect;
	Vector transform;
	Vector previous;
	Vector* dst_pos = new Vector(0, 0);
	float speed = 0.05;

	Camera();
	Camera(float w, float h);
	void SetCamera(Vector _windowSize);
	void SetBound(float left, float top, float right, float bottom);
	void SetAnchor(float x=0, float y=0);
	void Follow(Vector* _pos);
	void Update();
	bool canSee(Rect rect);
};

