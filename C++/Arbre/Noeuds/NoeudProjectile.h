///////////////////////////////////////////////////////////////////////////
/// @file NoeudProjectile.h
/// @author Najib Arbaoui
/// @date 2014-01-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDPROJECTILE_H__
#define __ARBRE_NOEUDS_NOEUDPROJECTILE_H__


#include "NoeudAbstrait.h"
#include "Modele3D.h"
#include <GL/gl.h>
class VisiteurAbstrait;

///////////////////////////////////////////////////////////////////////////
/// @class NoeudProjectile
/// @brief Classe qui repr�sente un exemple de noeud de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudProjectile : public NoeudAbstrait
{
public:
	/// Constructeur � partir du type du noeud.
	NoeudProjectile(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudProjectile();

	/// Affiche le cube.
	virtual void afficherConcret() const;
	/// Effectue l'animation du cube.
	virtual void animer( float temps );
	// Accepter visiteur
	virtual void accepter(VisiteurAbstrait& unVisiteur);
	// obtenir la boite qui englobe l'objet
	virtual void obtenirBoiteEnglobante(Vecteur3 &minXY, Vecteur3 &maxXY) const;
	virtual double obtenirSphereEnglobante() const;
   
	void setVitesse(double vitesseBase, Vecteur3 vitesseVaisseau);

	void detruire();
	bool isEnabled() const;
private:
	/// Mod�le 3D correspondant � ce noeud.
	Modele3D* modele_;
	/// Liste d'affichage pour l'affichage de ce noeud.
	GLuint liste_;

	Vecteur3 boiteMinXY_, boiteMaxXY_;
 
	// Emp�che de traiter ce noeud jusqu'� ce qu'il disparaisse
	bool enabled_;
	// Le temps pass� est retenu pour effacer le projectile s'il reste bloqu�
	float tempsPasse_;
};


#endif // __ARBRE_NOEUDS_NOEUDPROJECTILE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
