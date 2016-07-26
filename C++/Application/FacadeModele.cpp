///////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.cpp
/// @author Martin Bisson
/// @date 2007-05-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////


// Commentaire Doxygen mis sur la première page de la documentation Doxygen.
/**

@mainpage Projet intégrateur de deuxième année -- INF2990

@li <a href="../javadoc/index.html">Documentation Javadoc de la partie Java.</a>
*/

#include <windows.h>
#include <GL/GL.h>
#include <cassert>

#include <sstream>
#include<iostream>

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "FreeImage.h"

#include "FacadeModele.h"


#include "VueOrtho.h"
#include "VuePerspective.h"
#include "Camera.h"
#include "Projection.h"

#include "Utilitaire.h"
#include "AideGL.h"
#include "AideCollision.h"
#include "Droite3D.h"
#include "GestionnaireJeu.h"
#include "Jeu\ModelManager.h"
#include "ArbreRenduINF2990.h"
#include "Visiteurs\VisiteurSelection.h"
#include "Visiteurs\VisiteurSuppression.h"
#include "..\Arbre\Visiteurs\VisiteurDeplacement.h"
#include "..\Arbre\Visiteurs\VisiteurMiseAEchelle.h"
#include "..\Arbre\Visiteurs\VisiteurRotation.h"
#include "..\Arbre\Visiteurs\VisiteurBornesSelection.h"
#include "..\Arbre\Visiteurs\VisiteurDuplication.h"
#include "..\Arbre\Visiteurs\VisiteurAfficherTexte.h"


#include "ConfigScene.h"
#include "EtatModele\EtatModeleMenu.h"
#include "EtatModele\EtatModeleEditeur.h"
#include "EtatModele\EtatModeleJeu.h"
#include "EtatModele\EtatModeleModeTest.h"
#include "EtatModele\EtatModelePartieRapide.h"
#include "EtatModele\EtatModeleCampagne.h"
#include <vector>
// Remlacement de EnveloppeXML/XercesC par TinyXML
// Julien Gascon-Samson, été 2011
#include "tinyxml.h"
#include "NoeudZonejeu.h"
#include "CompteurAffichage.h"
#include "math.h"


/// Pointeur vers l'instance unique de la classe.
FacadeModele* FacadeModele::instance_ = 0;

/// Chaîne indiquant le nom du fichier de configuration du projet.
const std::string FacadeModele::FICHIER_CONFIGURATION = "configuration.xml";

////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele* FacadeModele::obtenirInstance()
///
/// Cette fonction retourne un pointeur vers l'instance unique de la
/// classe.  Si cette instance n'a pas été créée, elle la crée.  Cette
/// création n'est toutefois pas nécessairement "thread-safe", car
/// aucun verrou n'est pris entre le test pour savoir si l'instance
/// existe et le moment de sa création.
///
/// @return Un pointeur vers l'instance unique de cette classe.
///
////////////////////////////////////////////////////////////////////////
FacadeModele* FacadeModele::obtenirInstance()
{
   if (instance_ == 0)
      instance_ = new FacadeModele();

   return instance_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::libererInstance()
///
/// Cette fonction libère l'instance unique de cette classe.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::libererInstance()
{
	if (instance_ != 0)
	{
		delete instance_;
		instance_ = 0;
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele::FacadeModele()
///
/// Ce constructeur par défaut ne fait qu'initialiser toutes les
/// variables à une valeur nulle.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
FacadeModele::FacadeModele()
 : hGLRC_(0), hDC_(0), hWnd_(0), vue_(0), arbre_(0), etat_(0),afficherTexte_(false),lumiereAmbiante(false),lumiereDirectionnelle(false),lumiereSpot(false)
{
	m_mapInstance.insert(pair<EtatId, std::shared_ptr<EtatModeleAbstrait> >(ETATMENU,			new EtatModeleMenu()));
	m_mapInstance.insert(pair<EtatId, std::shared_ptr<EtatModeleAbstrait> >(ETATEDITEUR,		new EtatModeleEditeur()));
	m_mapInstance.insert(pair<EtatId, std::shared_ptr<EtatModeleAbstrait> >(ETATJEU,			new EtatModeleJeu()));
	m_mapInstance.insert(pair<EtatId, std::shared_ptr<EtatModeleAbstrait> >(ETATCONFIGURATION,	new EtatModeleMenu()));
	m_mapInstance.insert(pair<EtatId, std::shared_ptr<EtatModeleAbstrait> >(ETATMODETEST,		new EtatModeleModeTest()));
	m_mapInstance.insert(pair<EtatId, std::shared_ptr<EtatModeleAbstrait> >(ETATPARTIERAPIDE,	new EtatModelePartieRapide()));
	m_mapInstance.insert(pair<EtatId, std::shared_ptr<EtatModeleAbstrait> >(ETATCAMPAGNE,		new EtatModeleCampagne()));

	m_mapInstanceVue.insert(pair<TypeVue, vue::Vue*>(ORTHO, new vue::VueOrtho(
		vue::Camera(Vecteur3(0, 0, 200), Vecteur3(0, 0, 0),
		Vecteur3(0, 1, 0)  , Vecteur3(0, 1, 0)),
		0, 720, 0, 480,
		1, 1000, 1, 650, 1.25,
		-160, 160, -90, 90
		)
	));

	m_mapInstanceVue.insert(pair<TypeVue, vue::Vue*>(
		PERSPECTIVE,
		new vue::VuePerspective(
		vue::Camera(Vecteur3(0, 0, 400),
		Vecteur3(0, 0, 0), Vecteur3(0, 1, 0),
		Vecteur3(0, 1, 0)),
		0, 720, 0, 480,
		1, 1000, 1, 9, 1.25,
		-.96, .96, -.54, .54
		)
		));

	etat_ = m_mapInstance[ETATMENU];

	vueOrthographique_ = false;

	// Un noeud selectionne unique
	noeudSelectionUnique = NULL;
	arbre_ = new ArbreRenduINF2990();
	
	fichierSauvegarde = "";

	vue_ = NULL;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele::~FacadeModele()
///
/// Ce destructeur libère les objets du modèle.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
FacadeModele::~FacadeModele()
{
   delete arbre_;
   delete vue_;
}
//FacadeModele::afficherLesTetxes()
//{
//	glRasterPos2f(x,y); // Positionne le premier caractère de la chaîne
//	len = (int) strlen(string); // Calcule la longueur de la chaîne
//	for (i = 0; i < len; i++) glutBitmapCharacter(font,string[i]); // Affiche chaque caractère de la chaîne
//}

void vStrokeOutput(GLfloat x, GLfloat y, char *string, void *font)
{
	//char *p;

	//glPushMatrix();	// glPushMatrix et glPopMatrix sont utilisées pour sauvegarder 
	//		// et restaurer les systèmes de coordonnées non translatés
	//glTranslatef(x, y, 0); // Positionne le premier caractère de la chaîne
	//for (p = string; *p; p++) glutStrokeCharacter(font, *p); // Affiche chaque caractère de la chaîne
	//glPopMatrix();
}

void vDisplay() 
{ 
	////glClearColor(0,0,0,0);
	//glClearColor(1,1,1,1);
	//glClear(GL_COLOR_BUFFER_BIT);

	//glColor3d(1,1,1); // Texte en blanc
	////vBitmapOutput(0,0,"Blanc HELVETICA",GLUT_BITMAP_HELVETICA_18);
	//glFlush(); 
} 



////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::initialiserOpenGL(HWND hWnd)
///
/// Cette fonction permet d'initialiser le contexte OpenGL.  Elle crée
/// un contexte OpenGL sur la fenêtre passée en paramètre, initialise
/// FreeImage (utilisée par le chargeur 3DS) et assigne des paramètres
/// du contexte OpenGL.
///
/// @param[in] hWnd : La poignée ("handle") vers la fenêtre à utiliser.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::initialiserOpenGL(HWND hWnd)
{
	
   hWnd_ = hWnd;
   bool succes = aidegl::creerContexteGL(hWnd_, hDC_, hGLRC_);
   assert(succes);

   // Initialisation de la configuration
   chargerConfiguration();

   // FreeImage, utilisée par le chargeur, doit être initialisée
   FreeImage_Initialise();

   // La couleur de fond
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
   

   // Les lumières
   glEnable( GL_LIGHTING );
  // glLightModelf( GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE );
   glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE );
   glEnable( GL_COLOR_MATERIAL );

   glEnable(GL_LIGHT0);
   GLfloat shinin[] = { 128.0 };
		glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS,shinin );

   // Qualité
   glShadeModel( GL_SMOOTH );
   glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
   
   // Profondeur
   glEnable( GL_DEPTH_TEST );

   // Le cull face
   glEnable( GL_CULL_FACE );
   glCullFace( GL_BACK );

   // Création de l'arbre de rendu.  À moins d'être complètement certain
   // d'avoir une bonne raison de faire autrement, il est plus sage de créer
   // l'arbre après avoir créé le contexte OpenGL.
  /* arbre_ = new ArbreRenduINF2990();
   arbre_->initialiser();*/
  // arbre_->misAEchelle(0.0);
   // On crée une vue par défaut.
   
   this->activerVueOrthogonale();

	// Charger les modeles
	ModelManager::obtenirInstance()->loadModels();
 
	// Initialisation.
	reinitialiser();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAsteroide::SortieConsole() const
///
/// Quand un astéroïde est créé, la ligne suivante doit être affichée à la console:
/// HH:MM:SS:mm Création d'astéroìde x: POSX	y: POSY	vi: VI	t: T
///
/// Où POSX représente la position en x, POSY la position en Y, VI le module de la vitesse initiale, T la taille de l’astéroïde.
///
/// @param Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::SortieConsole(std::string strLum, bool bEtat) const
{
	const char* tab = "\t";
	std::string strTime = utilitaire::TimeToString();
	std::string strEtat = (bEtat) ? "ouverte" : "fermee";
	std::cout << strTime << " - " << "Lumiere : " << strLum << tab << strEtat << endl; 
}

bool FacadeModele::getLumiereAmbiante()
{
	 return lumiereAmbiante;
}
bool FacadeModele::getLumiereDirectionnelle()
{
	 return lumiereDirectionnelle;
 }
bool FacadeModele::getLumiereSpot()
{
	 return lumiereSpot;
}
void FacadeModele::setLumiereAmbiante(bool Ambiante)
{
	SortieConsole("Ambiante", Ambiante);
	lumiereAmbiante = Ambiante;
}

void FacadeModele::setLumiereDirectionnelle(bool directionnelle)
{
	SortieConsole("directionnelle", directionnelle);
	lumiereDirectionnelle = directionnelle;
}
 void FacadeModele::setLumiereSpot(bool Spot)
 {
	 SortieConsole("Spot", Spot);
	 lumiereSpot = Spot;
 }
HDC FacadeModele::obtenirContexte()
{
	return hDC_;
}

HGLRC  FacadeModele::obtenirContexteHglrc()
{
	return hGLRC_;
}

HWND  FacadeModele::obtenirContexteHwnd()
{
	return  hWnd_;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::chargerConfiguration() const
///
/// Cette fonction charge la configuration à partir d'un fichier XML si
/// ce dernier existe.  Sinon, le fichier de configuration est généré à
/// partir de valeurs par défaut directement dans le code.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::chargerConfiguration() const
{
   // Vérification de l'existance du ficher

   // Si le fichier n'existe pas, on le crée.
   if ( !utilitaire::fichierExiste(FICHIER_CONFIGURATION) ) {
      enregistrerConfiguration();
   }
   // si le fichier existe on le lit
   else {
		TiXmlDocument document;

		// Lire à partir du fichier de configuration
		document.LoadFile ( FacadeModele::FICHIER_CONFIGURATION.c_str() );
      
      // On lit les différentes configurations.
      ConfigScene::obtenirInstance()->lireDOM(document);
   }
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::enregistrerConfiguration() const
///
/// Cette fonction génère un fichier XML de configuration à partir de
/// valeurs par défaut directement dans le code.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::enregistrerConfiguration() const
{
	TiXmlDocument document;

	// Écrire la déclaration XML standard...
	TiXmlDeclaration* declaration = new TiXmlDeclaration( "1.0", "", "" );
	document.LinkEndChild(declaration);

   // On enregistre les différentes configurations.
   ConfigScene::obtenirInstance()->creerDOM(document);

   // Écrire dans le fichier
	document.SaveFile( FacadeModele::FICHIER_CONFIGURATION.c_str() );
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::enregistrerXml(std::string nomfichier ) 
///
/// Cette fonction génère un fichier XML contenant l'arbre de rendu 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::enregistrerXml(std::string nomfichier ) 
{
	if (fichierSauvegarde == "" && nomfichier == "")
	{
		assert(false);
	}

	if (nomfichier == "")
	{
		nomfichier = fichierSauvegarde;
	}
	else
	{
		fichierSauvegarde = nomfichier;
	}

	VisiteurXml* visiteur=VisiteurXml::obtenirInstance();
        
	visiteur->creerFichXml(arbre_, nomfichier);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::chargerXml(std::string nomfichier)
///
/// Cette fonction charge l'arbre de rendu à partir d'un fichier de sauvegarde 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::chargerXml(std::string nomfichier)
{
	// Réinitialiser l'arbre
	this->reinitialiser();

	VisiteurXml* visiteur=VisiteurXml::obtenirInstance();
	visiteur->lireFichXml(arbre_, nomfichier);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::fichierSauvegardeEstDefini()
///
/// Cette fonction retourne si le fichier de sauvegarde est défini
///
/// @return bool Vrai si le fichier de sauvegarde est défini, faux sinon.
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::fichierSauvegardeEstDefini()
{
	return !(fichierSauvegarde == "");
}

void FacadeModele::assignerFichierSauvegarde(string nomFichier)
{
	fichierSauvegarde = nomFichier;
}


string FacadeModele::obtenirNomFichierSauvegarde()
{
	return fichierSauvegarde;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::libererOpenGL()
///
/// Cette fonction libère le contexte OpenGL et désinitialise FreeImage.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::libererOpenGL()
{
   utilitaire::CompteurAffichage::libererInstance();

   // On libère les instances des différentes configurations.
   ConfigScene::libererInstance();

   bool succes = aidegl::detruireContexteGL(hWnd_, hDC_, hGLRC_);
   assert(succes);

   FreeImage_DeInitialise();

   // Charger les modeles
   ModelManager::obtenirInstance()->unloadModels();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficher() const
///
/// Cette fonction affiche le contenu de la scène.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficher() const
{
	
	
	// Efface l'ancien rendu
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );

	// Ne devrait pas être nécessaire
	vue_->appliquerProjection();

	// Positionne la caméra
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	vue_->appliquerCamera();
	
	// skybox

	Vecteur3 centre(0,0,0) /*= vue_->obtenirCamera().obtenirPosition()*/;
   /*glPushMatrix();*/
   FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirSkyBox()->afficher(centre, 320);
   /*glPopMatrix();*/
	

	// Afficher la scène
	afficherBase();
	// afficher les textes a savoir la minuterie et les points de vie des stations spatiales
	afficherLesTetxes(afficherTexte_);
	
	// Compte de l'affichage
	utilitaire::CompteurAffichage::obtenirInstance()->signalerAffichage();

	// Échange les tampons pour que le résultat du rendu soit visible.
	::SwapBuffers( hDC_ );
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::setAffichableTimer(bool afficherTexte) 
///
/// Cette fonction donne la permission au variable affichertexte 
/// d afficher oui ou non les textes dans le jeu.
///	
/// @param bool afficherTexte : variable qui active l affichage si vraie et non si c fausse
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::setAffichableTimer(bool afficherTexte) 
{
	afficherTexte_ = afficherTexte;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficherLesTetxes(bool activer)const
///
/// Cette fonction  affiche les textes dans le jeu
///
/// @param bool afficherTexte : variable qui active l affichage si vraie et non si c fausse
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficherLesTetxes(bool afficherTexte)const
{
	if(!afficherTexte)
		return;
	VisiteurAfficherTexte v = VisiteurAfficherTexte();
	arbre_->accepter(v);
	
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficherBase() const
///
/// Cette fonction affiche la base du contenu de la scène, c'est-à-dire
/// qu'elle met en place l'éclairage et affiche les objets.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficherBase() const
{
	

	glEnable(GL_LIGHTING);
	//glDisable(GL_LIGHT0);
	// Positionner la lumi?re.
	
	//Lumiere ambiante
	if(lumiereAmbiante)
	{
		//glDisable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		
		GLfloat position[4] = { 0, 0, 1, 0};
		GLfloat lumAmbiante1[4] = {0.2, 0.2, 0, 1.0}; 
		glLightfv(GL_LIGHT1, GL_POSITION, position);
		glLightfv( GL_LIGHT1, GL_AMBIENT, lumAmbiante1);
	}
	else
	{
		glDisable(GL_LIGHT1);
		//glEnable(GL_LIGHT0);
	}
	
		//Lumiere directionnelle
	if(lumiereDirectionnelle)
	{
		//glDisable(GL_LIGHT0);
		glEnable(GL_LIGHT2);
		GLfloat shini[] = { 125.0 };
		glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS,shini );

		//lumiere infinie dc 4 eme par position =0
		//GLfloat lumAmbiante2[4] = { 0, 0, 1, 0}; 
		//glLightfv( GL_LIGHT2, GL_AMBIENT, lumAmbiante2);
		GLfloat lumDirectionnellePosition2[4] = {10, 10, -1.0, 0.0};	
		GLfloat lumDirectionnelleDifuse2[4] = {1, 1, 1, 1.0};
		GLfloat lumDirectionnelleSpeculaire2[4] = {1.0, 1.0, 1.0, 1.0};	

		glLightfv( GL_LIGHT2, GL_POSITION, lumDirectionnellePosition2);	
		glLightfv( GL_LIGHT2, GL_DIFFUSE, lumDirectionnelleDifuse2 );
		glLightfv( GL_LIGHT2, GL_SPECULAR, lumDirectionnelleSpeculaire2 );
	}
	else
	{
		glDisable(GL_LIGHT2);
		//glEnable(GL_LIGHT0);
	}

	//Spot1
	if(lumiereSpot)
	{
		//glDisable(GL_LIGHT0);
		glEnable(GL_LIGHT3);
		GLfloat SpotDiffuse1[] = {1.0, 1, 1, 1.0f};
		GLfloat SpotSpeculaire1[] = {1.0f, 1.0f, 1.0f, 1.0f};
		GLfloat SpotAmbiant1[] = {0.2, 0.2, 0.2, 1.0f};

		GLfloat shini[] = { 125.0 };
		glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS,shini );
  
		glLightfv( GL_LIGHT3, GL_AMBIENT,SpotAmbiant1 );
		glLightfv( GL_LIGHT3, GL_DIFFUSE, SpotDiffuse1);
		glLightfv( GL_LIGHT3, GL_SPECULAR, SpotSpeculaire1 );
		glLightf ( GL_LIGHT3, GL_SPOT_EXPONENT, 2.0 );
		glLightf ( GL_LIGHT3, GL_SPOT_CUTOFF, 30) ;



		//Spot2

		//glEnable(GL_LIGHT4);
		GLfloat SpotDiffuse2[] = {1.0, 1, 1, 1.0f};
		GLfloat SpotSpeculaire2[] = {1.0f, 1.0f, 1.0f, 1.0f};
		GLfloat SpotAmbiant2[] = {0.2, 0.2, 0.2, 1.0f};

		
		glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS,shini );
  
		glLightfv( GL_LIGHT4, GL_AMBIENT,SpotAmbiant2 );
		glLightfv( GL_LIGHT4, GL_DIFFUSE, SpotDiffuse2);
		glLightfv( GL_LIGHT4, GL_SPECULAR, SpotSpeculaire2 );
		glLightf ( GL_LIGHT4, GL_SPOT_EXPONENT, 2.0 );
		glLightf ( GL_LIGHT4, GL_SPOT_CUTOFF, 30) ;
	}
	else
	{
		glDisable(GL_LIGHT3);
		glDisable(GL_LIGHT4);
		//glEnable(GL_LIGHT0);
	}

	//GLfloat mat_shin[] = { 50.0 };
	//glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS,mat_shin );

	// Positionner la lumière.
	//  GLfloat position[4] = { 0, 0, 1, 0 };
	// glLightfv(GL_LIGHT0, GL_POSITION, position);
  
	// Afficher la scène.
	arbre_->afficher();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::rafraichirFenetre() const
///
/// Cette fonction rafraîchit le contenu de la fenêtre, c'est-à-dire
/// qu'elle indique à Windows que la fenêtre doit être repeinte.  Un
/// événement sera donc généré puis traité plus tard, ce qui évite de
/// faire plusieurs affichages sans raison.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::rafraichirFenetre() const
{
   // Indique à Windows que la fenêtre doit être rafraîchie.
   //::InvalidateRect(hWnd_, 0, FALSE);

   // Finalement, on choisit de simplement appeler afficher() pour éviter
   // que le fond ne soit redessiné par Windows ou Java.

   // Or, comme il y a en permanence une boucle qui réaffiche, on ne fait
   // rien.

   //afficher();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::reinitialiser()
///
/// Cette fonction réinitialise la scène à un état "vide".
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::reinitialiser()
{
	// Réinitialisation de la scène.
	arbre_->initialiser();

	fichierSauvegarde = "";
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::animer(float temps)
///
/// Cette fonction effectue les différents calculs d'animations
/// nécessaires pour le mode jeu, tel que les différents calculs de
/// physique du jeu.
///
/// @param[in] temps : Intervalle de temps sur lequel effectuer le calcul.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::animer(float temps)
{
	// Mise à jour des objets.
	arbre_->animer(temps);

	// Mise à jour de la vue.
	vue_->animer( temps );

	glPushMatrix();

		//recuperation position spot1
		Vecteur3 positionVaisseau1 = GestionnaireJeu::obtenirInstance()->getPlayer(1)->getVaisseau()->obtenirPositionRelative();
		GLfloat  position1[] = {
			positionVaisseau1[0],
			positionVaisseau1[1],
			positionVaisseau1[2],
			1
		};
		//recuperation position spot2
		if(GestionnaireJeu::obtenirInstance()->getPlayer(2)!= NULL)
		{
		Vecteur3 positionVaisseau2 = GestionnaireJeu::obtenirInstance()->getPlayer(2)->getVaisseau()->obtenirPositionRelative();
		GLfloat  position2[] = {
			 positionVaisseau2[0],
			positionVaisseau2[1],
			positionVaisseau2[2],
			1
		};
		double angleVaisseau2 = utilitaire::DEG_TO_RAD(GestionnaireJeu::obtenirInstance()->getPlayer(2)->getVaisseau()->getAngleRotation());
		GLfloat SpotDirection2[] = {
			utilitaire::RAD_TO_DEG(cos(angleVaisseau2)),
			utilitaire::RAD_TO_DEG(sin(angleVaisseau2)),
			0.0
		};
	
		glLightfv( GL_LIGHT4, GL_POSITION,  position2);
		glLightfv( GL_LIGHT4, GL_SPOT_DIRECTION, SpotDirection2);
		glEnable(GL_LIGHT4);
		}
		double angleVaisseau1 = utilitaire::DEG_TO_RAD(GestionnaireJeu::obtenirInstance()->getPlayer(1)->getVaisseau()->getAngleRotation());
		
		
		GLfloat SpotDirection1[] = {
			utilitaire::RAD_TO_DEG(cos(angleVaisseau1)),
			utilitaire::RAD_TO_DEG(sin(angleVaisseau1)),
			0.0
		};
		
	    glLightfv( GL_LIGHT3, GL_POSITION,  position1);
		glLightfv( GL_LIGHT3, GL_SPOT_DIRECTION, SpotDirection1);
		glEnable(GL_LIGHT3);
		
	glPopMatrix();
}

void FacadeModele::ChangerEtat(int etatModele)
{
	if (obtenirEtat()->getEtatId() == ETATEDITEUR)
	{
		// Si dans le mode éditeur, il faut retourner à l'état action par défaut
		static_cast<EtatModeleEditeur*>(obtenirEtat())->buttonPressed("Par Défaut");

		// Désélectionner tout
		this->arbre_->deselectionnerTout();
	}
	else if (obtenirEtat()->getEtatId() == ETATJEU || obtenirEtat()->getEtatId() == ETATMODETEST)
	{
		// Il faut désinitialiser le jeu si on était en mode test ou mode jeu
		GestionnaireJeu::obtenirInstance()->DesinitialiserJeu();
	}

	std::map<EtatId, std::shared_ptr<EtatModeleAbstrait> >::const_iterator it;
	EtatId modelId = (EtatId)etatModele;
	it = m_mapInstance.find(modelId);
	if(it != m_mapInstance.end()) {
		this->etat_ = it->second;
	}
}

void FacadeModele::selectionObjet(Vecteur3 minXY, Vecteur3 maxXY, bool ctrlPressed)
{
	VisiteurSelection visiteur(minXY, maxXY, ctrlPressed);
	arbre_->accepter(visiteur);
	
	/// Verifier si seulement un noeud est selectionne
	noeudSelectionUnique = getElementUniqueSelectione();
}

NoeudAbstrait* FacadeModele::creerNoeud(double x, double y, string nomNoeud)
{
	// Créer le noeud et assigner sa position
	NoeudAbstrait* noeud = arbre_->creerNoeud(nomNoeud);
	noeud->assignerPositionRelative(Vecteur3(x, y, 0));
	
	// Obtenir la boîte englobante
	Vecteur3 minXY, maxXY;
	noeud->obtenirBoiteEnglobante(minXY, maxXY);

	// Vérifier si le nouveau noeud est dans la zone de jeu
	if (this->arbre_->estDansZoneJeu(minXY, maxXY))
	{
		// Si oui, ajouter le noeud à l'arbre
		arbre_->ajouter(noeud);
	}
	else
	{
		// Supprimer le noeud
		delete noeud;
		noeud = NULL;
	}

	return noeud;
}

NoeudAbstrait* FacadeModele::dupliquerNoeud(NoeudAbstrait* noeud, Vecteur3 nouvellePosition)
{
	// Dupliquer le noeud sans se soucier si la nouvelle position est légale. Ça doit être vérifié avant.
	Vecteur3 pointDebut, pointFin;
	NoeudAbstrait* nouveauNoeud;
	if (noeud->obtenirType() == ArbreRenduINF2990::NOM_BARRIEREPROTECTRICE)
	{
		static_cast<NoeudBarriereProtectrice*>(noeud)->obtenirExtremites(pointDebut, pointFin);
		nouveauNoeud = creerNoeud(pointDebut[0] + nouvellePosition[0], pointDebut[1] + nouvellePosition[1], noeud->obtenirType());
	}
	else
	{
		nouveauNoeud = creerNoeud(nouvellePosition[0], nouvellePosition[1], noeud->obtenirType());
	}

	nouveauNoeud->setAngleRotation(noeud->getAngleRotation());
	nouveauNoeud->setEchelle(noeud->getEchelle());
	
	return nouveauNoeud;
}


void FacadeModele::afficheZoneJeu() const 
{
	Vecteur3 position(0);
	NoeudAbstrait* noeud = arbre_->creerNoeud(ArbreRenduINF2990::NOM_ZONEJEU);
	noeud->assignerPositionRelative(Vecteur3(position));
	arbre_->ajouter(noeud);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::deplacerObjet(double dx, double dy)
///
/// Cette fonction permet de deplacer les objets situés dans la zone de jeu
///
/// @param[in] dx : le deplacement suivant l'axe X
///	@param[in] dy : le deplacement suivant l'axe Y
///
/// @return aucune
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::deplacerObjet(Vecteur3 deplacement)
{
	// Il faut au moins un noeud sélectionné
	if(arbre_->selectionExiste())
	{
		// Initialise le déplacement
		double dx = deplacement[0];
		double dy = deplacement[1];

		// On récupère les bornes de sélection
		Vecteur3 bornesMinXY, bornesMaxXY;
		arbre_->trouverBornesSelection(bornesMinXY, bornesMaxXY);

		// On récupère les dimensions de la zone de jeu
		Vecteur3 zoneJeuMinXY, zoneJeuMaxXY;
		arbre_->obtenirZoneJeu()->obtenirBoiteEnglobante(zoneJeuMinXY, zoneJeuMaxXY);

		// On vérifie le déplacement en X
		bornesMinXY[0] += dx;
		bornesMaxXY[0] += dx;
		
		// Si le déplacement cause un dépassement en X
		if (!arbre_->estDansZoneJeu(bornesMinXY, bornesMaxXY))
		{
			// On détermine si le dépassement est du côté min ou du côté max de la zone de jeu
			if (bornesMinXY[0] < zoneJeuMinXY[0] && !ALMOST_EQUALS(bornesMinXY[0], zoneJeuMinXY[0]))
			{
				// Dépassement du côté min
				// On diminue le déplacement par la valeur du dépassement
				deplacement[0] = dx + (zoneJeuMinXY[0] - bornesMinXY[0]);
			}
			else if(zoneJeuMinXY[0] < bornesMinXY[0] && !ALMOST_EQUALS(zoneJeuMinXY[0], bornesMinXY[0]))
			{
				// Dépassement du côté max
				// On diminue le déplacement par la valeur du dépassement
				deplacement[0] = dx - (bornesMaxXY[0] - zoneJeuMaxXY[0]);
			}
		}
		
		bornesMinXY[0] -= dx;
		bornesMaxXY[0] -= dx;

		// On vérifie le déplacement en Y
		bornesMinXY[1] += dy;
		bornesMaxXY[1] += dy;
		
		// Si le déplacement cause un dépassement en Y
		if (!arbre_->estDansZoneJeu(bornesMinXY, bornesMaxXY))
		{
			// On détermine si le dépassement est du côté min ou du côté max de la zone de jeu
			if (bornesMinXY[1] < zoneJeuMinXY[1] && !ALMOST_EQUALS(bornesMinXY[1], zoneJeuMinXY[1]))
			{
				// Dépassement du côté min
				// On diminue le déplacement par la valeur du dépassement
				deplacement[1] = dy + (zoneJeuMinXY[1] - bornesMinXY[1]);
			}
			else if (zoneJeuMinXY[1] < bornesMinXY[1] && !ALMOST_EQUALS(zoneJeuMinXY[1], bornesMinXY[1]))
			{
				// Dépassement du côté max
				// On diminue le déplacement par la valeur du dépassement
				deplacement[1] = dy - (bornesMaxXY[1] - zoneJeuMaxXY[1]);
			}
		}

		// On applique le déplacement calculé
		VisiteurDeplacement visiteur;
		visiteur.setDeplacement(deplacement);

		arbre_->accepter(visiteur);
	}
	
}



//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::misAEchelle(double echelle)
///
/// Cette fonction permet de mis a echelle sur les objets situés dans la zone de jeu
///
/// 
///
/// @param[in] echelle : Le facteur d'agrandissement à appliquer aux objets
///	
/// @return aucune
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::miseAEchelle(float lastScale, float scale)
{
	if(arbre_->selectionExiste())
	{
		// Appliquer la mise à l'échelle
		VisiteurMiseAEchelle visiteur(lastScale, scale);
		arbre_->accepter(visiteur);

		// Obtenir les bornes des noeuds sélectionnés
		Vecteur3 bornesMinXY, bornesMaxXY;
		arbre_->trouverBornesSelection(bornesMinXY, bornesMaxXY);
		
		// Vérifier si légal
		// On peut améliorer en calculant la mise à échelle maximale possible
		if (!arbre_->estDansZoneJeu(bornesMinXY, bornesMaxXY))
		{
			// Annuler la mise à l'échelle
			visiteur.setLastScale(scale);
			visiteur.setScale(lastScale);
			arbre_->accepter(visiteur);
		}
	}
}
	

	
//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::faireRotation(double angle)
///
/// Cette fonction permet de faire une rotation sur les objets situés dans la zone de jeu
///
/// 
///
/// @param[in] angle : la valeur appliquer sur l'objet pour les tourner
///	
/// @return aucune
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::faireRotation(double angle, Vecteur3 centreRotation)
{
	// Il faut au moins un noeud sélectionné
	if(arbre_->selectionExiste())
	{
		//Appliquer rotation
		VisiteurRotation visiteur(angle, centreRotation);
		arbre_->accepter(visiteur);

		// Vérifier si légal
		Vecteur3 minXY, maxXY;
		arbre_->trouverBornesSelection(minXY, maxXY);

		// On peut améliorer en calculant la rotation maximal possible
		if (!arbre_->estDansZoneJeu(minXY, maxXY))
		{
			// Annuler rotation
			visiteur.setAngle(-angle);
			visiteur.setCentreRotation(centreRotation);

			arbre_->accepter(visiteur);
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait * getElementUniqueSelectione()
///
/// Cette fonction recherche dans l arbre qui le neoud uniquement séléctionné
/// et le renvoie, si plusieurs sont séléctionnés ou aucun elle renvoie null
/// 
///
/// @param[in] : aucun.
///
/// @return le noeud unique sélectionné
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait * FacadeModele::getElementUniqueSelectione()
{
	int nbrElementSelectione = 0 ;
	
	NoeudAbstrait* noeud = NULL;

	for(unsigned int i = 0 ; i < arbre_->obtenirNombreEnfants() && nbrElementSelectione <=1 ; i++)
	{	
		if(arbre_->chercher(i)->estSelectionne())
		{
				nbrElementSelectione++;
				noeud =  arbre_->chercher(i);
				
		}
	}

	if(nbrElementSelectione == 1)
	{
		return noeud;
	}
	else
	{
		return NULL;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void dupliquerNoeuds(Vecteur3 position)
///
/// Cette fonction duplique les noeud sélectionné à la position voulu
/// en gardant la position relative aux autres noeud dupliqués
/// 
/// @param[in] position: Vecteur de la nouvelle position
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::dupliquerNoeuds(Vecteur3 position)
{
	// Il faut au moins un noeud sélectionné
	if(arbre_->selectionExiste())
	{
		// Obtenir les bornes de sélection
		Vecteur3 bornesMinXY, bornesMaxXY;
		arbre_->trouverBornesSelection(bornesMinXY, bornesMaxXY);

		// Obtenir la position du centre des noeuds sélectionnés
		Vecteur3 positionNoeudsSelectionnes;
		positionNoeudsSelectionnes[0] = (bornesMaxXY[0] + bornesMinXY[0])/2;
		positionNoeudsSelectionnes[1] = (bornesMaxXY[1] + bornesMinXY[1])/2;

		// Calculer le déplacement
		Vecteur3 deplacement = position - positionNoeudsSelectionnes;

		// Ajuster les bornes de sélection aux nouveaux noeuds que nous voulons créer
		bornesMinXY += deplacement;
		bornesMaxXY += deplacement;

		// Vérifier si dans zone de jeu
		if (arbre_->estDansZoneJeu(bornesMinXY, bornesMaxXY))
		{
			// Appliquer visiteur duplication
			VisiteurDuplication visiteur(deplacement);
			arbre_->accepter(visiteur);
		}
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void supprimerNoeudSelectione()
///
/// Cette fonction supprime les noeuds selectiones 
/// 
///
/// @param[in] aucun
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::supprimerNoeudSelectione()
{
	VisiteurSuppression visiteur;

	NoeudAbstrait* noeud;

	for(unsigned int i = 0 ; i < arbre_->obtenirNombreEnfants() ; i++)
	{
		noeud = arbre_->chercher(i);
		noeud->accepter(visiteur);
	}
	
	/// Verifier si seulement un noeud est selectionne
	noeudSelectionUnique = getElementUniqueSelectione();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn vector <NoeudAbstrait> FacadeModele::obtenirVectNoeudSelectione()
///
/// Cette fonction parcours l'arbre est renvoie un vecteur des noeuds sélectionés
///
/// @return vector <NoeudAbstrait>
/// 
///   obtenirVectNoeudSelectione().size() renvoie le nombre des noeuds sélectionnés
///   obtenirVectNoeudSelectione()[i] est l'élément qui se trouve dans la position i
///
///
////////////////////////////////////////////////////////////////////////
vector<NoeudAbstrait> FacadeModele::obtenirVectNoeudSelectione()
{
	/// Vecteur qui contient les noeuds séléctionnés
	vector<NoeudAbstrait> VecnoeudSelectiones ;

	for(unsigned int i = 0 ; i < arbre_->obtenirNombreEnfants() ; i++)
	{
		if(arbre_->chercher(i)->estSelectionne())
			VecnoeudSelectiones.push_back(*arbre_->chercher(i));
		
	}

   return VecnoeudSelectiones;
}

//Position 1 du noeud position de depart
NoeudPositionDepart* FacadeModele::positionUnPositionDepart()
{
	return arbre_->getNoeudPositionDeDepart1();
}

//Position 2 du noeud position de depart
NoeudPositionDepart* FacadeModele::positionDeuxPositionDepart()
{
	return arbre_->getNoeudPositionDeDepart2();
}

void FacadeModele::activerVuePerspective()
{
	if (vueOrthographique_)
	{
		vueOrthographique_ = false;
		vue_ = m_mapInstanceVue[PERSPECTIVE];
	}
}

void FacadeModele::activerVueOrthogonale()
{
	if (!vueOrthographique_)
	{
		vueOrthographique_ = true;
		vue_ = m_mapInstanceVue[ORTHO];
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
