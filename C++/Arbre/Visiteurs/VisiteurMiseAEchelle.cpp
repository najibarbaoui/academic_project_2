///////////////////////////////////////////////////////////////////////////
/// @file VisiteurSelection.cpp
/// @author Najib Arbaoui
/// @date 2014-01-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "VisiteurMiseAEchelle.h"
#include "ArbreRenduINF2990.h"
#include "FacadeModele.h"
///////////////////////////////////////////////////////////////////////////
/// @class  VisiteurDeplacement
/// @brief Classe de visiteur qui permet de deplacer les noeuds d un arbre
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAEchelle::VisiteurMiseAEchelle()
///
/// Constructeur par parametre
/// @param[in] :aucun
///
/// @return Aucune (constructeur).
///
//////////////////////////////////////////////////////////////////////////////////
VisiteurMiseAEchelle::VisiteurMiseAEchelle(float lastScale, float scale)
	: lastScale_(lastScale), scale_(scale)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAEchelle:: ~ VisiteurMiseAEchelle()
///
/// Destructeur par default
/// @param[in] :aucun
///
/// @return Aucune (destructeur).
///
//////////////////////////////////////////////////////////////////////////////////
VisiteurMiseAEchelle::~VisiteurMiseAEchelle()  
{
}

void VisiteurMiseAEchelle::setLastScale(float lastScale)
{
	lastScale_ = lastScale;
}

void VisiteurMiseAEchelle::setScale(float scale)
{
	scale_ = scale;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAEchelle::noeudAbstraitEchelle( NoeudAbstrait& noeudAbstrait)
///
///  Fonction qui permet au visiteur de faire mis a echelle sur le noeud abstrait
///
/// @param[in]: NoeudAbstrait & noeudAbstrait
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAEchelle::noeudAbstraitMiseAEchelle(NoeudAbstrait & noeudAbstrait)
{
	if(noeudAbstrait.estSelectionne())
	{
		double echelle = noeudAbstrait.getEchelle();

		echelle = echelle/lastScale_*scale_;

		noeudAbstrait.setEchelle(echelle);
	}
}	
////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAEchelle::noeudCompositeEchelle(NoeudComposite & noeudComposite)
///
///  Fonction qui permet au visiteur  de faire mis a echelle sur le noeud composite
///
/// @param[in]: NoeudAbstrait & noeudAbstrait
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAEchelle::noeudCompositeMiseAEchelle(NoeudComposite & noeudComposite)
{
	for(unsigned int i = 0; i < noeudComposite.obtenirNombreEnfants(); ++i) 
	{
		noeudComposite.chercher(i)->accepter(*this);
	}

	noeudAbstraitMiseAEchelle(noeudComposite);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAEchelle::visiter( NoeudAbstrait& noeudAbstrait)
///
///  Fonction qui permet au visiteur d'acceder au noeudAsteroide et faire son traitement
///
/// @param[in]: NoeudAbstrait & noeudAbstrait
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAEchelle::visiter(NoeudAbstrait & noeudAbstrait)
{
	noeudAbstraitMiseAEchelle(noeudAbstrait);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::visiter( NoeudAsteroide& noeudAsteroide)
///
///  Fonction qui permet au visiteur d'acceder au noeudAsteroide et faire son traitement
///
/// @param[in]: NoeudAsteroide & noeudAsteroide
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////

void VisiteurMiseAEchelle::visiter(NoeudAsteroide & noeudAsteroide)
{
	noeudAbstraitMiseAEchelle(noeudAsteroide);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::visiter( NoeudComposite& noeudComposite)
///
///  Fonction qui permet au visiteur d'acceder au NoeudComposite et faire son traitement
///
/// @param[in]: NoeudComposite & noeudComposite
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAEchelle::visiter(NoeudComposite& noeudComposite)
{
	noeudCompositeMiseAEchelle(noeudComposite);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAEchelle::visiter( NoeudBarriereProtectrice& noeudBarriereProtectrice)
///
///  Fonction qui permet au visiteur d'acceder au noeudAsteroide et faire son traitement
///
/// @param[in]: noeudBarriereProtectrice & noeudBarriereProtectrice
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAEchelle::visiter(NoeudBarriereProtectrice & noeudBarriereProtectrice)
{
	noeudAbstraitMiseAEchelle(noeudBarriereProtectrice);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAEchelle::visiter( NoeudAbstrait& noeudAbstrait)
///
///  Fonction qui permet au visiteur d'acceder au noeudAsteroide et faire son traitement
///
/// @param[in]: NoeudAbstrait & noeudAbstrait
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAEchelle::visiter(NoeudBonusAccelerateur & noeudBonusAccelerateur )
{
	noeudAbstraitMiseAEchelle(noeudBonusAccelerateur);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAEchelle::visiter(  NoeudPortail & noeudPortail)
///
///  Fonction qui permet au visiteur faire mis � �chelle sur le portail
///
/// @param[in]: NoeudPortail & noeudPortail
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAEchelle::visiter(NoeudPortail & noeudPortail)
{
	noeudAbstraitMiseAEchelle(noeudPortail);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAEchelle::visiter( NoeudPositionDepart & noeudPositionDepart)
///
///  Fonction qui permet au visiteur faire mis � �chelle sur le projectile
///
/// @param[in]: NoeudPositionDepart & noeudPositionDepart
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAEchelle::visiter(NoeudPositionDepart & noeudPositionDepart )
{
	noeudAbstraitMiseAEchelle(noeudPositionDepart);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAEchelle::visiter( NoeudProjectile & noeudProjectile)
///
///  Fonction qui permet au visiteur faire mis � �chelle sur le projectile
///
/// @param[in]: NoeudProjectile & noeudProjectile
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAEchelle::visiter(NoeudProjectile & noeudProjectile ) 
{
	noeudAbstraitMiseAEchelle(noeudProjectile);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAEchelle::visiter( NoeudStationSpatiale & noeudStationSpatiale)
///
///  Fonction qui permet au visiteur faire mis � �chelle sur la station spatiale
///
/// @param[in]: NoeudStationSpatiale & noeudStationSpatiale
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAEchelle::visiter(NoeudStationSpatiale & noeudStationSpatiale)
{
	noeudAbstraitMiseAEchelle(noeudStationSpatiale);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAEchelle::visiter( NoeudVaisseau & noeudVaisseau)
///
///  Fonction qui permet au visiteur de faire mis � echelle sur le vaisseaux
///
/// @param[in]: NoeudVaisseau & noeudVaisseau
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAEchelle::visiter(NoeudVaisseau & noeudVaisseau)
{
	noeudAbstraitMiseAEchelle(noeudVaisseau);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAEchelle::visiter( NoeudZoneJeu& noeudZoneJeu)
///
/// Fonction qui permet au visiteur de faire mis � echelle sur la zone de jeu
///
/// @param[in]: NoeudZoneJeu & noeudZoneJeu
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAEchelle::visiter(NoeudZoneJeu & noeudZoneJeu )
{
	noeudAbstraitMiseAEchelle(noeudZoneJeu);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAEchelle::visiter( NoeudZonePassage& noeudZonePassage)
///
/// Fonction qui permet au visiteur de faire mis � echelle sur la zone de passage
///
/// @param[in]:NoeudZonePassage& noeudZonePassage
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAEchelle::visiter(NoeudZonePassage & noeudZonePassage )
{
	noeudAbstraitMiseAEchelle(noeudZonePassage);
}
 void VisiteurMiseAEchelle::visiter(NoeudAnimation & noeudAnimation )
{

}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
