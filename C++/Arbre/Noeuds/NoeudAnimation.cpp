///////////////////////////////////////////////////////////////////////////////
/// @file NoeudAnimation.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudAnimation.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>
#include "Jeu\ModelManager.h"
#include "Utilitaire.h"
#include "FacadeModele.h"
////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAnimation::NoeudAnimation(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudAnimation::NoeudAnimation(const std::string& typeNoeud)
   : NoeudAbstrait(typeNoeud) 
{
	selectionnable_ = false;
	enregistrable_ = false;
	periode_ = 0.0;
	taille_ = 1.0;

    colorR_ = 1.0;
	colorG_ = 1.0;
	colorB_ = 1.0;
    modele_ = ModelManager::obtenirInstance()->getModel(typeNoeud);
	liste_ = ModelManager::obtenirInstance()->getDisplayList(typeNoeud);
	duree_ = 0.0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAnimation::~NoeudAnimation()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudAnimation::~NoeudAnimation()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAnimation::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAnimation::afficherConcret() const
{
	glColor3f(colorR_ , colorG_ , colorB_);
	glScaled(taille_, taille_,taille_);

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
void NoeudAnimation::animer(float temps)
{
	periode_ += temps;

	if(periode_ > 0.5 && periode_ <1)
	{
		taille_ += 0.5;
		colorR_ = 0.99f ;
		colorG_ = 0.05f ;
		colorB_= 0.05f;
	}
	else if(periode_ >= 1 && periode_ <=1.5)
	{
		taille_ -= 0.5;
		
		colorR_ = 0.97f;
		colorG_ = 0.7f;
		colorB_= 0.07f;
	}
	else
	{
		colorR_ = 1.0f;
		colorG_ = 1.0f;
		colorB_= 0.0f;
		if(periode_ > 1.5)
			periode_ = 0 ;
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
void NoeudAnimation::accepter(VisiteurAbstrait& visiteur)
{
	visiteur.visiter(*this);
}

void NoeudAnimation::obtenirBoiteEnglobante(Vecteur3 &minXY, Vecteur3 &maxXY) const
{
	
}

  
// fonction retourne la duree de l'animation
   float NoeudAnimation::obtenirDuree()
   {
		return duree_ ;
   }

   // fonction retourne la duree de l'animation
   void NoeudAnimation::assignerDuree( float duree)
   {
		this->duree_ = duree;
   }

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
