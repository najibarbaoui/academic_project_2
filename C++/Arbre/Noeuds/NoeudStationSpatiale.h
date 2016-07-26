///////////////////////////////////////////////////////////////////////////
/// @file NoeudStationSpatiale.h
/// @author Najib Arbaoui
/// @date 2014-01-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDSTATIONSPATIALE_H__
#define __ARBRE_NOEUDS_NOEUDSTATIONSPATIALE_H__


#include "NoeudAbstrait.h"
#include "Modele3D.h"
#include <GL/gl.h>

///////////////////////////////////////////////////////////////////////////
/// @class NoeudStationSpatiale
/// @brief Classe qui repr�sente un exemple de noeud de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudStationSpatiale : public NoeudAbstrait
{
public:
	/// Constructeur � partir du type du noeud.
	NoeudStationSpatiale(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudStationSpatiale();

	/// Affiche le cube.
	virtual void afficherConcret() const;
	/// Effectue l'animation de station spatiale suivant un axe de rotation.
	virtual void animer( float temps );
	///animer sa destruction
	void animerDestruction(float temps);
	// Accepter visiteur
	virtual void accepter(VisiteurAbstrait& unVisiteur);
   
	// obtenir la boite qui englobe l'objet
	virtual void obtenirBoiteEnglobante(Vecteur3 &minXY, Vecteur3 &maxXY) const;
	virtual double obtenirSphereEnglobante() const;
	
	// R�initialise le noeud pour l'�tat initiale apr�s le jeu
	virtual void reinitialiser();

	void baisserPointsDeVie();
	bool isEnabled() const;

	inline int obtenirPtVie() const {
		return ptDeVie_;
	}
	void setPointDeVie(int);
	int  getPointDeVie();

private:
	/// Mod�le 3D correspondant � ce noeud.
	Modele3D* modele_;
	/// Liste d'affichage pour l'affichage de ce noeud.
	GLuint liste_;

	Vecteur3 boiteMinXY_, boiteMaxXY_;

	//points de vie
	int ptDeVie_;

	bool enabled_;

	//vitesse de rotation
	float vitesseDeRotation_;

	

};


#endif // __ARBRE_NOEUDS_NOEUDSTATIONSPATIALE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
