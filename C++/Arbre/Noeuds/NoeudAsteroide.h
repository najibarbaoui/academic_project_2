///////////////////////////////////////////////////////////////////////////
/// @file NoeudAsteroide.h
/// @author Najib Arbaoui
/// @date 2014-01-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDASTEROIDE_H__
#define __ARBRE_NOEUDS_NOEUDASTEROIDE_H__

#include "NoeudAbstrait.h"
#include "Modele3D.h"
#include <GL/gl.h>
#include "NoeudPositionDepart.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudAsteroide
/// @brief Classe qui repr�sente un exemple de noeud de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudAsteroide : public NoeudAbstrait
{
public:
	/// Constructeur � partir du type du noeud.
	NoeudAsteroide(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudAsteroide();

	/// Affiche le cube.
	virtual void afficherConcret() const;
	/// Effectue l'animation du cube.
	virtual void animer( float temps );
	// Accepter visiteur
	virtual void accepter(VisiteurAbstrait& unVisiteur);
  
	virtual void obtenirBoiteEnglobante(Vecteur3 &minXY, Vecteur3 &maxXY) const;
	virtual double obtenirSphereEnglobante() const;
	
	void devierTrajectoire(Vecteur3 axe);

	int getPointsDeVie();
	void setPointsDeVie(int pointsDeVie);

	Vecteur3 getVitesse();
	void setVitesse(Vecteur3 vitesse);

    bool isEnabled() const;
	void setEnabled(bool value);
	void setCoteOuCree(int cote);
	int getCoteOuCree();
	void baisserPointsDeVie();

	std::string TimeToString() const;
	void SortieConsole() const;

private:
	/// Mod�le 3D correspondant � ce noeud.
	Modele3D* modele_;
	/// Liste d'affichage pour l'affichage de ce noeud.
	GLuint liste_;

   // points de vie
   int pointsDeVie_;
   // Emp�che de traiter ce noeud jusqu'� ce qu'il disparaisse
	bool enabled_;
      // vitesse de projectile
  // float vitesse_;
   //sens de rotation...
   bool sens_ ;

   // cote ou il est cr�e
   unsigned int coteOuCree_;
   Vecteur3 direction_;

   // angle
   float angle_;
};


#endif // __ARBRE_NOEUDS_NOEUDASTEROIDE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
