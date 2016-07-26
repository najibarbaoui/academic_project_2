///////////////////////////////////////////////////////////////////////////////
/// @file NoeudAsteroide.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudAsteroide.h"

#include <ctime>
#include <windows.h>
#include <GL/gl.h>
#include <cmath>
#define M_PI       3.14159265358979323846

#include "Utilitaire.h"
#include "FacadeModele.h"
#include "Jeu\ModelManager.h"
#include "Visiteurs\VisiteurCollisionSphereSphere.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAsteroide::NoeudAsteroide(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudAsteroide::NoeudAsteroide(const std::string& typeNoeud)
   : NoeudAbstrait(typeNoeud)
   
{
	modele_ = ModelManager::obtenirInstance()->getModel(typeNoeud);
	liste_ = ModelManager::obtenirInstance()->getDisplayList(typeNoeud);

	angle_ = 0;
	enabled_ = true;
	dynamique_ = true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAsteroide::~NoeudAsteroide()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudAsteroide::~NoeudAsteroide()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAsteroide::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAsteroide::afficherConcret() const
{
	if (enabled_)
	{
		// Sauvegarde de la matrice.
		glPushMatrix();
	
		// Rotation selon le temps
		// Révolution autour du centre.
		glRotatef(-angle_, 0.5 ,0.5,0.5);

		glColor3d(0.8, 0.8, 0.9);

		glCallList(liste_);

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
void NoeudAsteroide::animer(float temps)
{
	if (enabled_)
	{
		// Calculer acceleration
		acceleration_ += forces_;
		this->appliquerPhysique(temps);
		acceleration_ -= forces_;

		// Reset les forces en jeu
		forces_ = Vecteur3(0, 0, 0);

		angle_ += 100* temps;

		// Calculer les collisions
		VisiteurCollisionSphereSphere v(this);

		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(v);
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
void NoeudAsteroide::accepter(VisiteurAbstrait& visiteur)
{
	visiteur.visiter(*this);
}

void NoeudAsteroide::obtenirBoiteEnglobante(Vecteur3 &minXY, Vecteur3 &maxXY) const
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


double NoeudAsteroide::obtenirSphereEnglobante() const
{
	// Applique l'échelle
	//double rayon = modele_->calculerSphereEnglobante() * this->echelle_;
	double rayon = modele_->obtenirSphereEnglobante() * this->echelle_;

	// Facteur constant pour que les extrémités du modèle ne compte pas dans la détection des collisions
	return rayon * 0.8;
}

void NoeudAsteroide::devierTrajectoire(Vecteur3 axe)
{
	//// Il faut maintenant effecture le rebond. On va appliquer une rotation au vecteur vitesse.
	// On calcule l'angle de rotation
	double angleNormal = axe.lireTheta();
	double angleTrajectoire;
	if (vitesse_[1] > 0)
	{
		// Angle entre 0 et 180
		angleTrajectoire = vitesse_.lireTheta() - utilitaire::PI;
	}
	else
	{
		// Angle entre 0 et -180
		angleTrajectoire = vitesse_.lireTheta() + utilitaire::PI;
	}
	// On se retrouve avec un angle entre -180 et 180 
	double difference = angleNormal - angleTrajectoire;

	if (difference < -utilitaire::PI/2)
	{
		// Ajoute 360 pour se retrouver entre -90 et 90
		difference += utilitaire::PI + utilitaire::PI;
	}
	else if (difference > utilitaire::PI/2)
	{
		// Soustrait 360 pour se retrouver entre -90 et 90
		difference -= utilitaire::PI + utilitaire::PI;
	}
	
	// On applique la rotation nécessaire
	vitesse_ = vitesse_.tourner(2*(difference) + utilitaire::PI, Vecteur3(0, 0, 1));

}

int  NoeudAsteroide::getPointsDeVie()
{
	return this->pointsDeVie_;
}

void  NoeudAsteroide::setPointsDeVie(int pointsDeVie)
{
	this->pointsDeVie_ = pointsDeVie;
}
 
Vecteur3 NoeudAsteroide::getVitesse()
{
	return this->vitesse_;
}

void  NoeudAsteroide::setVitesse(Vecteur3 vitesse)
{
	this->vitesse_ = vitesse;
}

void NoeudAsteroide::baisserPointsDeVie()
{
	this->pointsDeVie_ -= 1;

	if (pointsDeVie_ == 0)
	{
		this->enabled_ = false;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAsteroide::SortieConsole() const
///
/// Quand un astéroïde est créé, la ligne suivante doit être affichée à la console:
/// HH:MM:SS:mm Création d'astéroìde x: POSX	y: POSY	vi: VI	t: T
///
/// Où POSX représente la position en x, POSY la position en Y, VI le module de la vitesse initiale, T la taille de l’astéroïde.
///
/// @param Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAsteroide::SortieConsole() const
{
	const char* tab = "\t";
	std::string strTime = utilitaire::TimeToString();
	std::cout << strTime << " - " << "Création d'astéroìde : x: " << positionRelative_[0] << tab
		<< "y: " << positionRelative_[1] << tab 
		<< "vi: " << vitesse_.norme() << tab 
		<< "t: " << echelle_ << endl;
}


bool NoeudAsteroide::isEnabled() const
{
	return enabled_;
}

void NoeudAsteroide::setEnabled(bool value)
{
	enabled_ = value ;
}

void NoeudAsteroide::setCoteOuCree(int cote)
{
	coteOuCree_ = cote ;
}

int NoeudAsteroide::getCoteOuCree()
{
	return coteOuCree_ ;
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
