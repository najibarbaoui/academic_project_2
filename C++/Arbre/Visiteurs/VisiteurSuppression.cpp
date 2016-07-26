///////////////////////////////////////////////////////////////////////////
/// @file VisiteurSuppression.cpp
/// @author Najib Arbaoui
/// @date 2014-01-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "VisiteurSuppression.h"
#include "FacadeModele.h"
#include "Utilitaire.h"

///////////////////////////////////////////////////////////////////////////
/// @class  VisiteurSuppression
/// @brief Classe de visiteur qui permet de selectionner les noeuds d un arbre
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSuppression::VisiteurSuppression()
///
/// Constructeur par default
/// @param[in] :aucun
///
/// @return Aucune (constructeur).
///
//////////////////////////////////////////////////////////////////////////////////
VisiteurSuppression::VisiteurSuppression()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSuppression:: ~ VisiteurSuppression()
///
/// Destructeur par default
/// @param[in] :aucun
///
/// @return Aucune (destructeur).
///
//////////////////////////////////////////////////////////////////////////////////
VisiteurSuppression::~VisiteurSuppression()  
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSuppression::visiter( NoeudAsteroide& noeudAsteroide)
///
///  Fonction qui permet au visiteur d'acceder au noeudAsteroide et faire son traitement
///
/// @param[in]: NoeudAsteroide & noeudAsteroide
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void VisiteurSuppression::visiter(NoeudAsteroide & noeudAsteroide)
{
	SupprimerNoeudSelectione(noeudAsteroide);
}

void VisiteurSuppression::visiter(NoeudAbstrait & noeudAbstrait)
{
	SupprimerNoeudSelectione(noeudAbstrait);
}

void VisiteurSuppression::visiter(NoeudBarriereProtectrice & noeudBarriereProtectrice)
{
	SupprimerNoeudSelectione(noeudBarriereProtectrice);
}

void VisiteurSuppression::visiter(NoeudBonusAccelerateur & noeudBonusAccelerateur )
{
	SupprimerNoeudSelectione(noeudBonusAccelerateur);
}

void VisiteurSuppression:: visiter(NoeudComposite & noeudComposite)
{
	SupprimerNoeudSelectione(noeudComposite);
}

void VisiteurSuppression::visiter(NoeudPortail & noeudPortail)
{			
	SupprimerNoeudSelectione(noeudPortail);
}

void VisiteurSuppression::visiter(NoeudPositionDepart & noeudPositionDepart )
{
}

void VisiteurSuppression::visiter(NoeudProjectile & noeudProjectile ) 
{
	SupprimerNoeudSelectione(noeudProjectile);
}

void VisiteurSuppression::visiter(NoeudStationSpatiale & noeudStationSpatiale)
{
	SupprimerNoeudSelectione(noeudStationSpatiale);
}

void VisiteurSuppression::visiter(NoeudVaisseau & noeudVaisseau)
{
	SupprimerNoeudSelectione(noeudVaisseau);
}

void VisiteurSuppression::visiter(NoeudZoneJeu & noeudZoneJeu )
{
}

void VisiteurSuppression::visiter(NoeudZonePassage & noeudZonePassage )
{
	SupprimerNoeudSelectione(noeudZonePassage);
}

void VisiteurSuppression::SupprimerNoeudSelectione(NoeudAbstrait & noeudAbstrait)
{
	noeudAbstrait.obtenirParent()->effacerSelection();
}

 void VisiteurSuppression::visiter(NoeudAnimation & noeudAnimation )
{

}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
