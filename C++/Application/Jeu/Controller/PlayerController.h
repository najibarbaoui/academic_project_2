//////////////////////////////////////////////////////////////////////////////
/// @file PlayerController.h
/// @author Najib Arbaoui
/// @date 2014-03-24
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef __APPLICATION_JEU_CONTROLLER_PLAYERCONTROLLER_H__
#define __APPLICATION_JEU_CONTROLLER_PLAYERCONTROLLER_H__

#include "Controller.h"

class PlayerController : public Controller
{
protected:

public:
	PlayerController();
	~PlayerController();
	
	virtual void update(float temps);
	virtual void keyPressed(int keyCode);
	virtual void keyReleased(int keyCode);

	virtual bool getCommand(PlayerAction action);
};

#endif // __APPLICATION_JEU_CONTROLLER_PLAYERCONTROLLER_H__

//////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////