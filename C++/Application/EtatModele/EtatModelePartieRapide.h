//////////////////////////////////////////////////////////////////////////////
/// @file EtatModelePartieRapide.h
/// @author Najib Arbaoui
/// @date 2014-03-20
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __APPLICATION_ETATMODELEPARTIERAPIDE_H__
#define __APPLICATION_ETATMODELEPARTIERAPIDE_H__

#include <map>

#include "ArbreRenduINF2990.h"

#include "EtatModele\EtatModeleAbstrait.h"

class EtatModelePartieRapide : public EtatModeleAbstrait
{
protected:
	std::map<string, EtatActionPartie> m_mapInstance;
	std::map<string, EtatActionPartie>::iterator it;
public:
	EtatModelePartieRapide();

	virtual void mouseMoved(int x, int y, bool ctrlPressed, bool altPressed);
	virtual void mousePressed(int x, int y, int button, bool ctrlPressed, bool altPressed);
	virtual void mouseClicked(int x, int y, int button, bool ctrlPressed, bool altPressed);
	virtual void mouseDragged(int x, int y, int dx, int dy, bool ctrlPressed, bool altPressed);
	virtual void mouseReleased(int x, int y, int button, bool ctrlPressed, bool altPressed);

	virtual void buttonPressed(string action);
};

#endif // __APPLICATION_ETATMODELEPARTIERAPIDE_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
