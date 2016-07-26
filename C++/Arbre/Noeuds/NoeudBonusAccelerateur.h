///////////////////////////////////////////////////////////////////////////
/// @file NoeudBonusAccelerateur.h
/// @author Najib Arbaoui
/// @date 2014-01-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDBONUSACCELERATEUR_H__
#define __ARBRE_NOEUDS_NOEUDBONUSACCELERATEUR_H__

#include "NoeudAbstrait.h"
#include "Modele3D.h"
#include <GL/gl.h>

///////////////////////////////////////////////////////////////////////////
/// @class NoeudBonusAccelerateur
/// @brief Classe qui repr�sente un exemple de noeud de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudBonusAccelerateur : public NoeudAbstrait
{
public:
   /// Constructeur � partir du type du noeud.
   NoeudBonusAccelerateur(const std::string& typeNoeud);
   /// Destructeur.
   ~NoeudBonusAccelerateur();

   /// Affiche le cube.
   virtual void afficherConcret() const;
   /// Effectue l'animation du cube.
   virtual void animer( float temps );
   // Accepter visiteur
   virtual void accepter(VisiteurAbstrait& unVisiteur);
   
   virtual void reinitialiser();
   void disable();

    // obtenir la boite qui englobe l'objet
   virtual void obtenirBoiteEnglobante(Vecteur3 &minXY, Vecteur3 &maxXY) const;
private:
	/// Mod�le 3D correspondant � ce noeud.
	Modele3D* modele_;
	/// Liste d'affichage pour l'affichage de ce noeud.
	GLuint liste_;

   // �tat actif ou inactif
   bool actif_;

   double tempsCumuleBonus_;
};


#endif // __ARBRE_NOEUDS_NOEUDBONUSACCELERATEUR_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
