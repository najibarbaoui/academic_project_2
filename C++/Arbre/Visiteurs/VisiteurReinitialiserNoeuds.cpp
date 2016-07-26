///////////////////////////////////////////////////////////////////////////
/// @file VisiteurReinitialiserNoeuds.cpp
/// @author Najib Arbaoui
/// @date 2014-03-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "VisiteurReinitialiserNoeuds.h"

VisiteurReinitialiserNoeuds::VisiteurReinitialiserNoeuds()
{
}

VisiteurReinitialiserNoeuds::~VisiteurReinitialiserNoeuds()
{
}

void VisiteurReinitialiserNoeuds::reinitialiser(NoeudAbstrait& noeudAbstrait)
{
	noeudAbstrait.reinitialiser();
}

void VisiteurReinitialiserNoeuds::visiter(NoeudAbstrait& noeudAbstrait)
{
}

void VisiteurReinitialiserNoeuds::visiter(NoeudComposite& noeudComposite)
{
	for(unsigned int i = 0; i < noeudComposite.obtenirNombreEnfants(); ++i)
	{
		noeudComposite.chercher(i)->accepter(*this);
	}
}

void VisiteurReinitialiserNoeuds::visiter(NoeudAsteroide & noeudAsteroide)
{
	reinitialiser(noeudAsteroide);
}

void VisiteurReinitialiserNoeuds::visiter(NoeudBarriereProtectrice & noeudBarriereProtectrice)
{
	reinitialiser(noeudBarriereProtectrice);
}

void VisiteurReinitialiserNoeuds::visiter(NoeudBonusAccelerateur & noeudBonusAccelerateur )
{
	reinitialiser(noeudBonusAccelerateur);
}

void VisiteurReinitialiserNoeuds::visiter(NoeudPortail & noeudPortail)
{			
	reinitialiser(noeudPortail);
}

void VisiteurReinitialiserNoeuds::visiter(NoeudPositionDepart & noeudPositionDepart )
{
	reinitialiser(noeudPositionDepart);
}

void VisiteurReinitialiserNoeuds::visiter(NoeudProjectile & noeudProjectile ) 
{
	reinitialiser(noeudProjectile);
}

void VisiteurReinitialiserNoeuds::visiter(NoeudStationSpatiale & noeudStationSpatiale)
{
	reinitialiser(noeudStationSpatiale);
}

void VisiteurReinitialiserNoeuds::visiter(NoeudVaisseau & noeudVaisseau)
{
	reinitialiser(noeudVaisseau);
}

void VisiteurReinitialiserNoeuds::visiter(NoeudZoneJeu & noeudZoneJeu )
{
	reinitialiser(noeudZoneJeu);
}

void VisiteurReinitialiserNoeuds::visiter(NoeudZonePassage & noeudZonePassage )
{
	reinitialiser(noeudZonePassage);
}
void VisiteurReinitialiserNoeuds::visiter(NoeudAnimation & noeudAnimation )
{

}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////