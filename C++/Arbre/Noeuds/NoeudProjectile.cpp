///////////////////////////////////////////////////////////////////////////////
/// @file NoeudProjectile.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudProjectile.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>
#define M_PI       3.14159265358979323846

#include "Utilitaire.h"
#include "FacadeModele.h"
#include "Visiteurs\VisiteurProjectile.h"
#include "Jeu\ModelManager.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudProjectile::NoeudProjectile(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudProjectile::NoeudProjectile(const std::string& typeNoeud)
   : NoeudAbstrait(typeNoeud)
{
	modele_ = ModelManager::obtenirInstance()->getModel(typeNoeud);
	liste_ = ModelManager::obtenirInstance()->getDisplayList(typeNoeud);
	
	modele_->obtenirBoiteEnglobante(boiteMinXY_, boiteMaxXY_);

	dynamique_ = true;
	enabled_ = true;
	masse_ = 10;
	tempsPasse_ = 0;

	// Augmenter la taille du projectile
	this->echelle_ = 2.0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudProjectile::~NoeudProjectile()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudProjectile::~NoeudProjectile()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudProjectile::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudProjectile::afficherConcret() const
{
	if (enabled_)
	{
		// Sauvegarde de la matrice.
		glPushMatrix();

		// Change la couleur au cyan
		glColor3d(0.12, 0.7, 0.84);
 
		// Rotation de l'axe des Z pour que le projectile soit orienté vers la droite lorsque l'angle de rotation est nulle
		glRotatef(270, 0, 0, 1);
	
		// Affichage du modèle.
		glCallList(liste_);

		// Restauration de la matrice.
		glPopMatrix();
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudProjectile::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudProjectile::animer(float temps)
{
	if (enabled_)
	{
		// Applique la physique tout en calculant la distance parcourue par le projectile,
		//afin de le faire disparaitre quand une trop grand distance a été passée
		Vecteur3 oldPosition = this->positionRelative_;
		
		// Calculer acceleration
		acceleration_ += forces_;
		this->appliquerPhysique(temps);
		acceleration_ -= forces_;

		// Reset les forces en jeu
		forces_ = Vecteur3(0, 0, 0);

		// Orienter le projectile selon la direction
		NoeudAbstrait::setAngleRotation(utilitaire::RAD_TO_DEG(vitesse_.lireTheta()));

		// Compter le temps écoulé
		tempsPasse_ += temps;
		// Si ça fait plus de 3 secondes
		if (tempsPasse_ > 3.0f)
		{
			enabled_ = false;
		}

		Vecteur3 minXY, maxXY;
		this->obtenirBoiteEnglobante(minXY, maxXY);
		if (!FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->estDansCadreDepart(minXY, maxXY))
		{
			enabled_ = false;
		}

		// Détection des collisions
		VisiteurProjectile v(this);
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(v);
	}
}

void NoeudProjectile::setVitesse(double vitesseBase, Vecteur3 vitesseVaisseau)
{
	// Simple calcul a refaire
	double dx = cos(utilitaire::DEG_TO_RAD(angleRotation_));
	double dy = sin(utilitaire::DEG_TO_RAD(angleRotation_));

	this->vitesse_ = vitesseBase*Vecteur3(dx, dy, 0) + vitesseVaisseau;
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
void NoeudProjectile::accepter(VisiteurAbstrait& visiteur)
{
	visiteur.visiter(*this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudProjectile::obtenirBoiteEnglobante(Vecteur3 &minXY, Vecteur3 &maxXY)
///
/// Cette fonction permet les coins min et max de la boite qui englobe l'objet
///
///
/// @param[in] minXY : le vecteur du coin min de l'objet
///	@param[in] maxXY : le vecteur du coin max de l'objet
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudProjectile::obtenirBoiteEnglobante(Vecteur3 &minXY, Vecteur3 &maxXY) const
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

double NoeudProjectile::obtenirSphereEnglobante() const
{
	// Applique l'échelle
	double rayon = modele_->obtenirSphereEnglobante() * this->echelle_;

	// Facteur constant pour que les extrémités du modèle ne compte pas dans la détection des collisions
	return rayon;
}

void NoeudProjectile::detruire()
{
	this->enabled_ = false;
}

bool NoeudProjectile::isEnabled() const
{
	return enabled_;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
