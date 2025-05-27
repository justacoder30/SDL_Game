#include "Camera.h"
#include "Global.h"
#include "RenderWindow.h"

float clamp(float value, float min, float max) {
	if (value < min) value = min;
	if (value > max) value = max;

	return value;
}

void Camera::CaculateWindowSize()
{
	/*window_size.x = (window.GetWindowSize().y * 16.f) / 9.f;

	if (window_size.x != window.GetWindowSize().x) {
		if (window_size.x < window.GetWindowSize().x)
	}*/
}

Camera::Camera()
{}

Camera::Camera(float w, float h)
{
	window_size.x = w * Global.scale;
	window_size.y = h * Global.scale;
		
	rect = Rect(0, 0, w, h);
	visibleWoldRect = rect;
}

void Camera::SetCamera(Vector _windowSize)
{
	window_size.x = rect.w * Global.scale;
	window_size.y = rect.h * Global.scale;

	pos.x = abs(_windowSize.x - window_size.x) / 2.f;
	pos.y = abs(_windowSize.y - window_size.y) / 2.f;
}

void Camera::SetBound(float left, float top, float right, float bottom)
{
	bound.left = left;
	bound.top = top;
	bound.right = right;
	bound.bottom = bottom;
}

void Camera::SetAnchor(float x, float y)
{
	if (x < 0) x = 0;
	if (x > 1) x = 1;
	if (y < 0) y = 0;
	if (y > 1) y = 1;

	anchor.x = x;
	anchor.y = y;
}

void Camera::Follow(Vector* _pos)
{
	dst_pos = _pos;
}

void Camera::Update()
{
	rect = Rect(pos.x / Global.scale,
				pos.y / Global.scale, 
				window_size.x / Global.scale, 
				window_size.y / Global.scale);
	
	transform.x = clamp(rect.w * anchor.x - dst_pos->x, rect.w * anchor.x - bound.right, rect.w * anchor.x - bound.left);
	transform.y = clamp(rect.h * anchor.y - dst_pos->y, rect.h * anchor.y - bound.bottom , rect.h * anchor.y - bound.top);

	float increase = 10;

	visibleWoldRect = Rect(
		-transform.x - increase/2,
		-transform.y - increase/2,
		rect.w + increase,
		rect.h + increase
	);
}

bool Camera::canSee(Rect rect)
{
	Rect r(0, 0, rect.w, rect.h);

	return visibleWoldRect.checkCollide(rect) || r.checkCollide(rect);
}
