//////////////////////////////////////////////////////////////////////////////
/// @file EtatActionRectangleElastique.h
/// @author Olivier Cotte
/// @date 2014-02-06
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _ETATACTIONREACTANGLEELASTIQUE_H_
#define _ETATACTIONREACTANGLEELASTIQUE_H_

#include "EtatActionAbstrait.h"

#include "Vecteur.h"
#include "FacadeModele.h"
#include "Vue.h"
#include "AideGL.h"

class EtatActionRectangleElastique : public EtatActionAbstrait 
{
public:
	EtatActionRectangleElastique();

	virtual void mousePressed(int x, int y, int button, bool ctrlPressed);
	virtual void mouseReleased(int x, int y, int button, bool ctrlPressed);
	virtual void mouseDragged(int x, int y, int dx, int dy, bool ctrlPressed);

	virtual void buttonPressed(string action);

private:
	int m_iLastX, m_iLastY;
	int m_iAncrageX, m_iAncrageY;
};

#endif // _ETATACTIONREACTANGLEELASTIQUE_H_

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////