///////////////////////////////////////////////////////////////////////////
/// @file VisiteurBonusAcceleration.cpp
/// @author Najib Arbaoui
/// @date 2014-03-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "VisiteurBonusAcceleration.h"
#include "GestionnaireAudio.h"
#include "Utilitaire.h"

VisiteurBonusAcceleration::VisiteurBonusAcceleration(NoeudBonusAccelerateur* noeud)
{
	noeudBonusAccelerateur = noeud;
}

VisiteurBonusAcceleration::~VisiteurBonusAcceleration()
{
}

void VisiteurBonusAcceleration::appliquerBonusAcceleration(NoeudVaisseau &noeud)
{
	// V�rifier collision
	Vecteur3 minXY, maxXY, vaisseauMinXY, vaisseauMaxXY;
	this->noeudBonusAccelerateur->obtenirBoiteEnglobante(minXY, maxXY);
	noeud.obtenirBoiteEnglobante(vaisseauMinXY, vaisseauMaxXY);

	if (utilitaire::AABB_COLLISION(vaisseauMinXY, vaisseauMaxXY, minXY, maxXY))
	{
		this->noeudBonusAccelerateur->disable();
		noeud.appliquerBonusAcceleration();
		// jouer le son de bonusAccelerateur
		GestionnaireAudio::obtenirInstance()->jouerAudioActivationBonusAccelerateur();
	}
}

void VisiteurBonusAcceleration::visiter(NoeudAbstrait& noeudAbstrait)
{
}

void VisiteurBonusAcceleration::visiter(NoeudComposite& noeudComposite)
{
	for(unsigned int i = 0; i < noeudComposite.obtenirNombreEnfants(); ++i)
	{
		noeudComposite.chercher(i)->accepter(*this);
	}
}

void VisiteurBonusAcceleration::visiter(NoeudAsteroide & noeudAsteroide)
{
}

void VisiteurBonusAcceleration::visiter(NoeudBarriereProtectrice & noeudBarriereProtectrice)
{
}

void VisiteurBonusAcceleration::visiter(NoeudBonusAccelerateur & noeudBonusAccelerateur )
{
}

void VisiteurBonusAcceleration::visiter(NoeudPortail & noeudPortail)
{			
}

void VisiteurBonusAcceleration::visiter(NoeudPositionDepart & noeudPositionDepart )
{
}

void VisiteurBonusAcceleration::visiter(NoeudProjectile & noeudProjectile ) 
{
}

void VisiteurBonusAcceleration::visiter(NoeudStationSpatiale & noeudStationSpatiale)
{
}

void VisiteurBonusAcceleration::visiter(NoeudVaisseau & noeudVaisseau)
{
	appliquerBonusAcceleration(noeudVaisseau);
}

void VisiteurBonusAcceleration::visiter(NoeudZoneJeu & noeudZoneJeu )
{
}

void VisiteurBonusAcceleration::visiter(NoeudZonePassage & noeudZonePassage )
{
}

void VisiteurBonusAcceleration::visiter(NoeudAnimation & noeudAnimation )
{

}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////