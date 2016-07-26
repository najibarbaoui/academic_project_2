//////////////////////////////////////////////////////////////////////////////
/// @file EtatModeleCampagne.h
/// @author Olivier Cotte
/// @date 2014-03-23
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __APPLICATION_ETATMODELECAMPAGNE_H__
#define __APPLICATION_ETATMODELECAMPAGNE_H__

#include <map>

#include "ArbreRenduINF2990.h"

#include "EtatModele\EtatModeleAbstrait.h"

class EtatModeleCampagne : public EtatModeleAbstrait
{
protected:
	
	std::map<string, EtatActionPartie> m_mapInstance;
	
public:
	EtatModeleCampagne();

	virtual void mouseMoved(int x, int y, bool ctrlPressed, bool altPressed) {}
	virtual void mousePressed(int x, int y, int button, bool ctrlPressed, bool altPressed) {}
	virtual void mouseClicked(int x, int y, int button, bool ctrlPressed, bool altPressed) {}
	virtual void mouseDragged(int x, int y, int dx, int dy, bool ctrlPressed, bool altPressed) {}
	virtual void mouseReleased(int x, int y, int button, bool ctrlPressed, bool altPressed) {}
	
	virtual void buttonPressed(string action);
};

#endif // __APPLICATION_ETATMODELECAMPAGNE_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
