///////////////////////////////////////////////////////////////////////////
/// @file VisiteurAIChercheCible.cpp
/// @author Najib Arbaoui
/// @date 2014-03-24
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "VisiteurAIChercheCible.h"

#include "ArbreRenduINF2990.h"
#include "FacadeModele.h"

VisiteurAIChercheCible::VisiteurAIChercheCible(NoeudVaisseau* noeud)
{
	vaisseau_ = noeud;
	cible_ = NULL;
}

VisiteurAIChercheCible::~VisiteurAIChercheCible()
{
}

NoeudAsteroide* VisiteurAIChercheCible::obtenirCible()
{
	return cible_;
}

void VisiteurAIChercheCible::visiter(NoeudAbstrait& noeudAbstrait)
{
}

void VisiteurAIChercheCible::visiter(NoeudComposite& noeudComposite)
{
	for(unsigned int i = 0; i < noeudComposite.obtenirNombreEnfants(); ++i)
	{
		noeudComposite.chercher(i)->accepter(*this);
	}
}

void VisiteurAIChercheCible::visiter(NoeudAsteroide & noeudAsteroide)
{
	Vecteur3 minXY, maxXY;
	noeudAsteroide.obtenirBoiteEnglobante(minXY, maxXY);

	if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->estDansZoneJeu(minXY, maxXY))
	{
		if (cible_ == NULL)
		{
			cible_ = &noeudAsteroide;
			distanceCible_ = (vaisseau_->obtenirPositionRelative() - cible_->obtenirPositionRelative()).norme();
		}
		else
		{
			double nouvelleDistance = (vaisseau_->obtenirPositionRelative() - noeudAsteroide.obtenirPositionRelative()).norme();
			if (nouvelleDistance < distanceCible_)
			{
				cible_ = &noeudAsteroide;
				distanceCible_ = nouvelleDistance;
			}
		}
	}
}

void VisiteurAIChercheCible::visiter(NoeudBarriereProtectrice & noeudBarriereProtectrice)
{
}

void VisiteurAIChercheCible::visiter(NoeudBonusAccelerateur & noeudBonusAccelerateur )
{
}

void VisiteurAIChercheCible::visiter(NoeudPortail & noeudPortail)
{		
}

void VisiteurAIChercheCible::visiter(NoeudPositionDepart & noeudPositionDepart )
{
}

void VisiteurAIChercheCible::visiter(NoeudProjectile & noeudProjectile ) 
{
}

void VisiteurAIChercheCible::visiter(NoeudStationSpatiale & noeudStationSpatiale)
{
}

void VisiteurAIChercheCible::visiter(NoeudVaisseau & noeudVaisseau)
{
}

void VisiteurAIChercheCible::visiter(NoeudZoneJeu & noeudZoneJeu )
{
}

void VisiteurAIChercheCible::visiter(NoeudZonePassage & noeudZonePassage )
{
}
void VisiteurAIChercheCible::visiter(NoeudAnimation & noeudAnimation )
{

}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////