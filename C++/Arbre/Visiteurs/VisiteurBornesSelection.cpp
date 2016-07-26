///////////////////////////////////////////////////////////////////////////
/// @file VisiteurBornesSelection.cpp
/// @author Najib Arbaoui et Najib
/// @date 2014-02-11
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "VisiteurBornesSelection.h"

VisiteurBornesSelection::VisiteurBornesSelection()
{
	auMoinsUnNoeudTraite = false;
}

VisiteurBornesSelection::~VisiteurBornesSelection()
{
}

void VisiteurBornesSelection::AjusterBornesSelection(NoeudAbstrait& noeudAbstrait)
{
	// Si le noeud est s�lectionn�
	if(noeudAbstrait.estSelectionne())
	{
		// Si aucun noeud n'a encore �t� trait�, on assigne directement le minXY et le maxXY � la boite englobante du noeud
		if(!auMoinsUnNoeudTraite)
		{
			noeudAbstrait.obtenirBoiteEnglobante(minXY_, maxXY_);

			auMoinsUnNoeudTraite = true;
		}
		// Tous les autres noeud seront compar�s pour obtenir la boite englobant tous les noeuds
		else
		{
			// On obtient la boite englobante du noeud que l'on traite
			Vecteur3 noeudMinXY, noeudMaxXY;
			noeudAbstrait.obtenirBoiteEnglobante(noeudMinXY, noeudMaxXY);

			// On trouve les extremums
			minXY_[0] = min(minXY_[0], noeudMinXY[0]);
			minXY_[1] = min(minXY_[1], noeudMinXY[1]);
			maxXY_[0] = max(maxXY_[0], noeudMaxXY[0]);
			maxXY_[1] = max(maxXY_[1], noeudMaxXY[1]);
		}
	}
}

void VisiteurBornesSelection::visiter(NoeudAbstrait& noeudAbstrait)
{
	AjusterBornesSelection(noeudAbstrait);
}

void VisiteurBornesSelection::visiter(NoeudComposite& noeudComposite)
{
	for(unsigned int i = 0; i < noeudComposite.obtenirNombreEnfants(); ++i)
	{
		noeudComposite.chercher(i)->accepter(*this);
	}

	AjusterBornesSelection(noeudComposite);
}

void VisiteurBornesSelection::visiter(NoeudAsteroide & noeudAsteroide)
{
	AjusterBornesSelection(noeudAsteroide);
}

void VisiteurBornesSelection::visiter(NoeudBarriereProtectrice & noeudBarriereProtectrice)
{
	AjusterBornesSelection(noeudBarriereProtectrice);
}

void VisiteurBornesSelection::visiter(NoeudBonusAccelerateur & noeudBonusAccelerateur )
{
	AjusterBornesSelection(noeudBonusAccelerateur);
}

void VisiteurBornesSelection::visiter(NoeudPortail & noeudPortail)
{			
	AjusterBornesSelection(noeudPortail);
}

void VisiteurBornesSelection::visiter(NoeudPositionDepart & noeudPositionDepart )
{
	AjusterBornesSelection(noeudPositionDepart);
}

void VisiteurBornesSelection::visiter(NoeudProjectile & noeudProjectile ) 
{
	AjusterBornesSelection(noeudProjectile);
}

void VisiteurBornesSelection::visiter(NoeudStationSpatiale & noeudStationSpatiale)
{
	AjusterBornesSelection(noeudStationSpatiale);
}

void VisiteurBornesSelection::visiter(NoeudVaisseau & noeudVaisseau)
{
	AjusterBornesSelection(noeudVaisseau);
}

void VisiteurBornesSelection::visiter(NoeudZoneJeu & noeudZoneJeu )
{
	AjusterBornesSelection(noeudZoneJeu);
}

void VisiteurBornesSelection::visiter(NoeudZonePassage & noeudZonePassage )
{
	AjusterBornesSelection(noeudZonePassage);
}

void VisiteurBornesSelection::getBornesSelection(Vecteur3 &minXY, Vecteur3 &maxXY)
{
	minXY = this->minXY_;
	maxXY = this->maxXY_;
}

void VisiteurBornesSelection::visiter(NoeudAnimation & noeudAnimation )
{

}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////