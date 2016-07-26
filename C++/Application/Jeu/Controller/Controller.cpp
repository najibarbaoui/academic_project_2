//////////////////////////////////////////////////////////////////////////////
/// @file Controller.cpp
/// @author Najib Arbaoui
/// @date 2014-03-24
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#include "Controller.h"

Controller::Controller()
{
}

Controller::~Controller()
{
}

void Controller::assignerTouches(int boutonAccelerer, int boutonVirage180, int boutonGauche, int boutonDroite, int boutonTirer)
{
	bAccelerer_ = boutonAccelerer;
	bVirage180_ = boutonVirage180;
	bGauche_ = boutonGauche;
	bDroite_ = boutonDroite;
	bTirer_ = boutonTirer;
}

PlayerActionState* Controller::getActionState()
{
	return &actionState_;
}

//////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////