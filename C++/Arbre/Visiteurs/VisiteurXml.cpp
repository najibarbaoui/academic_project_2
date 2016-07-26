////////////////////////////////////////////////////////////
//// VisiteurXML.cpp
//// Najib Arbaoui
//// date 08/02/2014
//// 
////////////////////////////////////////////////////////////

#include "VisiteurXml.h"
#include "FacadeModele.h"
// Pointeur vers l'instance unique de la classe.
VisiteurXml* VisiteurXml::instance_ = 0;

////////////////////////////////////////////////////////////////
// VisiteurXML::VisiteurXML()
// constructeur qui initialise un pointeur representant la racine
// du document xml
//
////     return aucun 
////
//////////////////////////////////////////////////////////////////
VisiteurXml::VisiteurXml() : fileXml_(0)
{
	fileXml_ = new TiXmlDocument();
}


////////////////////////////////////////////////////////////
////     VisiteurXML::~VisiteurXML()
////
///      destructeur qui lib�re le pointeur du constructeur
///                                     
////      return aucun
////
////////////////////////////////////////////////////////////
VisiteurXml::~VisiteurXml()
{
	if(fileXml_) {
			delete fileXml_;
	}
}
//////////////////////////////////////////////////////////////////////
/////     VisiteurXml* VisiteurXml::obtenirInstance()
/////
/////     Permet d'obtenir l'instance du visiteur xml (patron singleton)
/////     return aucun
/////
///////////////////////////////////////////////////////////////////////
VisiteurXml* VisiteurXml::obtenirInstance()
{
        if(instance_==0)
           instance_ = new VisiteurXml();
        
        return instance_;
}


/////////////////////////////////////////////////////
//  VisiteurXML::libererInstance()
/// Permet de liberer l'instance du singleton du Xml.
///     return aucun
///
//////////////////////////////////////////////////////
void VisiteurXml::libererInstance()
{
        delete instance_;
        instance_ = 0;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// void VisiteurXML::visitNoeudAbstrait(NoeudAbstrait* noeud)
/////
//////   Methode qui visite un noeud abstrait et ajoute au fichier xml les variables du noeud parametr�es
/////    noeud : noeud abstrait � visiter
/////    return aucun
/////
////////////////////////////////////////////////////////////////////////////////////////////////////////
void VisiteurXml::visitNoeudAbstrait(NoeudAbstrait* noeud, TiXmlElement* parentactu)
{       
	TiXmlHandle docHandle(fileXml_);//traiter le fichier xml courant
	{
		if(noeud->estEnregistrable()==true)//pas necessaire pour livrable 1 
		{
			std::string parametre= noeud->obtenirType();//obtenir type du noeud abstrait
			int obtenirNombreEnfants=noeud->obtenirNombreEnfants();
			double Echelle=noeud->getEchelle();
			double Rotation=noeud->getAngleRotation();
                             
			TiXmlElement* elementconcret = new TiXmlElement(parametre.c_str());//contient type du noeud abstrait
			TiXmlElement* elementAbstrait= new TiXmlElement("abstrait");//contient parametre du noeud abstrait
			//on regle tous les parametres du noeud dans le fichier xml
			elementAbstrait->SetDoubleAttribute("Agrandissement",Echelle);
			elementAbstrait->SetDoubleAttribute("FacteurRotation",Rotation);

			if(noeud->obtenirType() == ArbreRenduINF2990::NOM_STATIONSPATIALE) {
				elementAbstrait->SetDoubleAttribute("PointDeVie", static_cast<NoeudStationSpatiale*>(noeud)->obtenirPtVie());
			}
			/*parametre=recupvaleurbool(noeud->estAffiche());
			elementAbstrait->SetAttribute("estAffiche",parametre.c_str());*/

			/*parametre=recupvaleurbool(noeud->estSelectionnable());
			elementAbstrait->SetAttribute("estSelectionnable",parametre.c_str());*/

			/*parametre=recupvaleurbool(noeud->estSelectionne());
			elementAbstrait->SetAttribute("estSelectionne",parametre.c_str());*/

			/*parametre=noeud->obtenirNombreEnfants();
			elementAbstrait->SetAttribute("obtenirNombreEnfants",obtenirNombreEnfants);*/

                             
			//enregistrement de la position du noeud
			double Vec0=noeud->obtenirPositionRelative()[0];
			double Vec1= noeud->obtenirPositionRelative()[1];
			double Vec2= noeud->obtenirPositionRelative()[2];
                          

			elementAbstrait->SetDoubleAttribute("Vec0",Vec0);
			elementAbstrait->SetDoubleAttribute("Vec1",Vec1);
			elementAbstrait->SetDoubleAttribute("Vec2",Vec2);
                           
			//on link le "noeud abstrait xml" � la racine et � son type de noeud 
			elementconcret->LinkEndChild(elementAbstrait);
			parentactu->LinkEndChild(elementconcret);
		}
	}
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
void VisiteurXml::creerFichXml(ArbreRendu* arbre,std::string nomFichier)
{  
	fileXml_->Clear();
	TiXmlDeclaration* declaration = new TiXmlDeclaration("1.0", "UTF-8", "no");
	fileXml_->LinkEndChild(declaration);  
	std::string parametre= arbre->obtenirType();//obtention type concret du noeud
	racine = new TiXmlElement(parametre.c_str());
		  
		
	for( unsigned int i = 0; i < (arbre->obtenirNombreEnfants()); i++)
	{
		if(arbre->chercher(i) != NULL)//si le noeud dans l'arbre de rendu existe, on traite
		{
			int nb =arbre->chercher(i)->obtenirNombreEnfants();
			TiXmlElement *parentactuel=racine->FirstChildElement();
			NoeudAbstrait* noeudb=arbre->chercher(i);
                                
			arbre->chercher(i)->accepterXML((*obtenirInstance()), racine);
			chercherecursif(noeudb,nb,parentactuel);//fait une recursivit� sur les noeuds fils pour le meme traitement
		}

	}
	arbre->setAccelbonus(10);
	propriete=new TiXmlElement("proprietes");
	propriete->SetAttribute("stations",arbre->getNbstatsauv());
	propriete->SetAttribute("frequence",arbre->getAsterpsec());
	propriete->SetAttribute("acceleration",arbre->getAccelbonus());
	propriete->SetAttribute("cotediff",arbre->getDifficulte());


	racine->LinkEndChild(propriete);
	fileXml_->LinkEndChild(racine);
	fileXml_->SaveFile(nomFichier.c_str());
}
//////////////////////////////////////////////////////////////////////////////////////////
////
//// void VisiteurXml::chercherecursif(NoeudAbstrait* noeudb,int nbchild,TiXmlElement* parentactu)
///
/////   Cette methode effectue de maniere r�cursive la cr�tion des noeuds fils dans le fichier xml
////
///       noeud : noeud courant 
////      parentactu : parent actuel du noeud fils
///       nbchild:nombre d'enfants du noeud parent
////    return aucun
///
/////////////////////////////////////////////////////////////////////////////////////////////
void VisiteurXml::chercherecursif(NoeudAbstrait* noeudb,int nbchild,TiXmlElement* parentactu)
{
	for(int i = 0; i < nbchild; i++)
	{
		if(noeudb->chercher(i) != NULL)
		{
			//obtention type concret du noeud
			std::string parametre= noeudb->chercher(i)->obtenirType();
			TiXmlElement * parentactuel = new TiXmlElement(parametre.c_str());
			NoeudAbstrait* noeudc= noeudb->chercher(i);
			int nb =noeudc->obtenirNombreEnfants();
                       
			noeudb->chercher(i)->accepterXML((*obtenirInstance()),parentactu);
			chercherecursif(noeudc,nb,parentactuel);
		}
	}
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
void VisiteurXml::lireFichXml(ArbreRendu* arbre,std::string nomFichier)
{      
	   TiXmlElement* obj; std::string type;
        bool estAffiche_=false,estSelectionnable_=false,estSelectionne_=false;
        double Vec0, Vec1, Vec2,rotation,agr;
        Vecteur3 position;
		  NoeudPortail * port = 0;
        fileXml_->Clear();
        fileXml_->LoadFile(nomFichier.c_str());
	    TiXmlHandle docHandle(fileXml_);
		//TiXmlElement* child = docHandle.FirstChild().ToElement()->FirstChildElement();  //on accede au premier noeud du fichier xml
		TiXmlElement* child = docHandle.FirstChildElement().FirstChildElement().Element();

      if (child!=NULL)//si le fils existe
        {
			do//tant que l'on accede � un noeud fils
			{
				if(std::string(child->Value()) == "proprietes") {
					int accel; int stat; int freq; int diffi;
					child->QueryIntAttribute("acceleration",&accel);
					arbre->setAccelbonus(accel);
					child->QueryIntAttribute("stations",&stat);
					arbre->setNbstatsauv(stat);
					child->QueryIntAttribute("frequence",&freq);
					arbre->setAsterpsec(freq);
					child->QueryIntAttribute("cotediff",&diffi);
					arbre->setDifficulte(diffi);
					child = child->NextSiblingElement();
				} else {
					obj=child;
					type=obj->Value();//type du noeud consid�r�
			
                
 
					NoeudAbstrait*noeudAjout=arbre->creerNoeud(type);//on cr�e le noeud de type pr�c�dent
	            
	            
					if(type==ArbreRenduINF2990::NOM_PORTAIL)
				   { if(port==0)
					   { port= static_cast <NoeudPortail*> (noeudAjout);}
				   else
				   {
					   port->assignerPortailFrere(noeudAjout);
					   static_cast <NoeudPortail*>(noeudAjout)->assignerPortailFrere(port);
					   port=0;
					}
					}
					//on regle la position,l'agrandissement,la rotation,la selection et l'affichage du noeud
					obj->FirstChildElement()->QueryDoubleAttribute("Vec0",&Vec0);
					obj->FirstChildElement()->QueryDoubleAttribute("Vec1",&Vec1);
					obj->FirstChildElement()->QueryDoubleAttribute("Vec2",&Vec2);
					position[0]=Vec0;position[1]=Vec1;position[2]=Vec2;
					noeudAjout->assignerPositionRelative(position);
				
					/*obj->FirstChildElement()->QueryBoolAttribute("estAffiche",&estAffiche_);
					noeudAjout->assignerAffiche(estAffiche_);*/

					/*obj->FirstChildElement()->QueryBoolAttribute("estSelectionne",&estSelectionne_);
					noeudAjout->assignerSelection(estSelectionne_);*/

					/*obj->FirstChildElement()->QueryBoolAttribute("estSelectionnable",&estSelectionnable_);
					noeudAjout->assignerEstSelectionnable(estSelectionnable_);*/

					obj->FirstChildElement()->QueryDoubleAttribute("Agrandissement",&agr);
					noeudAjout->setEchelle(agr);
		        
					obj->FirstChildElement()->QueryDoubleAttribute("FacteurRotation",&rotation);
					noeudAjout->setAngleRotation(rotation);
		       
		
					arbre->ajouter(noeudAjout);
					child = child->NextSiblingElement();
				}
	  }
	  
        
		while(child!=NULL);  }
                
        
}






////////////////////////////////////////////////////////////////////////
///
/// std::string VisiteurXml::recupvaleurbool( bool valeur)
///
/// Cette methode de recuperer un booleen  des parametres des noeud pour mettre ds le xml
///valeur du parametre � ajouter au xml(venant tres souvent de noeud abstrait)
///
/// return aucune.
/////source:https://code.google.com/p/polyputtze/source/browse/trunk/INF2990/?r=3
////////////////////////////////////////////////////////////////////////
std::string VisiteurXml::recupvaleurbool(bool valeur)
{
        if(valeur==true)
                return "1";
        else
                return "0";
}