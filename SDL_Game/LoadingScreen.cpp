#include "LoadingScreen.h"
#include "SoundManager.h"

LoadingScreen::LoadingScreen(Vector size, double durationTime)
{
	float stepTime = 0.05;
	int amount = 4;
	animations = {
		{Idle1, Animation("resource/img/Loading/32x32_loading1.png", amount, stepTime, false)},
		{Idle2, Animation("resource/img/Loading/32x32_loading2.png", amount, stepTime, false)},
		{Idle3, Animation("resource/img/Loading/32x32_loading3.png", amount, stepTime, false)},
	};

	LoadingScreen::size = size;
	LoadingScreen::durationTime = durationTime;
	//animationManger = AnimationManager(animations[Idle1]);

	states = {
		Idle1,
		Idle2,
		Idle3,
	};

	current = states[currentIndex];

	pos = Vector(
		Global.camera.rect.w/2 - size.x/2,
		Global.camera.rect.h/2 - size.y/2
	);

	backDrop = true;
}

LoadingScreen::LoadingScreen()
{}

LoadingScreen::~LoadingScreen()
{
	std::cout << "LoadingScreen destroyed" << std::endl;
}

void LoadingScreen::Update()
{
	if (time < durationTime) time += Global.DeltaTime;

	UpdateState();
}

void LoadingScreen::UpdateState()
{
	if (animationManger.IsDone()) currentIndex++;

	if (currentIndex >= states.size()) currentIndex = 0;

	current = states[currentIndex];
	UpdateAnimation();
	if (!isEnd()) BreakLoop();
	else Loop();
}

void LoadingScreen::Draw()
{
	window.SetColor(0, 0, 0);
	window.Clear();

	window.blit(
		animationManger.animation.texture,
		pos,
		animationManger.getRect(),
		size
	);
	
}

bool LoadingScreen::isEnd()
{
	if (time < durationTime) return false;
	removeFromTree();
	return true;
}
