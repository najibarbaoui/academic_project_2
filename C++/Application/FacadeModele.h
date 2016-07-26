//////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.h
/// @author DGI
/// @date 2005-06-15
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __APPLICATION_FACADEMODELE_H__
#define __APPLICATION_FACADEMODELE_H__

#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <vector>
#include <list>
#include "Vecteur.h"
#include "..\Arbre\Visiteurs\VisiteurDeplacement.h"
#include "..\Arbre\Visiteurs\VisiteurXml.h"
#include "ConfigJeu.h"
#include "BoiteEnvironnement.h"

#include "AfficherTexte.h"

enum EtatId;
class NoeudAbstrait;
class ArbreRenduINF2990;
class EtatModeleAbstrait;
class NoeudStationSpatiale;

namespace vue {
   class Vue;
}

enum TypeVue {
	ORTHO = 0,
	PERSPECTIVE = 1
};

///////////////////////////////////////////////////////////////////////////
/// @class FacadeModele
/// @brief Classe qui constitue une interface (une façade) sur l'ensemble
///        du modèle et des classes qui le composent.
///
/// @author Martin Bisson
/// @date 2007-02-20
///////////////////////////////////////////////////////////////////////////
class FacadeModele
{
public:
	
	void afficherLesTetxes(bool activer)const;
	void setAffichableTimer(bool afficherTimer);
	
	HWND obtenirContexteHwnd();
	HDC obtenirContexte();
	HGLRC obtenirContexteHglrc();
	/// Obtient l'instance unique de la classe.
	static FacadeModele* obtenirInstance();
	/// Libère l'instance unique de la classe.
	static void libererInstance();

	/// Crée un contexte OpenGL et initialise celui-ci.
	void initialiserOpenGL(HWND hWnd);
	/// Charge la configuration à partir d'un fichier XML.
	void chargerConfiguration() const;
	/// Enregistre la configuration courante dans un fichier XML.
	void enregistrerConfiguration() const;
	/// Enregistre l'arbre courant dans un fichier XML
	void enregistrerXml(std::string nomfichier);
	/// Charger le XML dans l'arbre courant
	void chargerXml(std::string nomfichier);
	// Retourne si le fichier de sauvegarde est défini
	bool fichierSauvegardeEstDefini();
	// Assigne le nom du fichier de sauvegarde
	void assignerFichierSauvegarde(string nomFichier);
	// Obtenir le nom du fichier de sauvegarde
	string obtenirNomFichierSauvegarde();
	/// Libère le contexte OpenGL.
	void libererOpenGL();
	/// Affiche le contenu du modèle.
	void afficher() const;
	/// Affiche la base du contenu du modèle.
	void afficherBase() const;
	/// Indique que la fenêtre doit être réaffichée sans le faire directement.
	void rafraichirFenetre() const;

	/// Retourne la vue courante.
	inline vue::Vue* obtenirVue();
	/// Retourne l'arbre de rendu.
	inline const ArbreRenduINF2990* obtenirArbreRenduINF2990() const;
	/// Retourne l'arbre de rendu.
	inline ArbreRenduINF2990* obtenirArbreRenduINF2990();
	/// Retourne l'état du modèle.
	inline EtatModeleAbstrait* obtenirEtat() const;

	/// Réinitialise la scène.
	void reinitialiser();

	/// Anime la scène.
	void animer(float temps);
   
	// Changer l'état du modèle (ex. passer du menu à l'éditeur)
	void ChangerEtat(int etatModele);

	// séléctionner un objet
	void selectionObjet(Vecteur3 minXY, Vecteur3 maxXY, bool ctrlPressed);

	// creer un Noeud
	NoeudAbstrait* creerNoeud(double x, double y, string nomNoeud);
	// Dupliquer un noeud
	NoeudAbstrait* dupliquerNoeud(NoeudAbstrait* noeud, Vecteur3 nouvellePosition);

	//// Deplacement de l'objet
	void deplacerObjet(Vecteur3 deplacement);
	// Afficher noeud zone de jeu
	void afficheZoneJeu()const;

	/// appliquer mis a echelle sur un objet
	void miseAEchelle(float lastScale, float scale);
   
	/// Renvoie le seul élément séléctioné
	NoeudAbstrait* getElementUniqueSelectione(); 

	// Élément sélectionné unique
	NoeudAbstrait* noeudSelectionUnique;
	
	// Dupliquer les noeuds sélectionnés
	void dupliquerNoeuds(Vecteur3 position);
	
	//Supprimer noeud selectionne
	void supprimerNoeudSelectione();
   //Definir boite englobante
   void boiteEnglobante(Vecteur3& minXY,Vecteur3& maxXY,int& k);
   // Appliquer rotation
   void faireRotation(double angle, Vecteur3 centreRotation);
   
   // Renvoie un vecteur des noeuds séléctionés
   vector<NoeudAbstrait> obtenirVectNoeudSelectione();
  
   // verifier si les noeuds selectionnes sont a l interieur de la zone
   bool noeudSelectionEstHorsZonJeu(double dx , double dy);
   /////////////////
   double distanceMin(Vecteur3 centre) const;

   //Position 1 du noeud position de depart
   NoeudPositionDepart* positionUnPositionDepart();
    //Position 2 du noeud position de depart
   NoeudPositionDepart* positionDeuxPositionDepart();
   //affiche le noeud Position de depart suivant l'état ou le cache
   void afficherNoeudPositionDeDepart(string affiche); 
   
  

   
   void activerVuePerspective();
   void activerVueOrthogonale();

   //
   void setLumiereAmbiante(bool Ambiante);
   void setLumiereDirectionnelle(bool directionnelle);
   void setLumiereSpot(bool Spot);

   bool getLumiereAmbiante();
   bool getLumiereDirectionnelle();
   bool getLumiereSpot();
   
private:
	//lumiere embiante
	bool lumiereAmbiante;
	bool lumiereDirectionnelle;
	bool lumiereSpot;
	// Pour valider l affichage des textes uniquement dans zone de jeu
	bool afficherTexte_;
	/// Constructeur par défaut.
	FacadeModele();
	/// Destructeur.
	~FacadeModele();
	/// Constructeur copie.  Déclaré mais non défini pour éviter qu'il soit
	/// généré par le compilateur.
	FacadeModele(const FacadeModele&);
	/// Opérateur d'assignation.  Déclaré mais non défini pour éviter qu'il
	/// soit généré par le compilateur.
	FacadeModele& operator =(const FacadeModele&);
	/// Sortie de débogage
	void SortieConsole(std::string strLum, bool bEtat) const;
	/// Nom du fichier XML dans lequel doit se trouver la configuration.
	static const std::string FICHIER_CONFIGURATION;
	/// Nom du fichier XML dans lequel doit être enregistré la zone
	std::string fichierSauvegarde;

	/// Pointeur vers l'instance unique de la classe.
	static FacadeModele* instance_;
	//
	unsigned int chiffre_;
	/// Poignée ("handle") vers la fenêtre où l'affichage se fait.
	HWND  hWnd_;
	/// Poignée ("handle") vers le contexte OpenGL.
	HGLRC hGLRC_;
	/// Poignée ("handle") vers le "device context".
	HDC   hDC_;

	/// État du modèle
	std::shared_ptr<EtatModeleAbstrait> etat_;
	std::map<EtatId, std::shared_ptr<EtatModeleAbstrait> > m_mapInstance;

	std::list<double> lesMaxEChelles_;
	/// Vue courante de la scène.
	vue::Vue* vue_;
	/// Tient compte de toutes les projections
	std::map<TypeVue, vue::Vue*> m_mapInstanceVue;
	/// Arbre de rendu contenant les différents objets de la scène.
	ArbreRenduINF2990* arbre_;
	// Dernier facteur d'agrandissement appliqué
	float lastScale;
	// Booléen qui indique si cest la vue orthographioque ou perspective est activée
	bool vueOrthographique_;

};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline vue::Vue* FacadeModele::obtenirVue()
///
/// Cette fonction retourne la vue qui est présentement utilisée pour
/// voir la scène.
///
/// @return La vue courante.
///
////////////////////////////////////////////////////////////////////////
inline vue::Vue* FacadeModele::obtenirVue()
{
   return vue_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990() const
///
/// Cette fonction retourne l'arbre de rendu de la scène (version constante
/// de la fonction).
///
/// @return L'arbre de rendu de la scène.
///
////////////////////////////////////////////////////////////////////////
inline const ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990() const
{
   return arbre_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990()
///
/// Cette fonction retourne l'arbre de rendu de la scène (version non constante
/// de la fonction).
///
/// @return L'arbre de rendu de la scène.
///
////////////////////////////////////////////////////////////////////////
inline ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990()
{
   return arbre_;
}



////////////////////////////////////////////////////////////////////////
///
/// @fn inline EtatModeleAbstrait* FacadeModele::obtenirEtat()
///
/// Cette fonction retourne l'état du modèle
///
/// @return L'état du modèle.
///
////////////////////////////////////////////////////////////////////////
inline EtatModeleAbstrait* FacadeModele::obtenirEtat() const
{
	return etat_.get();
}

#endif // __APPLICATION_FACADEMODELE_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
