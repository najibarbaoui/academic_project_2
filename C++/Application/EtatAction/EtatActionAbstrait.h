//////////////////////////////////////////////////////////////////////////////
/// @file EtatActionAbstrait.h
/// @author Najib Arbaoui
/// @date 2014-02-04
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __APPLICATION_ETATACTIONABSTRAIT_H__
#define __APPLICATION_ETATACTIONABSTRAIT_H__

#include "FacadeModele.h"

using namespace std;

enum EtatActionId {
	PARDEFAUT = -1, SELECTION, DEPLACEMENT, ROTATION, MISEAECHELLE,
	DUPLICATION, ZOOM, AJOUTERNOEUDSTATIONSPATIALE, AJOUTERNOEUDBONUSACCELERATEUR,
	AJOUTERNOEUDBARRIEREPROTECTRICE, AJOUTERNOEUDPORTAIL, RECTANGLE_ELASTIQUE, MODETEST
};

class EtatActionAbstrait {
protected:
	int id_;
	bool utiliseRectangleElastique_;
	int compteClique_;
public:
	EtatActionAbstrait();

	virtual void Activer() = 0;
	virtual void Desactiver() = 0;

	virtual int getEtatActionId();
	virtual bool getUtiliseRectangleElastique();
	virtual int getCompteClique();
	
	virtual void mouseMoved(int x, int y, bool ctrlPressed, bool altPressed) = 0;
	virtual void mousePressed(int x, int y, int button, bool ctrlPressed, bool altPressed) = 0;
	virtual void mouseClicked(int x, int y, int button, bool ctrlPressed, bool altPressed) = 0;
	virtual void mouseDragged(int x, int y, int dx, int dy, bool ctrlPressed, bool altPressed) = 0;
	virtual void mouseReleased(int x, int y, int button, bool ctrlPressed, bool altPressed) = 0;

	virtual void buttonPressed(string action) = 0;
};

#endif // __APPLICATION_ETATACTIONABSTRAIT_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
