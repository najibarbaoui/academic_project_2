//////////////////////////////////////////////////////////////////////////////
/// @file PlayerController.cpp
/// @author Najib Arbaoui
/// @date 2014-03-24
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#include "PlayerController.h"

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::update(float temps)
{
	// Rien � updater
}

void PlayerController::keyPressed(int keyCode)
{
	if (keyCode == bAccelerer_)
	{
		actionState_.setActionState(ACCELERER, true);
	}
	else if (keyCode == bVirage180_)
	{
		actionState_.setActionState(DEMITOUR, true);
	}
	else if (keyCode == bGauche_)
	{
		actionState_.setActionState(GAUCHE, true);
	}
	else if (keyCode == bDroite_)
	{
		actionState_.setActionState(DROITE, true);
	}
	else if (keyCode == bTirer_)
	{
		actionState_.setActionState(TIRER, true);
	}
}

void PlayerController::keyReleased(int keyCode)
{
	if (keyCode == bAccelerer_)
	{
		actionState_.setActionState(ACCELERER, false);
	}
	else if (keyCode == bGauche_)
	{
		actionState_.setActionState(GAUCHE, false);
	}
	else if (keyCode == bDroite_)
	{
		actionState_.setActionState(DROITE, false);
	}
	else if (keyCode == bTirer_)
	{
		actionState_.setActionState(TIRER, false);
	}
}

bool PlayerController::getCommand(PlayerAction action)
{
	bool commandResult = actionState_.getActionState(action);

	// On traite le demi-tour pour un seul frame
	if (action == DEMITOUR && actionState_.getActionState(DEMITOUR))
	{
		actionState_.setActionState(DEMITOUR, false);
	}

	return commandResult;
}

//////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////