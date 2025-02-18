#include "Camera.h"
#include "Global.h"
#include "RenderWindow.h"

Camera::Camera()
{}

Camera::Camera(float w, float h)
{
	rect = Rect(0, 0, w, h);
}

void Camera::FollowEnity(Vector* pos)
{
	dst_pos = pos;
}

void Camera::Update()
{
	rect.w = window.GetWindowSize().x / Global.scale;
	rect.h = window.GetWindowSize().y / Global.scale;

	current_pos.x = rect.w / 2.0 - dst_pos->x;
	current_pos.y = rect.h / 2.0 - dst_pos->y;
}
