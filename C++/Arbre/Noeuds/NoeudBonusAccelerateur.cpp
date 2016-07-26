///////////////////////////////////////////////////////////////////////////////
/// @file NoeudBonusAccelerateur.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudBonusAccelerateur.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>
#define M_PI       3.14159265358979323846

#include "Utilitaire.h"
#include "Visiteurs\VisiteurBonusAcceleration.h"
#include "FacadeModele.h"
#include "Jeu\ModelManager.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudBonusAccelerateur::NoeudBonusAccelerateur(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudBonusAccelerateur::NoeudBonusAccelerateur(const std::string& typeNoeud)
   : NoeudAbstrait(typeNoeud)
{
	modele_ = ModelManager::obtenirInstance()->getModel(typeNoeud);
	liste_ = ModelManager::obtenirInstance()->getDisplayList(typeNoeud);

	this->actif_ = true;
	tempsCumuleBonus_ = 0.0f;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudBonusAccelerateur::~NoeudBonusAccelerateur()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudBonusAccelerateur::~NoeudBonusAccelerateur()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBonusAccelerateur::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBonusAccelerateur::afficherConcret() const
{
	// Modifie la couleur si sélectionné
	if (this->selectionne_)
	{
		// Rose (Le glPopAttrib remettra l'ancienne couleur)
		glColor3f(1, 0, 1);
	}
	else if (!this->actif_)
	{
		glColor3f(1, 0, 0);
	}
	else
	{
		// Vert
		glColor3f(0, 1, 0);
	}

	// Affichage du modèle.
	glCallList(liste_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCube::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBonusAccelerateur::animer(float temps)
{
	if (actif_)
	{
		VisiteurBonusAcceleration v(this);
   
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(v);
	}
	else
	{
		tempsCumuleBonus_ += temps;

		if (tempsCumuleBonus_ > 5.0f)
		{
			actif_ = true;
			tempsCumuleBonus_ = 0.0f;
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::accepter(VisiteurAbstrait& visiteur)
///
/// Cette fonction accepter le visiteur et lui permettre de faire son traitement 
/// sur l'objet appellant 
///
///
/// @param[in] visiteur : un objet visiteur
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBonusAccelerateur::accepter(VisiteurAbstrait& visiteur)
{
	visiteur.visiter(*this);
}

void NoeudBonusAccelerateur::reinitialiser()
{
	actif_ = true;
	tempsCumuleBonus_ = 0.0f;
}
	
void NoeudBonusAccelerateur::disable()
{
	this->actif_ = false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBonusAccelerateur::obtenirBoiteEnglobante(Vecteur3 &minXY, Vecteur3 &maxXY)
///
/// Cette fonction permet les coins min et max de la boite qui englobe l'objet
///
///
/// @param[in] minXY : le vecteur du coin min de l'objet
///	@param[in] maxXY : le vecteur du coin max de l'objet
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBonusAccelerateur::obtenirBoiteEnglobante(Vecteur3 &minXY, Vecteur3 &maxXY) const
{
	modele_->obtenirBoiteEnglobante(minXY, maxXY);

	// Appliquer échelle
	minXY *= echelle_;
	maxXY *= echelle_;

	// Appliquer rotation
	// On assume que la boite est centrée sur x, y
	double sinus = sin(angleRotation_*M_PI/180);
	double cosinus = cos(angleRotation_*M_PI/180);
	double width = maxXY[0] - minXY[0];
	double height = maxXY[1] - minXY[1];
	if (sinus < 0) sinus = -sinus;
	if (cosinus < 0) cosinus = -cosinus;

	double newWidth = height*sinus + width*cosinus;
	double newHeight = height*cosinus + width*sinus;
	
	minXY[0] = -newWidth/2;
	maxXY[0] = newWidth/2;
	minXY[1] = -newHeight/2;
	maxXY[1] = newHeight/2;

	// Appliquer translation
	minXY += this->positionRelative_;
	maxXY += this->positionRelative_;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
