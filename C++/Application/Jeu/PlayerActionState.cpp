#include "PlayerActionState.h"

PlayerActionState::PlayerActionState()
{
	// Initialiser les états à faux
	for (int i=0; i<5; i++)
	{
		actionStates_[i] = false;
	}
}

bool PlayerActionState::getActionState(PlayerAction playerAction)
{
	return actionStates_[playerAction];
}

void PlayerActionState::setActionState(PlayerAction playerAction, bool value)
{
	actionStates_[playerAction] = value;
}