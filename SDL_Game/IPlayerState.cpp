#include "IPlayerState.h"
#include "Input.h"

IPlayerState* IdleState::Update(Player& player)
{
    player.current = Idle;

	if (!player.isOnGround)
		return new FallState();

	if (player.velocity.y < 0) {
		return new JumpState();
	}
		
	if (player.velocity.x != 0) return new RunState();

    return this;
}

IPlayerState* RunState::Update(Player& player)
{
    player.current = Run;

	if (!player.isOnGround)
		return new FallState();

	if (player.velocity.y < 0) {
		return new JumpState();
	}

	if (player.velocity.x == 0) return new IdleState();

    return this;
}

IPlayerState* FallState::Update(Player& player)
{
	player.current = Fall;

	if (player.isOnGround) {
		if (player.velocity.x != 0) return new RunState();
		return new IdleState();
	}

	return this;
}

IPlayerState* JumpState::Update(Player& player)
{
	player.current = Jump;

	if (player.velocity.y >= 0) return new FallState();

	return this;
}
