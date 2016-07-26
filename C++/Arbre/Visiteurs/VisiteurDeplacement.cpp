///////////////////////////////////////////////////////////////////////////
/// @file VisiteurDeplacement.cpp
/// @author Najib Arbaoui
/// @date 2014-01-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "VisiteurDeplacement.h"
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
/// @fn VisiteurDeplacement::VisiteurDeplacement()
///
/// Constructeur par default
/// @param[in] :aucun
///
/// @return Aucune (constructeur).
///
//////////////////////////////////////////////////////////////////////////////////
VisiteurDeplacement::VisiteurDeplacement()
{
		
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDeplacement:: ~ VisiteurDeplacement()
///
/// Destructeur par default
/// @param[in] :aucun
///
/// @return Aucune (destructeur).
///
//////////////////////////////////////////////////////////////////////////////////
VisiteurDeplacement::~VisiteurDeplacement()  
{
		
}

//////////////////////////////////////////////////////////////////////
void VisiteurDeplacement::setDeplacement(Vecteur3 dec){
		
	deplacementX_ = dec[0];
	deplacementY_ = dec[1];
	deplacementZ_ = dec[2];
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::noeudAbstraitDeplacer(NoeudAbstrait& noeud)
///
///  Fonction qui permet au visiteur de deplacer un noeud abstrait
///
/// @param[in]: NoeudAbstrait& noeud
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void VisiteurDeplacement::noeudAbstraitDeplacer(NoeudAbstrait& noeud)
{
	Vecteur3 deplacement(deplacementX_,deplacementY_,0.0);
	Vecteur3 positionRelative = noeud.obtenirPositionRelative();

	if(noeud.estSelectionne()){
		positionRelative += deplacement;
		noeud.assignerPositionRelative(positionRelative);
	}
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
void VisiteurDeplacement::noeudCompositeDeplacer(NoeudComposite& noeudComposite)
{
	for(unsigned int i = 0; i < noeudComposite.obtenirNombreEnfants(); ++i)
	{
		if (noeudComposite.chercher(i)->estSelectionne()) {
			noeudComposite.chercher(i)->accepter(*this);
		}
	}
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
void VisiteurDeplacement::visiter(NoeudComposite& noeudComposite)
{
	noeudCompositeDeplacer(noeudComposite);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::visiter( NoeudAsteroide& noeudAsteroide)
///
///  Fonction qui permet au visiteur de deplacer le noeud asteroide
/// @param[in]: NoeudAsteroide & noeudAsteroide
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////

void VisiteurDeplacement::visiter(NoeudAbstrait & noeudAbstrait)
{
	noeudAbstraitDeplacer(noeudAbstrait);	
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
void VisiteurDeplacement::visiter(NoeudAsteroide & noeudAsteroide)
{
	noeudAbstraitDeplacer(noeudAsteroide);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::visiter(NoeudBarriereProtectrice & noeudBarriereProtectrice)
///
///  Fonction qui permet au visiteur de deplacer la barriere protectrice
///
/// @param[in]: NoeudBarriereProtectrice & noeudBarriereProtectrice
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void VisiteurDeplacement::visiter(NoeudBarriereProtectrice & noeudBarriereProtectrice)
{
	noeudAbstraitDeplacer(noeudBarriereProtectrice);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::visiter( NoeudBonusAccelerateur & noeudBonusAccelerateur)
///
///  Fonction qui permet au visiteur de deplacer le bonus accelerateur
///
/// @param[in]: NoeudBonusAccelerateur & noeudBonusAccelerateur
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
	void VisiteurDeplacement::visiter(NoeudBonusAccelerateur & noeudBonusAccelerateur )
	{
		noeudAbstraitDeplacer(noeudBonusAccelerateur);
	}
////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::visiter( NoeudPortail & noeudPortail)
///
///  Fonction qui permet au visiteur de deplacer le portail
///
/// @param[in]: NoeudPortail & noeudPortail
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
	void VisiteurDeplacement::visiter(NoeudPortail & noeudPortail)
	{
		noeudAbstraitDeplacer(noeudPortail);
	}
////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::visiter( NoeudPositionDepart & noeudPositionDepart )
///
///  Fonction qui permet au visiteur de deplacer la position de depart
///
/// @param[in]: NoeudPositionDepart & noeudPositionDepart 
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void VisiteurDeplacement::visiter(NoeudPositionDepart & noeudPositionDepart )
{
	noeudAbstraitDeplacer(noeudPositionDepart);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::visiter( NoeudProjectile & noeudProjectile)
///
///  Fonction qui permet au visiteur de deplacer le projectile
///
/// @param[in]: NoeudProjectile & noeudProjectile
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
	void VisiteurDeplacement::visiter(NoeudProjectile & noeudProjectile ) 
	{
		noeudAbstraitDeplacer(noeudProjectile);
	}
////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::visiter( NoeudStationSpatiale & noeudStationSpatiale)
///
///  Fonction qui permet au visiteur de deplacer la station spatiale
///
/// @param[in]: NoeudStationSpatiale & noeudStationSpatiale
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
	void VisiteurDeplacement::visiter(NoeudStationSpatiale & noeudStationSpatiale)
	{
		noeudAbstraitDeplacer(noeudStationSpatiale);
	}
////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::visiter( NoeudVaisseau & noeudVaisseau)
///
///  Fonction qui permet au visiteur de deplacer le vaisseau
///
/// @param[in]: NoeudVaisseau & noeudVaisseau
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
	void VisiteurDeplacement::visiter(NoeudVaisseau & noeudVaisseau)
	{
		noeudAbstraitDeplacer(noeudVaisseau);
	}
////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::visiter( NoeudZoneJeu & noeudZoneJeu )
///
///  Fonction qui permet au visiteur d'acceder au noeudAsteroide et faire son traitement
///
/// @param[in]: NoeudZoneJeu & noeudZoneJeu 
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
	void VisiteurDeplacement::visiter(NoeudZoneJeu & noeudZoneJeu ){
		noeudAbstraitDeplacer(noeudZoneJeu);
	}
////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::visiter( NoeudZonePassage & noeudZonePassage)
///
///  Fonction qui permet au visiteur de deplacer le noeud
///
/// @param[in]: NoeudZonePassage & noeudZonePassage
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
	
 void VisiteurDeplacement::visiter(NoeudZonePassage & noeudZonePassage ){}
 void VisiteurDeplacement::visiter(NoeudAnimation & noeudAnimation )
{

}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////