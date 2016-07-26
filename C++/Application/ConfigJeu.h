////////////////////////////////////////////////////////////////
/// classe: ConfigJeu.h
/// Najib Arbaoui
/// date 24/03/2014
/// 
///////////////////////////////////////////////////////////////

#ifndef __CONFIGURATION_CONFIGJEU_H__
#define __CONFIGURATION_CONFIGJEU_H__

#include "Singleton.h"
#include "tinyxml.h"
#include "Utilitaire.h"
#include <vector>
#include <string>
#include <NoeudComposite.h>
#include <ArbreRendu.h>
#include <NoeudAsteroide.h>
#include <NoeudBarriereProtectrice.h>
#include <NoeudBonusAccelerateur.h>
#include <NoeudPortail.h>
#include <NoeudPositionDepart.h>
#include <NoeudProjectile.h>
#include <NoeudStationSpatiale.h>
#include <NoeudVaisseau.h>
#include <NoeudZoneJeu.h.>
#include <NoeudZonePassage.h>
///////////////////////////////////////////////////////////////////////////
/// classe      ConfigJeu
///      Enregistrement et chargement des touches de configuration
///      sous forme de fichier XML.
///////////////////////////////////////////////////////////////////////////

class ConfigJeu
{
      
public : 
        
	//Constructeur 
	ConfigJeu();
	//Destructeur
	~ConfigJeu();
	//obtenir instance du visiteur
	static ConfigJeu* obtenirInstance();
	static void libererInstance();
	//chargemnt d'un fichier xml 
	void lireXml(std::string nomFichier);
	//Cr�ation fichier xml
	void creerXml(std::string nomFichier);
	//get set des touches et timer et autre....
	// set touche pour propultion vaisseau 1
	virtual void setprop1(int prop);
	// set touche pour tir vaisseau 1
	virtual void settir1(int tir);
	// set touche pour rotation horaire vaisseau 1
	void setrothor1(int hor);
	// set touche pour rotation antihoraire vaisseau 1
	void setrotantihor1(int ahor);
	// set touche pour rotation 180� vaisseau 1
	void setman1801(int man);
	// get touche pour propultion vaisseau 1
	int getprop1() const;
	// get touche pour tir vaisseau 1
	int gettir1() const;
	// get touche pour rotation horaire vaisseau 1
	int getrothor1() const;
	// get touche pour rotation 180� vaisseau 1
	int getrotantihor1() const;
	// get touche pour rotation 180� vaisseau 1
	int getman1801() const;
	// set touche pour propultion vaisseau 2
	void setprop2(int prop);
	// set touche pour tir vaisseau 2
	void settir2(int tir);
	// set touche pour rotation horaire vaisseau 2
	void setrothor2(int hor);
	// set touche pour rotation antihoraire vaisseau 2
	void setrotantihor2(int ahor);
	// set touche pour rotation 180� vaisseau 2
	void setman1802(int man);
	// get touche pour propultion vaisseau 2
	int getprop2() const;
	// get touche pour tir vaisseau 1
	int gettir2() const;
	// get touche pour rotation horaire vaisseau 2
	int getrothor2() const;
	// get touche pour rotation antihoraire vaisseau 2
	int getrotantihor2() const;
	// get touche pour rotation 180� vaisseau 2
	int getman1802() const;
	// set temps de la partie
	void settimer(int timer);
	//get temps de la partie
	int gettimer() const;
	//set temps de vie des stations spatiales
	void setptvie(int ptvie);
	//get temps de vie des stations spatiales
	int getptvie() const;
	void remisedefault();
	bool isAfficheDebug();
	bool isApparitionAsteroid(); 
	bool isChangementJoueurVirtuel();
	bool isEclairage();
	bool isCible();
	bool isCadreDepart();
	bool isZonePassage();
	bool isLimiteAttractionPortails();
	void setAfficheDebug(bool AfficheDebug);
	void setApparitionAsteroid(bool ApparitionAsteroid ); 
	void setChangementJoueurVirtuel(bool ChangementJoueurVirtuel);
	void setEclairage(bool Eclairage);
	void setCible(bool Cible);
	void setCadreDepart(bool CadreDepart);
	void setZonePassage(bool ZonePassage);
	void setLimiteAttractionPortails(bool LimiteAttractionPortails);

	//options d�bogage...
private :
	TiXmlDocument* fileXml2_;
	TiXmlElement* touchesjoueur1;
	TiXmlElement* touchesjoueur2;
	TiXmlElement* timer;
	TiXmlElement* pointvie;
	//variables touches config
	int prop1_;
	int tir1_;
	int rothor1_;
	int rotantihor1_;
	int man1801_;
	int prop2_;
	int tir2_;
	int rothor2_;
	int rotantihor2_;
	int man1802_;
	int timer_;
	int ptvie_;
	bool bAfficheDebug;
	bool bApparitionAsteroid; 
	bool bChangementJoueurVirtuel;
	bool bEclairage;
	bool bCible;
	bool bCadreDepart;
	bool bZonePassage;
	bool bLimiteAttractionPortails;


	//instance unique du visiteur Xml
	static ConfigJeu* instance_;
      
};
#endif  


