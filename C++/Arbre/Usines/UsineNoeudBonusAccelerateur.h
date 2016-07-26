///////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudBonusAccelerateur.h
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENoeudBonusAccelerateur_H__
#define __ARBRE_USINES_USINENoeudBonusAccelerateur_H__


#include "UsineNoeud.h"
#include "NoeudBonusAccelerateur.h"


///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudBonusAccelerateur
/// @brief Classe qui représente une usine capable de créer des noeuds de
///        type NoeudBonusAccelerateur.
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class UsineNoeudBonusAccelerateur : public UsineNoeud
{
public:
   /// Constructeur par paramètres.
   inline UsineNoeudBonusAccelerateur(const std::string& nom);

   /// Fonction à surcharger pour la création d'un noeud.
   inline virtual NoeudAbstrait* creerNoeud() const;


};


////////////////////////////////////////////////////////////////////////
///
/// @fn UsineNoeudBonusAccelerateur::UsineNoeudBonusAccelerateur(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres..
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds créés.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
inline UsineNoeudBonusAccelerateur::UsineNoeudBonusAccelerateur(const std::string& nom)
   : UsineNoeud(nom)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudBonusAccelerateur::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement créé du type produit
/// par cette usine, soit une araignée.
///
/// @return Le noeud nouvellement créé.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudBonusAccelerateur::creerNoeud() const
{
   return new NoeudBonusAccelerateur(obtenirNom());
}


#endif // __ARBRE_USINES_USINENoeudBonusAccelerateur_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
