#pragma once
#include "Entity.h"

class LoadingScreen: public Entity
{
private:
	int currentIndex = 0;
	std::vector<State> states;
	
	
public:
	double durationTime = 0;
	double time = 0;
	LoadingScreen(Vector size, double durationTime);
	LoadingScreen();
	~LoadingScreen()
	{
		freeEntities();
		freeAnimations();
	}
	void Update(const float& dt);
	void UpdateState(const float& dt);
	void Draw();
	bool isEnd();
};

