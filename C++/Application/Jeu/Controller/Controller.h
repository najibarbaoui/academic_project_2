//////////////////////////////////////////////////////////////////////////////
/// @file Controller.h
/// @author Najib Arbaoui
/// @date 2014-03-24
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef __APPLICATION_JEU_CONTROLLER_CONTROLLER_H__
#define __APPLICATION_JEU_CONTROLLER_CONTROLLER_H__

#include "..\PlayerActionState.h"

class Controller
{
protected:
	PlayerActionState actionState_;
	int bAccelerer_, bVirage180_, bGauche_, bDroite_, bTirer_;

public:
	Controller();
	~Controller();
	
	void assignerTouches(int boutonAccelerer, int boutonVirage180, int boutonGauche, int boutonDroite, int boutonTirer);
	PlayerActionState* getActionState();

	virtual void update(float temps) = 0;
	virtual void keyPressed(int keyCode) = 0;
	virtual void keyReleased(int keyCode) = 0;

	virtual bool getCommand(PlayerAction action) = 0;
};

#endif // __APPLICATION_JEU_CONTROLLER_CONTROLLER_H__

//////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////