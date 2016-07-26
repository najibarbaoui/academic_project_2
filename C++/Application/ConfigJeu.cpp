////////////////////////////////////////////////////////////
//// ConfigJeu.cpp
//// Najib Arbaoui
//// date 24/03/2014
//// 
////////////////////////////////////////////////////////////

#include "ConfigJeu.h"
#include "FacadeModele.h"
// Pointeur vers l'instance unique de la classe.
ConfigJeu* ConfigJeu::instance_ = 0;
//const std::string ConfigJeu::FICHIER_CONFIGURATION = "configurationtouches.xml";
////////////////////////////////////////////////////////////////
// VisiteurXML::VisiteurXML()
// constructeur qui initialise un pointeur representant la racine
// du document xml
//
////     return aucun 
////
//////////////////////////////////////////////////////////////////
ConfigJeu::ConfigJeu()
{
        fileXml2_ = new TiXmlDocument();
		//set valeurs par d�faut ici
}


////////////////////////////////////////////////////////////
////     VisiteurXML::~VisiteurXML()
////
///      destructeur qui lib�re le pointeur du constructeur
///                                     
////      return aucun
////
////////////////////////////////////////////////////////////
ConfigJeu:: ~ConfigJeu()
{
        delete fileXml2_;
}
//////////////////////////////////////////////////////////////////////
/////     VisiteurXml* VisiteurXml::obtenirInstance()
/////
/////     Permet d'obtenir l'instance du visiteur xml (patron singleton)
/////     return aucun
/////
///////////////////////////////////////////////////////////////////////
ConfigJeu* ConfigJeu::obtenirInstance()
{
        if(instance_==0)
           instance_ = new ConfigJeu();
        
        return instance_;
}


/////////////////////////////////////////////////////
//  VisiteurXML::libererInstance()
/// Permet de liberer l'instance du singleton du Xml.
///     return aucun
///
//////////////////////////////////////////////////////
void ConfigJeu::libererInstance()
{
        delete instance_;
        instance_ = 0;
}



//////////////////////////////////////////////////////////////////////////////////////////
////
//// void VisiteurXml::creerFichXml(ArbreRendu* arbre,std::string nomFichier)
///
/////   Cette methode ecrit un fichier xml contenant les parametres de mise en scene
///     du jeu.
////
///       arbre : Arbre de rendu courant 
////      nomFichier : nom du fichier xml consid�r�
///
////    return aucun
///
/////////////////////////////////////////////////////////////////////////////////////////////
void ConfigJeu::creerXml(std::string nomFichier)
{      
	fileXml2_->Clear();//clear le fichier
	
			TiXmlHandle docHandle(fileXml2_);//traiter le fichier xml courant
	{
	
			
                             touchesjoueur1= new TiXmlElement("touchesjoueur1");
							 touchesjoueur2= new TiXmlElement("touchesjoueur2");
			                 timer= new TiXmlElement("timer");
							 pointvie= new TiXmlElement("pointvie");
			
			//on regle tous les parametres touche joueurs dans le fichier xml
							touchesjoueur1->SetAttribute("touche propulsion joueur 1",ConfigJeu::obtenirInstance()->getprop1());
							touchesjoueur1->SetAttribute("touche tir joueur 1",ConfigJeu::obtenirInstance()->gettir1());
						    touchesjoueur1->SetAttribute("rotation horaire joueur 1",ConfigJeu::obtenirInstance()->getrothor1());
							touchesjoueur1->SetAttribute("rotation antihoraire joueur 1",ConfigJeu::obtenirInstance()->getrotantihor1());
							touchesjoueur1->SetAttribute("manoeuvre 180 joueur 1",ConfigJeu::obtenirInstance()->getman1801());


							touchesjoueur2->SetAttribute("touche propulsion joueur 2",ConfigJeu::obtenirInstance()->getprop2());
							touchesjoueur2->SetAttribute("touche tir joueur 2",ConfigJeu::obtenirInstance()->gettir2());
						    touchesjoueur2->SetAttribute("rotation horaire joueur 2",ConfigJeu::obtenirInstance()->getrothor2());
							touchesjoueur2->SetAttribute("rotation antihoraire joueur 2",ConfigJeu::obtenirInstance()->getrotantihor2());
							touchesjoueur2->SetAttribute("manoeuvre 180 joueur 2",ConfigJeu::obtenirInstance()->getman1802());

							pointvie->SetAttribute("points de vie",ConfigJeu::obtenirInstance()->getptvie());
							timer->SetAttribute("timer partie",ConfigJeu::obtenirInstance()->gettimer());
						  //optiondebogage
								 
	}

	

	
	fileXml2_->LinkEndChild(touchesjoueur1);
	fileXml2_->LinkEndChild(touchesjoueur2);
	//fileXml2_->LinkEndChild(optiondebogage);
	fileXml2_->LinkEndChild(pointvie);
	fileXml2_->LinkEndChild(timer);
	fileXml2_->SaveFile(nomFichier.c_str());
}

////////////////////////////////////////////////////////////////////////
///
/// void VisiteurXml::lireFichXml(ArbreRendu* arbre,std::string nomFichier)
///
/// methode qui permet d'ouvrir un fichier XML pour creer
/// l'arbre de rendu.
///   
/// aucun return
///
////////////////////////////////////////////////////////////////////////
void ConfigJeu::lireXml(std::string nomFichier)
{       int prop1;
		  int tir1;
		  int rothor1;
		  int rotantihor1;
		  int man1801;
		  int prop2;
		  int tir2;
		  int rothor2;
		  int rotantihor2;
		  int man1802;
		  int timer;
		  int ptvie;
        fileXml2_->Clear();
        fileXml2_->LoadFile(nomFichier.c_str());
	    TiXmlHandle docHandle(fileXml2_);
		TiXmlElement* child = docHandle.FirstChild().ToElement();  //on accede au premier noeud du fichier xml pour joueur1
		docHandle.FirstChild().ToElement()->QueryIntAttribute("touche propulsion joueur 1",&prop1);
		docHandle.FirstChild().ToElement()->QueryIntAttribute("touche tir joueur 1",&tir1);
		docHandle.FirstChild().ToElement()->QueryIntAttribute("rotation horaire joueur 1",&rothor1);
		docHandle.FirstChild().ToElement()->QueryIntAttribute("rotation antihoraire joueur 1",&rotantihor1);
		docHandle.FirstChild().ToElement()->QueryIntAttribute("manoeuvre 180 joueur 1",&man1801);
		//set
		docHandle.FirstChild().ToElement()->NextSiblingElement()->QueryIntAttribute("touche propulsion joueur 2",&prop2);
		docHandle.FirstChild().ToElement()->NextSiblingElement()->QueryIntAttribute("touche tir joueur 2",&tir2);
		docHandle.FirstChild().ToElement()->NextSiblingElement()->QueryIntAttribute("rotation horaire joueur 2",&rothor2);
		docHandle.FirstChild().ToElement()->NextSiblingElement()->QueryIntAttribute("rotation antihoraire joueur 2",&rotantihor2);
		docHandle.FirstChild().ToElement()->NextSiblingElement()->QueryIntAttribute("manoeuvre 180 joueur 2",&man1802);
		//set les valeurs

		docHandle.FirstChild().ToElement()->NextSiblingElement()->NextSiblingElement()->QueryIntAttribute("points de vie",&ptvie);
		docHandle.FirstChild().ToElement()->NextSiblingElement()->NextSiblingElement()->NextSiblingElement()->QueryIntAttribute("timer partie",&timer);
                //docHandle.FirstChild().ToElement()->NextSiblingElement()->QueryIntAttribute("acceleration",&accel);
        //set les valeurs ici
}



  void ConfigJeu::setprop1(int prop)
{
	this->prop1_= prop;
}
   
    void ConfigJeu::settir1(int tir)
{
	this->tir1_ = tir;
}
   
    void ConfigJeu:: setrothor1(int hor)
{
	this->rothor1_ = hor;
}
   
	void ConfigJeu:: setrotantihor1(int ahor)
{
	this->rotantihor1_= ahor;
}
   void ConfigJeu:: setman1801(int man)
{
	this->man1801_ = man;
}
   void ConfigJeu:: setprop2(int prop)
{
	this->prop2_ = prop;
}
  void ConfigJeu::settir2(int tir)
{
	this->tir2_ = tir;
}
  void ConfigJeu:: setrothor2(int hor)
{
	this->rothor2_ = hor;
}
  void ConfigJeu:: setrotantihor2(int ahor)
{
	this->rotantihor2_ = ahor;
}
  void ConfigJeu:: setman1802(int man)
{
	this->man1802_ = man;
}
   
  int ConfigJeu::getprop1() const
{
	return prop1_;
}
   
  int ConfigJeu::gettir1() const
{
	return tir1_ ;
}
   
  int ConfigJeu:: getrothor1() const
{
	return rothor1_ ;
}
   
 int ConfigJeu:: getrotantihor1() const
{
	return rotantihor1_;
}
  int ConfigJeu:: getman1801() const
{
	return man1801_ ;
}
  int ConfigJeu:: getprop2() const
{
	return prop2_ ;
}
  int ConfigJeu::gettir2() const
{
	return tir2_ ;
}
  int ConfigJeu:: getrothor2() const
{
	return rothor2_ ;
}
  int ConfigJeu:: getrotantihor2() const
{
	return rotantihor2_ ;
}
  int ConfigJeu:: getman1802() const
{
	return man1802_ ;
}
   
  void ConfigJeu::settimer(int timer)
		{
	this->timer_ = timer;
}

	
	int ConfigJeu:: gettimer() const
{
	return timer_ ;
}
	
	
	int ConfigJeu:: getptvie() const
{
	return ptvie_ ;
}
	void ConfigJeu::setptvie(int ptvie)
{
	this->ptvie_ = ptvie;
}
void ConfigJeu::remisedefault()
{
	
}
bool ConfigJeu::isAfficheDebug()
{
	return bAfficheDebug;
}
bool ConfigJeu::isApparitionAsteroid()
{
	return bAfficheDebug && bApparitionAsteroid;
}
bool ConfigJeu::isChangementJoueurVirtuel()
{
	return bAfficheDebug && bChangementJoueurVirtuel;
}
bool ConfigJeu::isEclairage()
{
	return bAfficheDebug && bEclairage;
}
bool ConfigJeu::isCible()
{
	return bAfficheDebug && bCible;
}
bool ConfigJeu::isCadreDepart()
{
	return bAfficheDebug && bCadreDepart;
}
bool ConfigJeu::isZonePassage()
{
	return bAfficheDebug && bZonePassage;
}
bool ConfigJeu::isLimiteAttractionPortails()
{
	return bAfficheDebug && bLimiteAttractionPortails;
}


void ConfigJeu::setAfficheDebug(bool AfficheDebug)
{
	bAfficheDebug = AfficheDebug;
}
void  ConfigJeu::setApparitionAsteroid(bool ApparitionAsteroid )
{
	bApparitionAsteroid = ApparitionAsteroid;
}
void  ConfigJeu::setChangementJoueurVirtuel(bool ChangementJoueurVirtuel)
{
	bChangementJoueurVirtuel = ChangementJoueurVirtuel;
}
void  ConfigJeu::setEclairage(bool Eclairage)
{
	bEclairage = Eclairage;
}
void  ConfigJeu::setCible(bool Cible)
{
	bCible = Cible;
}
void  ConfigJeu::setCadreDepart(bool CadreDepart)
{
	bCadreDepart = CadreDepart;
}
void  ConfigJeu::setZonePassage(bool ZonePassage)
{
	bZonePassage = ZonePassage;
}
void  ConfigJeu::setLimiteAttractionPortails(bool LimiteAttractionPortails)
{
	bLimiteAttractionPortails = LimiteAttractionPortails;
}