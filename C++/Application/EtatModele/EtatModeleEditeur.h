//////////////////////////////////////////////////////////////////////////////
/// @file EtatModeleEditeur.h
/// @author Najib Arbaoui
/// @date 2014-01-31
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __APPLICATION_ETATMODELEEDITEUR_H__
#define __APPLICATION_ETATMODELEEDITEUR_H__

#include <map>

#include "ArbreRenduINF2990.h"

#include "EtatModele\EtatModeleAbstrait.h"
#include "EtatAction\EtatActionRectangleElastique.h"

class EtatModeleEditeur : public EtatModeleAbstrait
{
protected:
	std::shared_ptr<EtatActionAbstrait> etatAction;
	map<string, int> indexMap;
	std::map<EtatActionId, std::shared_ptr<EtatActionAbstrait> > m_mapInstance;

	int m_iLastX, m_iLastY;
	int m_iAncrageX, m_iAncrageY;
	int m_iPointFinalX, m_iPointFinalY;

	int lastDragX;
	int lastDragY;
	
	// Le bouton enfonc�e lorsque l'�v�nement de souris a �t� commenc�e
	int button_;

	void _initialiserRectangleElastique(int pointAncrageX, int pointAncrageY);
	void _mettreAJourRectangleElastique(int pointApresX, int pointApresY);
	void _terminerRectangleElastique(int pointFinalX, int pointFinalY);
public:
	EtatModeleEditeur();
	
	virtual void mouseMoved(int x, int y, bool ctrlPressed, bool altPressed);
	virtual void mousePressed(int x, int y, int button, bool ctrlPressed, bool altPressed);
	virtual void mouseClicked(int x, int y, int button, bool ctrlPressed, bool altPressed);
	virtual void mouseDragged(int x, int y, int dx, int dy, bool ctrlPressed, bool altPressed);
	virtual void mouseReleased(int x, int y, int button, bool ctrlPressed, bool altPressed);
	
	virtual void buttonPressed(string action);

	virtual int getEtatActionId();
};

#endif // __APPLICATION_ETATMODELEEDITEUR_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
