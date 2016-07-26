///////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990.cpp
/// @author Martin Bisson
/// @date 2007-03-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "ArbreRenduINF2990.h"
#include <time.h>    
#include "Utilitaire.h"
#include "EtatOpenGL.h"
#include "FacadeModele.h"
#include "GestionnaireJeu.h"
#include "Jeu\ModelManager.h"


#include "Usines/UsineNoeudAsteroide.h"
#include "Usines\UsineNoeudZoneJeu.h"
#include "Usines\UsineNoeudBarriereProtectrice.h"
#include "Usines\UsineNoeudBonusAccelerateur.h"
#include "Usines\UsineNoeudPortail.h"
#include "Usines\UsineNoeudPositionDepart.h"
#include "Usines\UsineNoeudProjectile.h"
#include "Usines\UsineNoeudStationSpatiale.h"
#include "Usines\UsineNoeudVaisseau.h"
#include "Usines\UsineNoeudZonePassage.h"
#include "Usines\UsineNoeudCurseurCroix.h"
#include "Usines\UsineNoeudTamponPrevisualisation.h"
#include "Usines\UsineNoeudCadreDepart.h"
#include "Usines\UsineNoeudAnimation.h"
#include "Visiteurs\VisiteurDeplacement.h"
#include "Visiteurs\VisiteurMiseAEchelle.h"
#include "Visiteurs\VisiteurBornesSelection.h"

/// La chaîne représentant le type des Asteroides.
  const std::string ArbreRenduINF2990::NOM_ASTEROIDE ="asteroide";
/// La chaîne représentant le type des barres protectrices.
   const std::string ArbreRenduINF2990::NOM_BARRIEREPROTECTRICE ="barriereProtectrice";
 /// chaîne représentant le type des bonus accelerateurs.
  const std::string ArbreRenduINF2990::NOM_BONUSACCELERATEUR="bonusAccelerateur";
/// La chaîne représentant le type des portails.
   const std::string ArbreRenduINF2990::NOM_PORTAIL="portail";
/// La chaîne représentant le type des positions de depart.
   const std::string ArbreRenduINF2990::NOM_POSITIONDEPART="positionDepart";
/// La chaîne représentant le type des .
   const std::string ArbreRenduINF2990::NOM_PROJECTILE="projectile";
/// La chaîne représentant le type des .
   const std::string ArbreRenduINF2990::NOM_STATIONSPATIALE="stationSpatiale";
/// La chaîne représentant le type des .
   const std::string ArbreRenduINF2990::NOM_VAISSEAU="vaisseau";
/// La chaîne représentant le type des .
   const std::string ArbreRenduINF2990::NOM_ZONEJEU="zoneJeu";
/// La chaîne représentant le type des .
   const std::string ArbreRenduINF2990::NOM_ZONEPASSAGE="zonePassage";
/// La chaîne représentant le type des .
   const std::string ArbreRenduINF2990::NOM_CURSEURCROIX="curseurCroix";
/// La chaîne représentant le type des .
   const std::string ArbreRenduINF2990::NOM_TAMPONPREVISUALISATION="tamponPrevisualisation";

/// La chaîne représentant le type des .
   const std::string ArbreRenduINF2990::NOM_CADREDEPART="cadreDepart";
   /// La chaîne représentant le type des .
   const std::string ArbreRenduINF2990::NOM_ANIMATION = "animation";


////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRenduINF2990::ArbreRenduINF2990()
///
/// Ce constructeur crée toutes les usines qui seront utilisées par le
/// projet de INF2990et les enregistre auprès de la classe de base.
/// Il crée également la structure de base de l'arbre de rendu, c'est-à-dire
/// avec les noeuds structurants.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRenduINF2990::ArbreRenduINF2990()
{
  
	zoneJeu_ = 0;
	// Construction des usines
	ajouterUsine(NOM_ASTEROIDE , new UsineNoeudAsteroide(NOM_ASTEROIDE));
	ajouterUsine(NOM_BARRIEREPROTECTRICE , new UsineNoeudBarriereProtectrice(NOM_BARRIEREPROTECTRICE));
	ajouterUsine(NOM_BONUSACCELERATEUR , new UsineNoeudBonusAccelerateur(NOM_BONUSACCELERATEUR));
	ajouterUsine(NOM_PORTAIL , new UsineNoeudPortail(NOM_PORTAIL));
	ajouterUsine(NOM_POSITIONDEPART , new UsineNoeudPositionDepart(NOM_POSITIONDEPART));
	ajouterUsine(NOM_PROJECTILE , new UsineNoeudProjectile(NOM_PROJECTILE));
	ajouterUsine(NOM_STATIONSPATIALE , new UsineNoeudStationSpatiale(NOM_STATIONSPATIALE));
	ajouterUsine(NOM_VAISSEAU , new UsineNoeudVaisseau(NOM_VAISSEAU));
	ajouterUsine(NOM_ZONEPASSAGE , new UsineNoeudZonePassage(NOM_ZONEPASSAGE));
	ajouterUsine(NOM_ZONEJEU , new UsineNoeudZoneJeu(NOM_ZONEJEU));
	ajouterUsine(NOM_CURSEURCROIX , new UsineNoeudCurseurCroix(NOM_CURSEURCROIX));
	ajouterUsine(NOM_TAMPONPREVISUALISATION , new UsineNoeudTamponPrevisualisation(NOM_TAMPONPREVISUALISATION));
	ajouterUsine(NOM_CADREDEPART , new UsineNoeudCadreDepart(NOM_CADREDEPART));
	ajouterUsine(NOM_ANIMATION , new UsineNoeudAnimation(NOM_ANIMATION));
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRenduINF2990::~ArbreRenduINF2990()
///
/// Ce destructeur ne fait rien pour le moment.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRenduINF2990::~ArbreRenduINF2990()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990::initialiser()
///
/// Cette fonction crée la structure de base de l'arbre de rendu, c'est-à-dire
/// avec les noeuds structurants (pour les objets, les murs, les billes,
/// les parties statiques, etc.)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::initialiser()
{
	ModelManager::obtenirInstance()->loadModels();

	// On vide l'arbre
	vider();
	
	// initialiser pour génération des randoms
	srand (static_cast<unsigned int>(time(NULL)));

	// construire le skyBox
    construireSkyBox();
	// Zone de jeu
	zoneJeu_ = creerNoeud(ArbreRenduINF2990::NOM_ZONEJEU);
	ajouter(zoneJeu_);
	// position de depart
	noeudPositionDeDepart1_ = static_cast<NoeudPositionDepart*>(creerNoeud(ArbreRenduINF2990::NOM_POSITIONDEPART));
	noeudPositionDeDepart2_ = static_cast<NoeudPositionDepart*>(creerNoeud(ArbreRenduINF2990::NOM_POSITIONDEPART));
	noeudPositionDeDepart1_->assignerPositionRelative(Vecteur3(-200, 0, 0));
	noeudPositionDeDepart2_->assignerPositionRelative(Vecteur3(200, 0, 0));
	ajouter(noeudPositionDeDepart1_);
	ajouter(noeudPositionDeDepart2_);
	
}

NoeudAbstrait* ArbreRenduINF2990::obtenirZoneJeu()
{
	return zoneJeu_;
}

NoeudPositionDepart* ArbreRenduINF2990::getNoeudPositionDeDepart1()
{
	double noeud1X = noeudPositionDeDepart1_->obtenirPositionRelative()[0];
	double noeud2X = noeudPositionDeDepart2_->obtenirPositionRelative()[0];

	if (noeud1X < noeud2X)
	{
		return noeudPositionDeDepart1_;
	}
	else
	{
		return noeudPositionDeDepart2_;
	}
}

NoeudPositionDepart* ArbreRenduINF2990::getNoeudPositionDeDepart2()
{
	double noeud1X = noeudPositionDeDepart1_->obtenirPositionRelative()[0];
	double noeud2X = noeudPositionDeDepart2_->obtenirPositionRelative()[0];

	if (noeud1X < noeud2X)
	{
		return noeudPositionDeDepart2_;
	}
	else
	{
		return noeudPositionDeDepart1_;
	}
}

void ArbreRenduINF2990::trouverBornesSelection(Vecteur3 &minXY, Vecteur3 &maxXY)
{
	VisiteurBornesSelection v;

	this->accepter(v);

	v.getBornesSelection(minXY, maxXY);
}

bool ArbreRenduINF2990::estDansZoneJeu(const Vecteur3 minXY, const Vecteur3 maxXY)
{
	// Obtient les limites de la zone de jeu
	Vecteur3 minXYZoneJeu, maxXYZoneJeu;
	this->zoneJeu_->obtenirBoiteEnglobante(minXYZoneJeu, maxXYZoneJeu);

	if(utilitaire::ALMOST_EQUALS(min(minXYZoneJeu[0], minXY[0]), minXYZoneJeu[0]) &&
		utilitaire::ALMOST_EQUALS(min(minXYZoneJeu[1], minXY[1]), minXYZoneJeu[1]) &&
		utilitaire::ALMOST_EQUALS(max(maxXYZoneJeu[0], maxXY[0]), maxXYZoneJeu[0]) &&
		utilitaire::ALMOST_EQUALS(max(maxXYZoneJeu[1], maxXY[1]), maxXYZoneJeu[1]))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ArbreRenduINF2990::estDansCadreDepart(const Vecteur3 minXY, const Vecteur3 maxXY)
{
	// Obtient les limites du cadre  de jeu
	Vecteur3 minXYCadreJeu, maxXYCadreJeu;
	GestionnaireJeu::obtenirInstance()->obtenirCadreDepartAsteroide(minXYCadreJeu ,  maxXYCadreJeu );

	if(utilitaire::ALMOST_EQUALS(min( minXYCadreJeu[0], minXY[0]),  minXYCadreJeu[0]) &&
		utilitaire::ALMOST_EQUALS(min( minXYCadreJeu[1], minXY[1]),  minXYCadreJeu[1]) &&
		utilitaire::ALMOST_EQUALS(max(maxXYCadreJeu[0], maxXY[0]), maxXYCadreJeu[0]) &&
		utilitaire::ALMOST_EQUALS(max(maxXYCadreJeu[1], maxXY[1]), maxXYCadreJeu[1]))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ArbreRenduINF2990::estProcheZoneJeu(NoeudAbstrait* noeud)
{
	// Obtient les limites de la zone de jeu
	Vecteur3 minXYZoneJeu, maxXYZoneJeu;
	this->zoneJeu_->obtenirBoiteEnglobante(minXYZoneJeu, maxXYZoneJeu);
	minXYZoneJeu *= 0.8;
	maxXYZoneJeu *= 0.8;

	Vecteur3 minXY, maxXY;
	noeud->obtenirBoiteEnglobante(minXY, maxXY);

	if(utilitaire::ALMOST_EQUALS(min(minXYZoneJeu[0], minXY[0]), minXYZoneJeu[0]) &&
		utilitaire::ALMOST_EQUALS(min(minXYZoneJeu[1], minXY[1]), minXYZoneJeu[1]) &&
		utilitaire::ALMOST_EQUALS(max(maxXYZoneJeu[0], maxXY[0]), maxXYZoneJeu[0]) &&
		utilitaire::ALMOST_EQUALS(max(maxXYZoneJeu[1], maxXY[1]), maxXYZoneJeu[1]))
	{
		return false;
	}
	else
	{
		return true;
	}
}

//////////////////////////// SkyBox ////////////////////////////////////

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::construireSkyBox()
///
/// Cette fonction 
/// @return 
///
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::construireSkyBox()
{
	
	const std::string fichierXpos("media/skybox/right.jpg");
	const std::string fichierXneg("media/skybox/left.jpg");
	const std::string fichierYpos("media/skybox/front.jpg"); 
	const std::string fichierYneg("media/skybox/back.jpg");
	const std::string fichierZpos("media/skybox/top.jpg");
	const std::string fichierZneg("media/skybox/bottom.jpg");
	skyBox = new utilitaire::BoiteEnvironnement(fichierXneg,fichierXpos,fichierYpos,fichierYneg,fichierZneg, fichierZpos);

}
////////////////////////////////////////////////////////////////////////
///
/// @fn utilitaire::BoiteEnvironnement * FacadeModele::obtenirSkyBox()
///
/// Cette fonction 
/// @return 
///
///
////////////////////////////////////////////////////////////////////////
   utilitaire::BoiteEnvironnement * ArbreRenduINF2990::obtenirSkyBox()
{
   return this->skyBox ;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
