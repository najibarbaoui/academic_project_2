////////////////////////////////////////////////////////////////
/// classe: VisiteurXml.h
/// Najib Arbaoui
/// date 08/02/2014
/// 
///////////////////////////////////////////////////////////////

#ifndef __CONFIGURATION_VISITEURXML_H__
#define __CONFIGURATION_VISITEURXML_H__

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
#include "Noeuds/NoeudAnimation.h"
///////////////////////////////////////////////////////////////////////////
/// classe      VisiteurXml
///      traitement des diff�rents noeuds sous forme de xml.Chaque noeud 
//       a un diff�rent traitement selon son type
///////////////////////////////////////////////////////////////////////////

class VisiteurXml : public ArbreRendu
{
      
public : 
        
        //obtenir instance du visiteur
        static VisiteurXml* obtenirInstance();
        
        static void libererInstance();
        //chargemnt d'un fichier xml 
        void lireFichXml(ArbreRendu* arbre,std::string nomFichier);
        //Cr�ation fichier xml
        void creerFichXml(ArbreRendu* arbre,std::string nomFichier);
		//traite de mani�ere r�cursive un noeud fils
        void chercherecursif(NoeudAbstrait* noeudb,int nbchild,TiXmlElement* parentactu);
        //traduit en string une valeur booleene
	    std::string recupvaleurbool(bool valeur);
      //visiteur du noeud abstrait pour regler un fichier xml
      virtual  void visitNoeudAbstrait(NoeudAbstrait* noeud,TiXmlElement* parentactu);
     
        //

private :
        TiXmlDocument* fileXml_;
		  TiXmlElement* racine;
		   TiXmlElement* propriete;
        //Constructeur 
        VisiteurXml();
        //Destructeur
        ~VisiteurXml();
        //instance unique du visiteur Xml
        static VisiteurXml* instance_;
      
};
#endif  


