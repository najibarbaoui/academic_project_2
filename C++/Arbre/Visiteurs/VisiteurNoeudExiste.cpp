///////////////////////////////////////////////////////////////////////////
/// @file VisiteurNoeudExiste.cpp
/// @author Najib Arbaoui
/// @date 2014-03-24
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "VisiteurNoeudExiste.h"

VisiteurNoeudExiste::VisiteurNoeudExiste(NoeudAbstrait* noeudATester)
{
	noeudATester_ = noeudATester;
	existe_ = false;
}

VisiteurNoeudExiste::~VisiteurNoeudExiste()
{
}

bool VisiteurNoeudExiste::obtenirExiste()
{
	return existe_;
}

void VisiteurNoeudExiste::testeNoeud(NoeudAbstrait* noeudAbstrait)
{
	if (noeudATester_ == noeudAbstrait)
	{
		existe_ = true;
	}
}

void VisiteurNoeudExiste::visiter(NoeudAbstrait& noeudAbstrait)
{
	this->testeNoeud(&noeudAbstrait);
}

void VisiteurNoeudExiste::visiter(NoeudComposite& noeudComposite)
{
	for(unsigned int i = 0; i < noeudComposite.obtenirNombreEnfants(); ++i)
	{
		noeudComposite.chercher(i)->accepter(*this);
	}

	this->testeNoeud(&noeudComposite);
}

void VisiteurNoeudExiste::visiter(NoeudAsteroide & noeudAsteroide)
{
	this->testeNoeud(&noeudAsteroide);
}

void VisiteurNoeudExiste::visiter(NoeudBarriereProtectrice & noeudBarriereProtectrice)
{
	this->testeNoeud(&noeudBarriereProtectrice);
}

void VisiteurNoeudExiste::visiter(NoeudBonusAccelerateur & noeudBonusAccelerateur )
{
	this->testeNoeud(&noeudBonusAccelerateur);
}

void VisiteurNoeudExiste::visiter(NoeudPortail & noeudPortail)
{		
	this->testeNoeud(&noeudPortail);
}

void VisiteurNoeudExiste::visiter(NoeudPositionDepart & noeudPositionDepart )
{
	this->testeNoeud(&noeudPositionDepart);
}

void VisiteurNoeudExiste::visiter(NoeudProjectile & noeudProjectile ) 
{
	this->testeNoeud(&noeudProjectile);
}

void VisiteurNoeudExiste::visiter(NoeudStationSpatiale & noeudStationSpatiale)
{
	this->testeNoeud(&noeudStationSpatiale);
}

void VisiteurNoeudExiste::visiter(NoeudVaisseau & noeudVaisseau)
{
	this->testeNoeud(&noeudVaisseau);
}

void VisiteurNoeudExiste::visiter(NoeudZoneJeu & noeudZoneJeu )
{
	this->testeNoeud(&noeudZoneJeu);
}

void VisiteurNoeudExiste::visiter(NoeudZonePassage & noeudZonePassage )
{
	this->testeNoeud(&noeudZonePassage);
}

 void VisiteurNoeudExiste::visiter(NoeudAnimation & noeudAnimation )
{

}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////