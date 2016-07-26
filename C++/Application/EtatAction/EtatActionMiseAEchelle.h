///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
/// @file EtatActionMiseAEchelle.h
/// @author Najib Arbaoui
/// @date 2014-02-06
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __APPLICATION_ETATACTIONMISEAECHELLE_H__
#define __APPLICATION_ETATACTIONMISEAECHELLE_H__

#include "EtatActionAbstrait.h"

class EtatActionMiseAEchelle : public EtatActionAbstrait
{
protected:
	float lastScale;
public:
	EtatActionMiseAEchelle();
	
	virtual void Activer();
	virtual void Desactiver();

	virtual void mouseMoved(int x, int y, bool ctrlPressed, bool altPressed);
	virtual void mousePressed(int x, int y, int button, bool ctrlPressed, bool altPressed);
	virtual void mouseClicked(int x, int y, int button, bool ctrlPressed, bool altPressed);
	virtual void mouseDragged(int x, int y, int dx, int dy, bool ctrlPressed, bool altPressed);
	virtual void mouseReleased(int x, int y, int button, bool ctrlPressed, bool altPressed);

	virtual void buttonPressed(string action);
};

#endif // __APPLICATION_ETATACTIONMISEAECHELLE_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
