///////////////////////////////////////////////////////////////////////////////
/// @file NoeudPositionDepart.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudPositionDepart.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>
#define M_PI       3.14159265358979323846

#include "Jeu\ModelManager.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPositionDepart::NoeudPositionDepart(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPositionDepart::NoeudPositionDepart(const std::string& typeNoeud)
   : NoeudAbstrait(typeNoeud)
{
	modele_ = ModelManager::obtenirInstance()->getModel(typeNoeud);
	liste_ = ModelManager::obtenirInstance()->getDisplayList(typeNoeud);
	
	modele_->obtenirBoiteEnglobante(boiteMinXY_, boiteMaxXY_);

	this->enregistrable_ = false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPositionDepart::~NoeudPositionDepart()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPositionDepart::~NoeudPositionDepart()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPositionDepart::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPositionDepart::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();
	
	// Modifie la couleur si sélectionné
	if (this->selectionne_)
	{
		// Rose (Le glPopAttrib remettra l'ancienne couleur)
		glColor3f(1, 0, 1);
	}

	// Affichage du modèle.
	glCallList(liste_);
	// Restauration de la matrice.
	glPopMatrix();
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
void NoeudPositionDepart::animer(float temps)
{
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
void NoeudPositionDepart::accepter(VisiteurAbstrait& visiteur)
{
	visiteur.visiter(*this);
}

void NoeudPositionDepart::obtenirBoiteEnglobante(Vecteur3 &minXY, Vecteur3 &maxXY) const
{
	minXY = boiteMinXY_;
	maxXY = boiteMaxXY_;

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
