///////////////////////////////////////////////////////////////////////////
/// @file NoeudTamponPrevisualisation.h
/// @author Najib Arbaoui
/// @date 2014-01-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NoeudTamponPrevisualisation_H__
#define __ARBRE_NOEUDS_NoeudTamponPrevisualisation_H__


#include "NoeudAbstrait.h"
#include "Modele3D.h"
#include <GL/gl.h>

///////////////////////////////////////////////////////////////////////////
/// @class NoeudTamponPrevisualisation
/// @brief Classe qui repr�sente un exemple de noeud de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudTamponPrevisualisation: public NoeudAbstrait
{
public:
   /// Constructeur � partir du type du noeud.
   NoeudTamponPrevisualisation(const std::string& typeNoeud);
   /// Destructeur.
   ~NoeudTamponPrevisualisation();

   /// Affiche le cube.
   virtual void afficherConcret() const;
   /// Effectue l'animation de station spatiale suivant un axe de rotation.
   virtual void animer( float temps );
   ///animer sa destruction
   void animerDestruction(float temps);
   // Accepter visiteur
   virtual void accepter(VisiteurAbstrait& unVisiteur);
   
	 // tracer le tampon
   virtual void tracerTampon(Vecteur3 minXY, Vecteur3 maxXY);
   	 // obtenir la boite qui englobe l'objet
   virtual void obtenirBoiteEnglobante(Vecteur3 &minXY, Vecteur3 &maxXY) const;

private:
   /// Mod�le 3D correspondant � ce noeud.
   Modele3D modele_;
   /// Liste d'affichage pour l'affichage de ce noeud.
   GLuint liste_;

    //points de vie
   int ptDeVie_;
   //La masse de la station
   float masse_;
   //vitesse de rotation
   float vitesseDeRotation_;
   //bornes 
   Vecteur3  borneMinXY_ ,  borneMaxXY_ ;
 
};


#endif // __ARBRE_NOEUDS_NoeudTamponPrevisualisation_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
