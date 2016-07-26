///////////////////////////////////////////////////////////////////////////
/// @file NoeudVaisseau.h
/// @author Najib et Oussman
/// @date 2014-01-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDVAISSEAU_H__
#define __ARBRE_NOEUDS_NOEUDVAISSEAU_H__


#include "NoeudComposite.h"
#include "Modele3D.h"
#include <GL/gl.h>
#include "NoeudBonusAccelerateur.h"
#include "NoeudPositionDepart.h"
#include "NoeudProjectile.h"
#include <list>

class VisiteurAbstrait;

///////////////////////////////////////////////////////////////////////////
/// @class NoeudVaisseau
/// @brief Classe qui représente un exemple de noeud de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudVaisseau : public NoeudComposite
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudVaisseau(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudVaisseau();
	// Accepter visiteur
	virtual void accepter(VisiteurAbstrait& unVisiteur);
	/// Affiche le cube.
	virtual void afficherConcret() const;
	/// Effectue l'animation du cube.
	virtual void animer( float temps );
	void collisionZoneJeu();
   
	virtual void obtenirBoiteEnglobante(Vecteur3 &minXY, Vecteur3 &maxXY) const;
	virtual double obtenirSphereEnglobante() const;

	
   //obtenir l'angle de rotation
	virtual double getAngleRotation() const;
	void setVitesseRotation(float valeur);
	void setAcceleration(double valeur);
	void appliquerBonusAcceleration();
	void devierTrajectoire(Vecteur3 axe);
  
	void tirer();
	void effectuerDemiTour();
	void toggleEtourdi();

private:
	/// Modèle 3D correspondant à ce noeud.
	Modele3D* modele_;
	/// Liste d'affichage pour l'affichage de ce noeud.
	GLuint liste_;

	Vecteur3 boiteMinXY_, boiteMaxXY_;

	// vitesse de projectile
	// float vitesse_;
	//sens de rotation...
	bool sens_ ;
	// Est-ce que soumis à un bonus d'acceleration
	bool bonusAcceleration_;
	// Temps depuis dernier bonus acceleration
	float tempsCumuleBonus_;
	float tempsCumuleEtourdi_;

	// vitesse maximale
	double vitesseMax_;

	list<NoeudProjectile*> projectileList;

	float vitesseRotation_; // En degré par secondes

	bool etourdi_;
};

#endif // __ARBRE_NOEUDS_NOEUDVAISSEAU_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
