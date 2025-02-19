#include "Camera.h"
#include "Global.h"
#include "RenderWindow.h"


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
}

void Camera::FollowEnity(Vector* _pos)
{
	dst_pos = _pos;
	pos.x = abs(window.GetWindowSize().x - window_size.x) / 2.f;
	pos.y = abs(window.GetWindowSize().y - window_size.y) / 2.f;
}

void Camera::Update()
{
	rect = Rect(pos.x / Global.scale,
				pos.y / Global.scale, 
				window_size.x / Global.scale, 
				window_size.y / Global.scale);
	
	current_pos.x = rect.w / 2.0 - dst_pos->x;
	current_pos.y = rect.h / 2.0 - dst_pos->y;
}
