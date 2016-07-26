//////////////////////////////////////////////////////////////////////////////
/// @file EtatModeleEditeur.h
/// @author Najib Arbaoui
/// @date 2014-03-12
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __APPLICATION_ETATMODELEMODETEST_H__
#define __APPLICATION_ETATMODELEMODETEST_H__

#include <map>

#include "ArbreRenduINF2990.h"

#include "EtatModele\EtatModeleAbstrait.h"


class EtatModeleModeTest : public EtatModeleAbstrait
{
protected:
	// Le bouton enfonc�e lorsque l'�v�nement de souris a �t� commenc�e
	int button_;

	int lastDragX;
	int lastDragY;
public:
	EtatModeleModeTest();
	
	virtual void mouseMoved(int x, int y, bool ctrlPressed, bool altPressed);
	virtual void mousePressed(int x, int y, int button, bool ctrlPressed, bool altPressed);
	virtual void mouseClicked(int x, int y, int button, bool ctrlPressed, bool altPressed);
	virtual void mouseDragged(int x, int y, int dx, int dy, bool ctrlPressed, bool altPressed);
	virtual void mouseReleased(int x, int y, int button, bool ctrlPressed, bool altPressed);
	
	virtual void buttonPressed(string action);

	//virtual int getEtatActionId();
};

#endif // __APPLICATION_ETATMODELEMODETEST_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
