///////////////////////////////////////////////////////////////////////////////
/// @file NoeudVaisseau.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudVaisseau.h"

#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>
#define M_PI       3.14159265358979323846

#include "FacadeModele.h"
#include "GestionnaireAudio.h"
#include "Jeu\ModelManager.h"
#include "Visiteurs\VisiteurCollisionSphereSphere.h"

class VisiteurAbstrait;
////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudVaisseau::NoeudVaisseau(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudVaisseau::NoeudVaisseau(const std::string& typeNoeud)
   : NoeudComposite(typeNoeud)
   
{
	modele_ = ModelManager::obtenirInstance()->getModel(typeNoeud);
	liste_ = ModelManager::obtenirInstance()->getDisplayList(typeNoeud);
	
	modele_->obtenirBoiteEnglobante(boiteMinXY_, boiteMaxXY_);
	cout<<"MinZ:"<<boiteMinXY_[2]<<" MaxZ:"<<boiteMaxXY_[2]<<endl;

	vitesseRotation_ = 120;
	dynamique_ = true;
	masse_ = 120;
	bonusAcceleration_ = false;
	tempsCumuleBonus_ = 0.0f;
	vitesseMax_ = 100;
	etourdi_ = false;
	tempsCumuleEtourdi_ = 0.0f;

	// Diminue la taille du vaisseau
	this->echelle_ = 0.5;

	// Création d'une liste d'affichage.  ATTENTION, CECI N'EST PAS UN
	// USAGE CORRECT DES LISTES D'AFFICHAGE, puisque la même liste serait
	// recréée pour chaque instance d'un noeud, alors que la même pourrait
	// être partagée par toutes les instances d'un même type de noeud.
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudVaisseau::~NoeudVaisseau()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudVaisseau::~NoeudVaisseau()
{
   while (!projectileList.empty())
   {
		// Obtenir le projectile sur le dessus
		NoeudProjectile* toDelete = projectileList.front();
		projectileList.pop_front();

		// L'effacer de l'arbre
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(toDelete);
   }
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudVaisseau::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudVaisseau::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();

	// Change la couleur 
	glColor3d(0.83, 0.52, 0.1);
 
	// L'ordre des rotations est importante
	// Rotation de l'axe des Y pour voir le vaisseau du dessus
	glRotatef(180, 0, 1, 0);
	// Rotation de l'axe des Z pour que le vaisseau pointe vers la droite lorsque angleRotation_ == 0
	glRotatef(270, 0, 0, 1);

	if (etourdi_)
	{
		glRotatef(360*tempsCumuleEtourdi_, 0, 0, 1.0);

		glColor3d(1.0f, 1.0f, 1.0f);
	}
	else if (bonusAcceleration_)
	{
		glColor3d(1.0, 0.22, 0.05);
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
void NoeudVaisseau::animer(float temps)
{
	// Calculer acceleration
	acceleration_ += forces_;
	this->appliquerPhysique(temps);
	acceleration_ -= forces_;

	// Reset les forces en jeu
	forces_ = Vecteur3(0, 0, 0);

	// Vitesse max
	if (vitesse_.norme() > vitesseMax_)
	{
		vitesse_.normaliser();
		vitesse_ *= vitesseMax_;
	}

	if (!this->etourdi_)
	{
		// Appliquer vitesse de rotation
		this->setAngleRotation(this->angleRotation_ + vitesseRotation_ * temps);
	}

	while (!projectileList.empty() && !projectileList.front()->isEnabled())
	{
		// Obtenir le projectile sur le dessus
		NoeudProjectile* toDelete = projectileList.front();
		projectileList.pop_front();

		// L'effacer de l'arbre
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(toDelete);
	}

	//// Collision avec zone de jeu
	this->collisionZoneJeu();

	// Calculer les collisions
	VisiteurCollisionSphereSphere v(this);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(v);

	// Calculer le temps passé depuis que le bonus d'acceleration a été appliqué
	if (etourdi_)
	{
		tempsCumuleEtourdi_ += temps;

		if (tempsCumuleEtourdi_ > 1.0f)
		{
			etourdi_ = false;
			tempsCumuleEtourdi_ = 0.0f;
		}
	}

	// Calculer le temps passé depuis que le bonus d'acceleration a été appliqué
	if (bonusAcceleration_)
	{
		tempsCumuleBonus_ += temps;

		if (tempsCumuleBonus_ > 2.0f)
		{
			bonusAcceleration_ = false;
			tempsCumuleBonus_ = 0.0f;
		}
	}
}

void NoeudVaisseau::collisionZoneJeu()
{
	// Les limites de chacun des noeuds
	Vecteur3 minXY, maxXY, zoneJeuMinXY, zoneJeuMaxXY;
	//this->obtenirBoiteEnglobante(minXY, maxXY);
	double rayon = this->obtenirSphereEnglobante();
	minXY[0] = this->positionRelative_[0] - rayon;
	minXY[1] = this->positionRelative_[1] - rayon;
	maxXY[0] = this->positionRelative_[0] + rayon;
	maxXY[1] = this->positionRelative_[1] + rayon;

	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirZoneJeu()->obtenirBoiteEnglobante(zoneJeuMinXY, zoneJeuMaxXY);
	
	// Gauche
	if (minXY[0] < zoneJeuMinXY[0])
	{
		positionRelative_[0] += (zoneJeuMinXY[0] - minXY[0]);
		vitesse_[0] = 0;
	}
	// Droite
	else if (maxXY[0] > zoneJeuMaxXY[0])
	{
		positionRelative_[0] += (zoneJeuMaxXY[0] - maxXY[0]);
		vitesse_[0] = 0;
	}

	// Bas
	if (minXY[1] < zoneJeuMinXY[1])
	{
		positionRelative_[1] += (zoneJeuMinXY[1] - minXY[1]);
		vitesse_[1] = 0;
	}
	// Haut
	else if (maxXY[1] > zoneJeuMaxXY[1])
	{
		positionRelative_[1] += (zoneJeuMaxXY[1] - maxXY[1]);
		vitesse_[1] = 0;
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
void NoeudVaisseau::accepter(VisiteurAbstrait& visiteur)
{
	visiteur.visiter(*this);
}

void NoeudVaisseau::obtenirBoiteEnglobante(Vecteur3 &minXY, Vecteur3 &maxXY) const
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

double NoeudVaisseau::obtenirSphereEnglobante() const
{
	// Applique l'échelle
	double rayon = modele_->obtenirSphereEnglobante() * this->echelle_;

	// Facteur constant pour que les extrémités du modèle ne compte pas dans la détection des collisions
	return rayon * 0.8;
}


   //obtenir l'angle de rotation
double NoeudVaisseau::getAngleRotation() const
{
	if (this->etourdi_)
	{
		return fmod(angleRotation_ - 360*tempsCumuleEtourdi_ + 360, 360);
	}
	else
	{
		return angleRotation_;
	}
}

void NoeudVaisseau::setVitesseRotation(float valeur)
{
	vitesseRotation_ = valeur;
}

void NoeudVaisseau::setAcceleration(double valeur)
{
	if (!this->etourdi_)
	{
		// Simple calcul a refaire
		double dx = cos(utilitaire::DEG_TO_RAD(angleRotation_));
		double dy = sin(utilitaire::DEG_TO_RAD(angleRotation_));

		// Double l'acceleration si soumis à un bonus accelerateur
		if (bonusAcceleration_ && valeur != 0)
		{
			valeur += FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getAccelbonus();
		}

		this->acceleration_ = valeur*Vecteur3(dx, dy, 0);
	}
	else
	{
		this->acceleration_ = Vecteur3(0, 0, 0);
	}
}

void NoeudVaisseau::appliquerBonusAcceleration()
{
	bonusAcceleration_ = true;
	tempsCumuleBonus_ = 0.0f;
}

void NoeudVaisseau::devierTrajectoire(Vecteur3 axe)
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

void NoeudVaisseau::tirer()
{
	if (!this->etourdi_)
	{
		// On créé le projectile
		NoeudProjectile* projectile = static_cast<NoeudProjectile*>(FacadeModele::obtenirInstance()->creerNoeud(0, 0, ArbreRenduINF2990::NOM_PROJECTILE));

		// On applique la rotation du vaisseau au projectile
		projectile->setAngleRotation(angleRotation_);

		// On applique la position du devant du vaisseau au projectile
		Vecteur3 direction(cos(utilitaire::DEG_TO_RAD(angleRotation_)), sin(utilitaire::DEG_TO_RAD(angleRotation_)), 0);
		double distanceVaisseauProjectile = this->obtenirSphereEnglobante() + projectile->obtenirSphereEnglobante();
		projectile->assignerPositionRelative(this->positionRelative_ + direction*distanceVaisseauProjectile);

		// On calcule la vitesse du projectile selon les requis
		//this->vitesseMax_;
		projectile->setVitesse(3*this->vitesseMax_, this->vitesse_);

		// On ajoute le projectile à la liste des projectiles du vaisseau
		projectileList.push_back(projectile);
		// jouer le son de tir
		GestionnaireAudio::obtenirInstance()->jouerAudioTirProjectile();
	}
}

void NoeudVaisseau::effectuerDemiTour()
{
	if (!this->etourdi_)
	{
		this->setAngleRotation(this->angleRotation_ + 180);
	}
}

void NoeudVaisseau::toggleEtourdi()
{
	etourdi_ = true;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
