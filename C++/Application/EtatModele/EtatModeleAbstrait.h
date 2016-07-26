//////////////////////////////////////////////////////////////////////////////
/// @file EtatModeleAbstrait.h
/// @author Najib Arbaoui
/// @date 2014-01-31
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __APPLICATION_ETATMODELEABSTRAIT_H__
#define __APPLICATION_ETATMODELEABSTRAIT_H__

#include "FacadeModele.h"
#include "EtatAction\EtatActionAbstrait.h"

#include <iostream>

using namespace std;

enum EtatId {
 
	ETATMENU = 0, ETATEDITEUR, ETATJEU, ETATCONFIGURATION, ETATMODETEST, ETATPARTIERAPIDE, ETATCAMPAGNE
};

enum BoutonSouris {
	BOUTONGAUCHE = 1, BOUTONDROIT = 3
};

enum EtatActionPartie{
	SOLO, COOPERATIVE, HUMAIN, VIRTUEL, VALIDER
};
class EtatModeleAbstrait {
protected:
	int etatId_;
	bool m_bDrawScene; // Il ne faut pas dessiner la sc�ene lorsque l'on rend le rectangle �lastique
	bool m_bAltPressed;
public:
	virtual int getEtatId();
	virtual bool DoWeDrawScene() const;

	virtual void mouseMoved(int x, int y, bool ctrlPressed, bool altPressed) = 0;
	virtual void mousePressed(int x, int y, int button, bool ctrlPressed, bool altPressed) = 0;
	virtual void mouseClicked(int x, int y, int button, bool ctrlPressed, bool altPressed) = 0;
	virtual void mouseDragged(int x, int y, int dx, int dy, bool ctrlPressed, bool altPressed) = 0;
	virtual void mouseReleased(int x, int y, int button, bool ctrlPressed, bool altPressed) = 0;
	
	virtual void buttonPressed(string action) = 0;
};

#endif // __APPLICATION_ETATMODELEABSTRAIT_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
