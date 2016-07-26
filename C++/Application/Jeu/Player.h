//////////////////////////////////////////////////////////////////////////////
/// @file Player.h
/// @author Najib Arbaoui
/// @date 2014-03-04
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef __APPLICATION_JEU_PLAYER_H__
#define __APPLICATION_JEU_PLAYER_H__

#include "PlayerActionState.h"
#include "NoeudVaisseau.h"
#include "Controller\Controller.h"

class Player
{
private:
	NoeudVaisseau* vaisseau_;
	Controller* controller_;

	bool human_;
	int id_;
	float tempsDernierTir_;

public:
	Player(int id, bool human);
	~Player();

	void assignerTouches(int boutonAccelerer, int boutonVirage180, int boutonGauche, int boutonDroite, int boutonTirer);
	void touchesParDefaut();

	void update(float temps);
	void keyPressed(int keyCode);
	void keyReleased(int keyCode);

	PlayerActionState* getPlayerActionState();
	NoeudVaisseau* getVaisseau();
};

#endif // __APPLICATION_JEU_PLAYER_H__

//////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////