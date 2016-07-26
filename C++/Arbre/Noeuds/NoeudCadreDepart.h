///////////////////////////////////////////////////////////////////////////
/// @file NoeudCadreDepart.h
/// @author Najib et Oussman
/// @date 2014-01-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDCADREDEPART_H__
#define __ARBRE_NOEUDS_NOEUDCADREDEPART_H__


#include "NoeudAbstrait.h"
#include "Modele3D.h"
#include <GL/gl.h>
class VisiteurAbstrait;

///////////////////////////////////////////////////////////////////////////
/// @class NoeudCadreDepart
/// @brief Classe qui représente un exemple de noeud de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudCadreDepart : public NoeudAbstrait
{
public:
   /// Constructeur à partir du type du noeud.
   NoeudCadreDepart(const std::string& typeNoeud);
   /// Destructeur.
   ~NoeudCadreDepart();
   // Accepter visiteur
   virtual void accepter(VisiteurAbstrait& unVisiteur);
   /// Affiche le cube.
   virtual void afficherConcret() const;
   /// Effectue l'animation du cube.
   virtual void animer( float temps );
   
   virtual void obtenirBoiteEnglobante(Vecteur3 &minXY, Vecteur3 &maxXY) const;

private:
   /// Modèle 3D correspondant à ce noeud.
   Modele3D modele_;
   /// Liste d'affichage pour l'affichage de ce noeud.
   GLuint liste_;
   
   // Position de la zone de passage
   Vecteur3 minXY_, maxXY_;
};


#endif // __ARBRE_NOEUDS_NOEUDCADREDEPART_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
