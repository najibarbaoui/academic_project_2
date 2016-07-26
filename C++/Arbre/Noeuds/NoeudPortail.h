///////////////////////////////////////////////////////////////////////////
/// @file NoeudPortail.h
/// @author Najib Arbaoui
/// @date 2014-01-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDPORTAIL_H__
#define __ARBRE_NOEUDS_NOEUDPORTAIL_H__

#include "NoeudAbstrait.h"
#include "Modele3D.h"
#include <GL/gl.h>

///////////////////////////////////////////////////////////////////////////
/// @class NoeudPortail
/// @brief Classe qui repr�sente un exemple de noeud de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudPortail : public NoeudAbstrait
{
public:
   /// Constructeur � partir du type du noeud.
   NoeudPortail(const std::string& typeNoeud);
   /// Destructeur.
   ~NoeudPortail();

   /// Affiche le cube.
   virtual void afficherConcret() const;
   /// Effectue l'animation du cube.
   virtual void animer( float temps );
   // Accepter visiteur
   virtual void accepter(VisiteurAbstrait& unVisiteur);

   void setEnabled(bool value);

   // Assigner le frere du portail
   void assignerPortailFrere(NoeudAbstrait* frere);
   // Obtenir le frere du portail
   NoeudAbstrait* obtenirPortailFrere();
   void teleporterNoeud(NoeudAbstrait* noeud);

    // obtenir la boite qui englobe l'objet
   virtual void obtenirBoiteEnglobante(Vecteur3 &minXY, Vecteur3 &maxXY) const;
	virtual double obtenirSphereEnglobante() const;

   /// Efface les enfants s�lectionn�s.
   virtual void effacerSelection();
private:
	/// Mod�le 3D correspondant � ce noeud.
	Modele3D* modele_;
	/// Liste d'affichage pour l'affichage de ce noeud.
	GLuint liste_;

	Vecteur3 boiteMinXY_, boiteMaxXY_;

	NoeudAbstrait* frere_;
	NoeudAbstrait* noeudTeleporte_;

	// rayon portail
	float rayon_;
	// la port�e du champ
	float limite;
	// etat du champ d attraction actif ou inactif
	bool enabled_;

	void appliquerChampAttraction();
};


#endif // __ARBRE_NOEUDS_NOEUDPORTAIL_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
