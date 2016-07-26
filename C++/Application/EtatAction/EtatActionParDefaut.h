///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
/// @file EtatActionParDefaut.h
/// @author Najib Arbaoui
/// @date 2014-02-04
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __APPLICATION_ETATACTIONPARDEFAUT_H__
#define __APPLICATION_ETATACTIONPARDEFAUT_H__

#include "EtatActionAbstrait.h"

class EtatActionParDefaut : public EtatActionAbstrait
{
public:
	EtatActionParDefaut();
	
	virtual void Activer();
	virtual void Desactiver();

	virtual void mouseMoved(int x, int y, bool ctrlPressed, bool altPressed);
	virtual void mousePressed(int x, int y, int button, bool ctrlPressed, bool altPressed);
	virtual void mouseClicked(int x, int y, int button, bool ctrlPressed, bool altPressed);
	virtual void mouseDragged(int x, int y, int dx, int dy, bool ctrlPressed, bool altPressed);
	virtual void mouseReleased(int x, int y, int button, bool ctrlPressed, bool altPressed);

	virtual void buttonPressed(string action);
};

#endif // __APPLICATION_ETATACTIONPARDEFAUT_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
