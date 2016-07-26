
///////////////////////////////////////////////////////////////////////////
/// @file VisiteurDeplacement.cpp
/// @author Najib Arbaoui
/// @date 2014-01-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "VisiteurRotation.h"

#define M_PI       3.14159265358979323846

///////////////////////////////////////////////////////////////////////////
/// @class  VisiteurDeplacement
/// @brief Classe de visiteur qui permet de deplacer les noeuds d un arbre
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::VisiteurRotation(double angle, Vecteur3 centreRotation)
///
/// Constructeur par default
/// @param[in] : Angle de rotation d�sir�
/// @param[in] : Centre de rotation d�sir�
///
/// @return Aucune (constructeur).
///
//////////////////////////////////////////////////////////////////////////////////
VisiteurRotation::VisiteurRotation(double angle, Vecteur3 centreRotation)
{
		angle_ = angle;
		centreRotation_ = centreRotation;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation:: ~ VisiteurRotation()
///
/// Destructeur par default
/// @param[in] :aucun
///
/// @return Aucune (destructeur).
///
//////////////////////////////////////////////////////////////////////////////////
VisiteurRotation::~VisiteurRotation()  
{
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::setAngle(double angle)
///
///  Fonction qui permet de modifier l'angle de rotation
///
/// @param[in]: Angle de rotation d�sir�
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::setAngle(double angle)
{
	angle_ = angle;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::setCentreRotation(Vecteur3 centreRotation)
///
///  Fonction qui permet de modifier le centre de rotation
///
/// @param[in]: Centre de rotation d�sir�
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::setCentreRotation(Vecteur3 centreRotation)
{
	centreRotation_ = centreRotation;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::noeudAbstraitDeplacer(NoeudAbstrait& noeud)
///
///  Fonction qui permet au visiteur de deplacer un noeud abstrait
///
/// @param[in]: NoeudAbstrait& noeud
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::noeudAbstraitRotation(NoeudAbstrait& noeud)
{
	if(noeud.estSelectionne())
	{
		// Rotation du noeud
		double angle = noeud.getAngleRotation();
		angle += angle_;
		noeud.setAngleRotation(angle);
		
		// Bouger le noeud autour du centre de rotation
		Vecteur3 positionRelativeCentreRotation = noeud.getPosition() - centreRotation_;

		// Rotation de la position
		positionRelativeCentreRotation = positionRelativeCentreRotation.tourner(angle_ * M_PI/180, Vecteur3(0, 0, 1));

		// Rebouger le noeud
		noeud.assignerPositionRelative(positionRelativeCentreRotation + centreRotation_);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::visiter( NoeudComposite& noeudComposite)
///
///  Fonction qui permet au visiteur d'acceder au NoeudComposite et faire son traitement
///
/// @param[in]: NoeudComposite & noeudComposite
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::noeudCompositeRotation(NoeudComposite& noeudComposite)
{
	for(unsigned int i = 0; i < noeudComposite.obtenirNombreEnfants(); ++i)
	{
		if (noeudComposite.chercher(i)->estSelectionne()) {
			noeudComposite.chercher(i)->accepter(*this);
		}
	}

	noeudAbstraitRotation(noeudComposite);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::visiter( NoeudComposite& noeudComposite)
///
///  Fonction qui permet au visiteur d'acceder au NoeudComposite et faire son traitement
///
/// @param[in]: NoeudComposite & noeudComposite
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::visiter(NoeudComposite& noeudComposite)
{
	noeudCompositeRotation(noeudComposite);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::visiter( NoeudAsteroide& noeudAsteroide)
///
///  Fonction qui permet au visiteur de deplacer le noeud asteroide
/// @param[in]: NoeudAsteroide & noeudAsteroide
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////

void VisiteurRotation::visiter(NoeudAbstrait & noeudAbstrait)
{
	noeudAbstraitRotation(noeudAbstrait);	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::visiter( NoeudAsteroide& noeudAsteroide)
///
///  Fonction qui permet au visiteur d'acceder au noeudAsteroide et faire son traitement
///
/// @param[in]: NoeudAsteroide & noeudAsteroide
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////

	void VisiteurRotation::visiter(NoeudAsteroide & noeudAsteroide)
	{
		noeudAbstraitRotation(noeudAsteroide);
	}
////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::visiter(NoeudBarriereProtectrice & noeudBarriereProtectrice)
///
///  Fonction qui permet au visiteur de deplacer la barriere protectrice
///
/// @param[in]: NoeudBarriereProtectrice & noeudBarriereProtectrice
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::visiter(NoeudBarriereProtectrice & noeudBarriereProtectrice)
{
	noeudAbstraitRotation(noeudBarriereProtectrice);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::visiter( NoeudBonusAccelerateur & noeudBonusAccelerateur)
///
///  Fonction qui permet au visiteur de deplacer le bonus accelerateur
///
/// @param[in]: NoeudBonusAccelerateur & noeudBonusAccelerateur
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
	void VisiteurRotation::visiter(NoeudBonusAccelerateur & noeudBonusAccelerateur )
	{
		noeudAbstraitRotation(noeudBonusAccelerateur);
	}
////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::visiter( NoeudPortail & noeudPortail)
///
///  Fonction qui permet au visiteur de deplacer le portail
///
/// @param[in]: NoeudPortail & noeudPortail
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
	void VisiteurRotation::visiter(NoeudPortail & noeudPortail)
	{
		noeudAbstraitRotation(noeudPortail);
	}
////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::visiter( NoeudPositionDepart & noeudPositionDepart )
///
///  Fonction qui permet au visiteur de deplacer la position de depart
///
/// @param[in]: NoeudPositionDepart & noeudPositionDepart 
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
	void VisiteurRotation::visiter(NoeudPositionDepart & noeudPositionDepart )
	{
		noeudAbstraitRotation(noeudPositionDepart);
	}
////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::visiter( NoeudProjectile & noeudProjectile)
///
///  Fonction qui permet au visiteur de deplacer le projectile
///
/// @param[in]: NoeudProjectile & noeudProjectile
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
	void VisiteurRotation::visiter(NoeudProjectile & noeudProjectile ) 
	{
		noeudAbstraitRotation(noeudProjectile);
	}
////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::visiter( NoeudStationSpatiale & noeudStationSpatiale)
///
///  Fonction qui permet au visiteur de deplacer la station spatiale
///
/// @param[in]: NoeudStationSpatiale & noeudStationSpatiale
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
	void VisiteurRotation::visiter(NoeudStationSpatiale & noeudStationSpatiale)
	{
		noeudAbstraitRotation(noeudStationSpatiale);
	}
////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::visiter( NoeudVaisseau & noeudVaisseau)
///
///  Fonction qui permet au visiteur de deplacer le vaisseau
///
/// @param[in]: NoeudVaisseau & noeudVaisseau
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
	void VisiteurRotation::visiter(NoeudVaisseau & noeudVaisseau)
	{
		noeudAbstraitRotation(noeudVaisseau);
	}
////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::visiter( NoeudZoneJeu & noeudZoneJeu )
///
///  Fonction qui permet au visiteur d'acceder au noeudAsteroide et faire son traitement
///
/// @param[in]: NoeudZoneJeu & noeudZoneJeu 
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
	void VisiteurRotation::visiter(NoeudZoneJeu & noeudZoneJeu ){}
////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::visiter( NoeudZonePassage & noeudZonePassage)
///
///  Fonction qui permet au visiteur de deplacer le noeud
///
/// @param[in]: NoeudZonePassage & noeudZonePassage
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
	
 void VisiteurRotation::visiter(NoeudZonePassage & noeudZonePassage ){}

 void VisiteurRotation::visiter(NoeudAnimation & noeudAnimation )
{

}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////


