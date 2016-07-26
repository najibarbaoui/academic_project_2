///////////////////////////////////////////////////////////////////////////////
/// @file NoeudStationSpatiale.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudStationSpatiale.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>
#include <climits>
#define M_PI       3.14159265358979323846

#include "Utilitaire.h"
#include "FacadeModele.h"
#include "Jeu\ModelManager.h"
#include "GestionnaireAudio.h"
#include "GestionnaireJeu.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudStationSpatiale::NoeudStationSpatiale(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudStationSpatiale::NoeudStationSpatiale(const std::string& typeNoeud)
   : NoeudAbstrait(typeNoeud)
{
	modele_ = ModelManager::obtenirInstance()->getModel(typeNoeud);
	liste_ = ModelManager::obtenirInstance()->getDisplayList(typeNoeud);
	
	modele_->obtenirBoiteEnglobante(boiteMinXY_, boiteMaxXY_);

	enabled_ = true;
	masse_ = DBL_MAX;
	
	// TODO: obtenir le nombre de points de vie de la FacadeModele
	this->ptDeVie_ = 3;
	vitesseDeRotation_ = static_cast<float>(rand()%200); // vitesse de rotation aléatoir pour chaque noeud crée
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudStationSpatiale::~NoeudStationSpatiale()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudStationSpatiale::~NoeudStationSpatiale()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudStationSpatiale::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudStationSpatiale::afficherConcret() const
{
	if (enabled_)
	{
		// Sauvegarde de la matrice.
		glPushMatrix();
	
		// Rotation de la station spatiale dans le temps
		glRotatef(-vitesseDeRotation_, 0.5 ,0.0,0.5);

		// Modifie la couleur si sélectionné
		if (this->selectionne_)
		{
			// Rose (Le glPopAttrib remettra l'ancienne couleur)
			glColor3f(1, 0, 1);
		}
		else
		{
			// Jaune
			glColor3d(0.83, 0.81, 0.41);
		}

		// Affichage du modèle.
		glCallList(liste_);
	
		// Afficher une sphère englobante
		glBegin(GL_LINE_LOOP);
 
		// Couleur de la sphère
		glColor3d(0.0, 0.0, 1.0);

		// On a déja appliquer l'échelle rendu à cette étape. on ne peut donc pas utiliser this->obtenirSphereEnglobante()
		double radius = modele_->obtenirSphereEnglobante() * 0.8;
		for (int i=0; i <= 360; i++)
		{
			double degInRad = utilitaire::DEG_TO_RAD(i);
			glVertex2d(cos(degInRad)*radius, sin(degInRad)*radius);
		}
 
		glEnd();

		// Restauration de la matrice.
		glPopMatrix();
	}
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
void NoeudStationSpatiale::animer(float temps)
{
	if (enabled_)
	{
		vitesseDeRotation_ +=  temps * 10 ;
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
void NoeudStationSpatiale::accepter(VisiteurAbstrait& visiteur)
{
	visiteur.visiter(*this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudStationSpatiale::obtenirBoiteEnglobante(Vecteur3 &minXY, Vecteur3 &maxXY)
///
/// Cette fonction permet les coins min et max de la boite qui englobe l'objet
///
///
/// @param[in] minXY : le vecteur du coin min de l'objet
///	@param[in] maxXY : le vecteur du coin max de l'objet
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudStationSpatiale::obtenirBoiteEnglobante(Vecteur3 &minXY, Vecteur3 &maxXY) const
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

double NoeudStationSpatiale::obtenirSphereEnglobante() const
{
	// Applique l'échelle
	double rayon = modele_->obtenirSphereEnglobante() * this->echelle_;

	// Facteur constant pour que les extrémités du modèle ne compte pas dans la détection des collisions
	return rayon * 0.8;
}

void NoeudStationSpatiale::reinitialiser()
{
	this->enabled_ = true;
	// TODO: obtenir le nombre de points de vie de la FacadeModele
	ptDeVie_ = 10;
}

void NoeudStationSpatiale::baisserPointsDeVie()
{
	this->ptDeVie_ -= 1;

	if (ptDeVie_ == 0)
	{
		this->enabled_ = false;
		
		GestionnaireJeu::obtenirInstance()->simulerExplosion(this,1,"station");
	}
}

bool NoeudStationSpatiale::isEnabled() const
{
	return enabled_;
}

void NoeudStationSpatiale::setPointDeVie(int pointDeVie)
{
  this->ptDeVie_ = pointDeVie;
	
}
int NoeudStationSpatiale::getPointDeVie()
{
  return ptDeVie_ ;
	
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
