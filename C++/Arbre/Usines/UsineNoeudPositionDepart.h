///////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudPositionDepart.h
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENoeudPositionDepart_H__
#define __ARBRE_USINES_USINENoeudPositionDepart_H__


#include "UsineNoeud.h"
#include "NoeudPositionDepart.h"


///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudPositionDepart
/// @brief Classe qui repr�sente une usine capable de cr�er des noeuds de
///        type NoeudPositionDepart.
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class UsineNoeudPositionDepart : public UsineNoeud
{
public:
   /// Constructeur par param�tres.
   inline UsineNoeudPositionDepart(const std::string& nom);

   /// Fonction � surcharger pour la cr�ation d'un noeud.
   inline virtual NoeudAbstrait* creerNoeud() const;


};


////////////////////////////////////////////////////////////////////////
///
/// @fn UsineNoeudPositionDepart::UsineNoeudPositionDepart(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres..
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds cr��s.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
inline UsineNoeudPositionDepart::UsineNoeudPositionDepart(const std::string& nom)
   : UsineNoeud(nom)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudPositionDepart::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cr�� du type produit
/// par cette usine, soit une araign�e.
///
/// @return Le noeud nouvellement cr��.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudPositionDepart::creerNoeud() const
{
   return new NoeudPositionDepart(obtenirNom());
}


#endif // __ARBRE_USINES_USINENoeudPositionDepart_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
