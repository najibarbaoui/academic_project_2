///////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.cpp
/// @author Najib Arbaoui
/// @date 2014-01-31
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "EtatModeleEditeur.h"

#include "EtatAction\EtatActionParDefaut.h"
#include "EtatAction\EtatActionDeplacement.h"
#include "EtatAction\EtatActionSelection.h"
#include "EtatAction\EtatActionRotation.h"
#include "EtatAction\EtatActionMiseAEchelle.h"
#include "EtatAction\EtatActionDuplication.h"
#include "EtatAction\EtatActionZoom.h"
#include "EtatAction\EtatActionMiseAEchelle.h"
#include "EtatAction\EtatActionAjouterStationSpatiale.h"
#include "EtatAction\EtatActionAjouterBonusAccelerateur.h"
#include "EtatAction\EtatActionAjouterBarriereProtectrice.h"
#include "EtatAction\EtatActionAjouterPortail.h"
#include "EtatAction\EtatActionModeTest.h"

EtatModeleEditeur::EtatModeleEditeur() 
{
	this->etatId_ = ETATEDITEUR;
	this->m_bDrawScene = true;
	this->m_bAltPressed = false;

	indexMap.insert(pair<string, int>("Par D�faut", PARDEFAUT));
	indexMap.insert(pair<string, int>("S�lection", SELECTION));
	indexMap.insert(pair<string, int>("D�placement", DEPLACEMENT));
	indexMap.insert(pair<string, int>("Rotation", ROTATION));
	indexMap.insert(pair<string, int>("Mise � l'�chelle", MISEAECHELLE));
	indexMap.insert(pair<string, int>("Duplication", DUPLICATION));
	indexMap.insert(pair<string, int>("Zoom", ZOOM));
	indexMap.insert(pair<string, int>("Ajouter Noeud: stationSpatiale", AJOUTERNOEUDSTATIONSPATIALE));
	indexMap.insert(pair<string, int>("Ajouter Noeud: bonusAccelerateur", AJOUTERNOEUDBONUSACCELERATEUR));
	indexMap.insert(pair<string, int>("Ajouter Noeud: barriereProtectrice", AJOUTERNOEUDBARRIEREPROTECTRICE));
	indexMap.insert(pair<string, int>("Ajouter Noeud: portail", AJOUTERNOEUDPORTAIL));
	indexMap.insert(pair<string, int>("Mode test", MODETEST));

	m_mapInstance.insert(pair<EtatActionId, std::shared_ptr<EtatActionAbstrait> >(PARDEFAUT,			new EtatActionParDefaut()));
	m_mapInstance.insert(pair<EtatActionId, std::shared_ptr<EtatActionAbstrait> >(SELECTION,			new EtatActionSelection()));
	m_mapInstance.insert(pair<EtatActionId, std::shared_ptr<EtatActionAbstrait> >(DEPLACEMENT,			new EtatActionDeplacement()));
	m_mapInstance.insert(pair<EtatActionId, std::shared_ptr<EtatActionAbstrait> >(ROTATION,				new EtatActionRotation()));
	m_mapInstance.insert(pair<EtatActionId, std::shared_ptr<EtatActionAbstrait> >(MISEAECHELLE,			new EtatActionMiseAEchelle()));
	m_mapInstance.insert(pair<EtatActionId, std::shared_ptr<EtatActionAbstrait> >(DUPLICATION,			new EtatActionDuplication()));
	m_mapInstance.insert(pair<EtatActionId, std::shared_ptr<EtatActionAbstrait> >(ZOOM,					new EtatActionZoom()));
	m_mapInstance.insert(pair<EtatActionId, std::shared_ptr<EtatActionAbstrait> >(AJOUTERNOEUDSTATIONSPATIALE,		new EtatActionAjouterStationSpatiale()));
	m_mapInstance.insert(pair<EtatActionId, std::shared_ptr<EtatActionAbstrait> >(AJOUTERNOEUDBONUSACCELERATEUR,	new EtatActionAjouterBonusAccelerateur()));
	m_mapInstance.insert(pair<EtatActionId, std::shared_ptr<EtatActionAbstrait> >(AJOUTERNOEUDBARRIEREPROTECTRICE,	new EtatActionAjouterBarriereProtectrice()));
	m_mapInstance.insert(pair<EtatActionId, std::shared_ptr<EtatActionAbstrait> >(AJOUTERNOEUDPORTAIL,			new EtatActionAjouterPortail()));
	m_mapInstance.insert(pair<EtatActionId, std::shared_ptr<EtatActionAbstrait> >(MODETEST,			new EtatActionModeTest()));

	// �tat de d�part : par d�faut
	this->etatAction = m_mapInstance[PARDEFAUT];
}

void EtatModeleEditeur::mouseMoved(int x, int y, bool ctrlPressed, bool altPressed)
{
	this->etatAction->mouseMoved(x, y, ctrlPressed, altPressed);
}

void EtatModeleEditeur::mousePressed(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
	button_ = button;
		
	// Clique gauche
	if (button_ == BOUTONGAUCHE)
	{
		this->etatAction->mousePressed(x, y, button, ctrlPressed,altPressed);
	}
	else if (button_ == BOUTONDROIT)
	{
		lastDragX = x;
		lastDragY = y;
	}
}

void EtatModeleEditeur::mouseClicked(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
	// Clique gauche
	if (button_ == BOUTONGAUCHE)
	{
		this->etatAction->mouseClicked(x, y, button, ctrlPressed, altPressed);
	}
}

void EtatModeleEditeur::mouseDragged(int x, int y, int dx, int dy, bool ctrlPressed, bool altPressed)
{
	// Clique gauche
	if (button_ == BOUTONGAUCHE)
	{
		if (this->etatAction->getUtiliseRectangleElastique() && (abs(dx) >= 3 && abs(dy) >= 3)) {
			if (!m_bDrawScene && (abs(dx) < 3 || abs(dy) < 3)) {
				_terminerRectangleElastique(x, y);
				m_bAltPressed = false;
			} else if (m_bDrawScene && (abs(dx) >= 3 && abs(dy) >= 3)) {
				_initialiserRectangleElastique(x, y);
				m_bAltPressed = altPressed;
			} else if (abs(dx) >= 3 && abs(dy) >= 3) {
				_mettreAJourRectangleElastique(x, y);
			}
		}

		this->etatAction->mouseDragged(x, y, dx, dy, ctrlPressed, altPressed);
	}
	// Clique droit
	else if (button_ == BOUTONDROIT)
	{
		FacadeModele::obtenirInstance()->obtenirVue()->deplacerCamera(x, y, lastDragX, lastDragY);

		lastDragX = x;
		lastDragY = y;
	}
}

void EtatModeleEditeur::mouseReleased(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
	// Clique gauche
	if (button_ == BOUTONGAUCHE)
	{
		if (this->etatAction->getUtiliseRectangleElastique()) {
			if (!m_bDrawScene) {
				_terminerRectangleElastique(x, y);
				if(etatAction->getEtatActionId() == ZOOM) {
					Vecteur3 pointAncrage3, pointFinal3;
					FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(m_iAncrageX, m_iAncrageY, pointAncrage3);
					FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(m_iPointFinalX, m_iPointFinalY, pointFinal3);
					Vecteur2i pointAncrage2(static_cast<int>(pointAncrage3[0]), static_cast<int>(pointAncrage3[1]));
					Vecteur2i pointFinal2(static_cast<int>(pointFinal3[0]), static_cast<int>(pointFinal3[1]));
					if(m_bAltPressed) { // Zoom out
						FacadeModele::obtenirInstance()->obtenirVue()->zoomerOutElastique(pointAncrage2, pointFinal2);
						m_bAltPressed = false;
					} else { // Zoom in
						FacadeModele::obtenirInstance()->obtenirVue()->zoomerInElastique(pointAncrage2, pointFinal2);
					}
				}
			}
		}

		this->etatAction->mouseReleased(x, y, button, ctrlPressed, altPressed);
	}
}

void EtatModeleEditeur::_initialiserRectangleElastique(int pointAncrageX, int pointAncrageY)
{
	m_bDrawScene = false;

	Vecteur2i pointAncrage2(pointAncrageX, pointAncrageY);
	aidegl::initialiserRectangleElastique(pointAncrage2);

	m_iLastX = m_iAncrageX = pointAncrageX;
	m_iLastY = m_iAncrageY = pointAncrageY;
}

void EtatModeleEditeur::_mettreAJourRectangleElastique(int pointApresX, int pointApresY)
{
	Vecteur2i pointAncrage2(m_iAncrageX, m_iAncrageY);
	Vecteur2i pointAvant2(m_iLastX, m_iLastY);
	Vecteur2i pointFinal2(pointApresX, pointApresY);

	aidegl::mettreAJourRectangleElastique(pointAncrage2, pointAvant2, pointFinal2);

	m_iLastX = pointApresX; m_iLastY = pointApresY;
}

void EtatModeleEditeur::_terminerRectangleElastique(int pointFinalX, int pointFinalY)
{
	m_bDrawScene = true;

	Vecteur2i pointAncrage2(m_iAncrageX, m_iAncrageY);
	Vecteur2i pointFinal2(pointFinalX, pointFinalY);

	aidegl::terminerRectangleElastique(pointAncrage2, pointFinal2);

	m_iPointFinalX = pointFinalX;
	m_iPointFinalY = pointFinalY;
}

void EtatModeleEditeur::buttonPressed(string action)
{
	if(action == "Changer vue: Mode test")
	{
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getNoeudPositionDeDepart1()->assignerAffiche(false);
	}
	if (action == "Supprimer")
	{
		FacadeModele::obtenirInstance()->supprimerNoeudSelectione();
	}
	else if (action == "Escape")
	{
		// Si le compte clique est z�ro, on quitte l'�tat action courant
		if (etatAction->getCompteClique() == 0)
		{
			// Desactiver l'�tat courant. Pas besoin d'appeler Activer() pour l'�tat PARDEFAUT
			this->etatAction->Desactiver();
			this->etatAction = m_mapInstance[PARDEFAUT];
		}
		// Sinon on annule le clique de l'�tat action
		else
		{
			this->etatAction->buttonPressed("Annuler");
		}
	}
	// Regarde si l'action est reconnu (Est contenu dans le map)
	else if (indexMap.find(action) == indexMap.end())
	{
		this->etatAction->buttonPressed(action);
	}
	// Regarde si l'�tat courant est d�j� celui demand�
	else if (this->etatAction->getEtatActionId() == indexMap.at(action))
	{
		// Desactiver l'�tat courant. Pas besoin d'appeler Activer() pour l'�tat PARDEFAUT
		this->etatAction->Desactiver();
		this->etatAction = m_mapInstance[PARDEFAUT];
	}
	else
	{
		this->etatAction->Desactiver();
		std::map<EtatActionId, std::shared_ptr<EtatActionAbstrait> >::const_iterator it;
		EtatActionId actionId = (EtatActionId)indexMap[action];
		it = m_mapInstance.find(actionId);
		if(it != m_mapInstance.end()) {
			this->etatAction = it->second;
			// Activer l'�tat
			this->etatAction->Activer();
		}
	}
}

int EtatModeleEditeur::getEtatActionId()
{
	return this->etatAction->getEtatActionId();
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////