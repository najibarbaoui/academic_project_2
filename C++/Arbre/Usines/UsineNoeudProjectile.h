///////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudProjectile.h
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENoeudProjectile_H__
#define __ARBRE_USINES_USINENoeudProjectile_H__


#include "UsineNoeud.h"
#include "NoeudProjectile.h"


///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudProjectile
/// @brief Classe qui représente une usine capable de créer des noeuds de
///        type NoeudProjectile.
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class UsineNoeudProjectile : public UsineNoeud
{
public:
   /// Constructeur par paramètres.
   inline UsineNoeudProjectile(const std::string& nom);

   /// Fonction à surcharger pour la création d'un noeud.
   inline virtual NoeudAbstrait* creerNoeud() const;


};


////////////////////////////////////////////////////////////////////////
///
/// @fn UsineNoeudProjectile::UsineNoeudProjectile(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres..
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds créés.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
inline UsineNoeudProjectile::UsineNoeudProjectile(const std::string& nom)
   : UsineNoeud(nom)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudProjectile::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement créé du type produit
/// par cette usine, soit une araignée.
///
/// @return Le noeud nouvellement créé.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudProjectile::creerNoeud() const
{
   return new NoeudProjectile(obtenirNom());
}


#endif // __ARBRE_USINES_USINENoeudProjectile_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
