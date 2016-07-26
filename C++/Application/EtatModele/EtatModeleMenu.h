//////////////////////////////////////////////////////////////////////////////
/// @file EtatModeleMenu.h
/// @author Najib Arbaoui
/// @date 2014-02-10
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __APPLICATION_ETATMODELEMENU_H__
#define __APPLICATION_ETATMODELEMENU_H__

#include "EtatModele\EtatModeleAbstrait.h"

class EtatModeleMenu : public EtatModeleAbstrait
{
public:
	EtatModeleMenu();
	
	virtual void mouseMoved(int x, int y, bool ctrlPressed, bool atlPressed);
	virtual void mousePressed(int x, int y, int button, bool ctrlPressed, bool atlPressed);
	virtual void mouseClicked(int x, int y, int button, bool ctrlPressed, bool atlPressed);
	virtual void mouseDragged(int x, int y, int dx, int dy, bool ctrlPressed, bool atlPressed);
	virtual void mouseReleased(int x, int y, int button, bool ctrlPressed, bool atlPressed);

	virtual void buttonPressed(string action);
};

#endif // __APPLICATION_ETATMODELEMENU_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
