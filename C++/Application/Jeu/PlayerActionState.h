//////////////////////////////////////////////////////////////////////////////
/// @file PlayerActionState.h
/// @author Najib Arbaoui
/// @date 2014-03-04
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef __APPLICATION_JEU_PLAYERACTIONSTATE_H__
#define __APPLICATION_JEU_PLAYERACTIONSTATE_H__

enum PlayerAction {
	ACCELERER, DEMITOUR, GAUCHE, DROITE, TIRER
};

class PlayerActionState
{
private:
	bool actionStates_[5];

public:
	PlayerActionState();

	bool getActionState(PlayerAction playerAction);
	void setActionState(PlayerAction playerAction, bool value);
};

#endif // __APPLICATION_JEU_PLAYERACTIONSTATE_H__

//////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////