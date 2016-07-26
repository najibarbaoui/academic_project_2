///////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990.h
/// @author Martin Bisson
/// @date 2007-03-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_ARBRERENDUINF2990_H__
#define __ARBRE_ARBRERENDUINF2990_H__


#include "ArbreRendu.h"
#include "BoiteEnvironnement.h"
#include <map>
#include <string>
 class GestionnaireJeu;
///////////////////////////////////////////////////////////////////////////
/// @class ArbreRenduINF2990
/// @brief Classe qui repr�sente l'arbre de rendu sp�cifique au projet de
///        INF2990.
///
///        Cette classe s'occupe de configurer les usines des noeuds qui
///        seront utilis�s par le projet.
///
/// @author Martin Bisson
/// @date 2007-03-23
///////////////////////////////////////////////////////////////////////////
class ArbreRenduINF2990 : public ArbreRendu
{
protected:
	NoeudAbstrait* zoneJeu_;
	NoeudPositionDepart* noeudPositionDeDepart1_;
	NoeudPositionDepart* noeudPositionDeDepart2_;
	   // SkyBox
   utilitaire::BoiteEnvironnement *skyBox;
public:

   /// Constructeur par d�faut.
   ArbreRenduINF2990();
   /// Destructeur.
   virtual ~ArbreRenduINF2990();

   /// Initialise l'arbre de rendu � son �tat initial.
   void initialiser();

   bool estselectionne();

   void trouverBornesSelection(Vecteur3 &minXY, Vecteur3 &maxXY);

   bool estDansZoneJeu(const Vecteur3 minXY, const Vecteur3 maxXY);
   bool estDansCadreDepart(const Vecteur3 minXY, const Vecteur3 maxXY);
   bool estProcheZoneJeu(NoeudAbstrait* noeud);

   NoeudAbstrait* obtenirZoneJeu();
   NoeudPositionDepart* getNoeudPositionDeDepart1();
   NoeudPositionDepart* getNoeudPositionDeDepart2();
   

    // SkyBox
   void construireSkyBox();
   utilitaire::BoiteEnvironnement * obtenirSkyBox();

	/// La cha�ne repr�sentant le type des araign�es.
   static const std::string NOM_ARAIGNEE;
	/// La cha�ne repr�sentant le type des cones-cubes.
   static const std::string NOM_CONECUBE;
    /// La cha�ne repr�sentant le type des Asteroides.
   static const std::string NOM_ASTEROIDE;
	/// La cha�ne repr�sentant le type des barres protectrices.
   static const std::string NOM_BARRIEREPROTECTRICE;
    /// La cha�ne repr�sentant le type des bonus accelerateurs.
   static const std::string NOM_BONUSACCELERATEUR;
   /// La cha�ne repr�sentant le type des portails.
   static const std::string NOM_PORTAIL;
    /// La cha�ne repr�sentant le type des positions de depart.
   static const std::string NOM_POSITIONDEPART;
    /// La cha�ne repr�sentant le type des .
   static const std::string NOM_PROJECTILE;
    /// La cha�ne repr�sentant le type des .
   static const std::string NOM_STATIONSPATIALE;
    /// La cha�ne repr�sentant le type des .
   static const std::string NOM_VAISSEAU;
    /// La cha�ne repr�sentant le type des .
   static const std::string NOM_ZONEJEU;
    /// La cha�ne repr�sentant le type des .
   static const std::string NOM_ZONEPASSAGE;
    /// La cha�ne repr�sentant le type des .
   static const std::string NOM_CURSEURCROIX;
    /// La cha�ne repr�sentant le type des .
    static const std::string NOM_TAMPONPREVISUALISATION;
	  /// La cha�ne repr�sentant le type des .
    static const std::string NOM_CADREDEPART;
	 /// La cha�ne repr�sentant le type des .
    static const std::string NOM_ANIMATION;
};


#endif // __ARBRE_ARBRERENDUINF2990_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
