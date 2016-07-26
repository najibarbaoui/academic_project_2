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
/// @brief Classe qui constitue une interface (une fa�ade) sur l'ensemble
///        du mod�le et des classes qui le composent.
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
	/// Lib�re l'instance unique de la classe.
	static void libererInstance();

	/// Cr�e un contexte OpenGL et initialise celui-ci.
	void initialiserOpenGL(HWND hWnd);
	/// Charge la configuration � partir d'un fichier XML.
	void chargerConfiguration() const;
	/// Enregistre la configuration courante dans un fichier XML.
	void enregistrerConfiguration() const;
	/// Enregistre l'arbre courant dans un fichier XML
	void enregistrerXml(std::string nomfichier);
	/// Charger le XML dans l'arbre courant
	void chargerXml(std::string nomfichier);
	// Retourne si le fichier de sauvegarde est d�fini
	bool fichierSauvegardeEstDefini();
	// Assigne le nom du fichier de sauvegarde
	void assignerFichierSauvegarde(string nomFichier);
	// Obtenir le nom du fichier de sauvegarde
	string obtenirNomFichierSauvegarde();
	/// Lib�re le contexte OpenGL.
	void libererOpenGL();
	/// Affiche le contenu du mod�le.
	void afficher() const;
	/// Affiche la base du contenu du mod�le.
	void afficherBase() const;
	/// Indique que la fen�tre doit �tre r�affich�e sans le faire directement.
	void rafraichirFenetre() const;

	/// Retourne la vue courante.
	inline vue::Vue* obtenirVue();
	/// Retourne l'arbre de rendu.
	inline const ArbreRenduINF2990* obtenirArbreRenduINF2990() const;
	/// Retourne l'arbre de rendu.
	inline ArbreRenduINF2990* obtenirArbreRenduINF2990();
	/// Retourne l'�tat du mod�le.
	inline EtatModeleAbstrait* obtenirEtat() const;

	/// R�initialise la sc�ne.
	void reinitialiser();

	/// Anime la sc�ne.
	void animer(float temps);
   
	// Changer l'�tat du mod�le (ex. passer du menu � l'�diteur)
	void ChangerEtat(int etatModele);

	// s�l�ctionner un objet
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
   
	/// Renvoie le seul �l�ment s�l�ction�
	NoeudAbstrait* getElementUniqueSelectione(); 

	// �l�ment s�lectionn� unique
	NoeudAbstrait* noeudSelectionUnique;
	
	// Dupliquer les noeuds s�lectionn�s
	void dupliquerNoeuds(Vecteur3 position);
	
	//Supprimer noeud selectionne
	void supprimerNoeudSelectione();
   //Definir boite englobante
   void boiteEnglobante(Vecteur3& minXY,Vecteur3& maxXY,int& k);
   // Appliquer rotation
   void faireRotation(double angle, Vecteur3 centreRotation);
   
   // Renvoie un vecteur des noeuds s�l�ction�s
   vector<NoeudAbstrait> obtenirVectNoeudSelectione();
  
   // verifier si les noeuds selectionnes sont a l interieur de la zone
   bool noeudSelectionEstHorsZonJeu(double dx , double dy);
   /////////////////
   double distanceMin(Vecteur3 centre) const;

   //Position 1 du noeud position de depart
   NoeudPositionDepart* positionUnPositionDepart();
    //Position 2 du noeud position de depart
   NoeudPositionDepart* positionDeuxPositionDepart();
   //affiche le noeud Position de depart suivant l'�tat ou le cache
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
	/// Constructeur par d�faut.
	FacadeModele();
	/// Destructeur.
	~FacadeModele();
	/// Constructeur copie.  D�clar� mais non d�fini pour �viter qu'il soit
	/// g�n�r� par le compilateur.
	FacadeModele(const FacadeModele&);
	/// Op�rateur d'assignation.  D�clar� mais non d�fini pour �viter qu'il
	/// soit g�n�r� par le compilateur.
	FacadeModele& operator =(const FacadeModele&);
	/// Sortie de d�bogage
	void SortieConsole(std::string strLum, bool bEtat) const;
	/// Nom du fichier XML dans lequel doit se trouver la configuration.
	static const std::string FICHIER_CONFIGURATION;
	/// Nom du fichier XML dans lequel doit �tre enregistr� la zone
	std::string fichierSauvegarde;

	/// Pointeur vers l'instance unique de la classe.
	static FacadeModele* instance_;
	//
	unsigned int chiffre_;
	/// Poign�e ("handle") vers la fen�tre o� l'affichage se fait.
	HWND  hWnd_;
	/// Poign�e ("handle") vers le contexte OpenGL.
	HGLRC hGLRC_;
	/// Poign�e ("handle") vers le "device context".
	HDC   hDC_;

	/// �tat du mod�le
	std::shared_ptr<EtatModeleAbstrait> etat_;
	std::map<EtatId, std::shared_ptr<EtatModeleAbstrait> > m_mapInstance;

	std::list<double> lesMaxEChelles_;
	/// Vue courante de la sc�ne.
	vue::Vue* vue_;
	/// Tient compte de toutes les projections
	std::map<TypeVue, vue::Vue*> m_mapInstanceVue;
	/// Arbre de rendu contenant les diff�rents objets de la sc�ne.
	ArbreRenduINF2990* arbre_;
	// Dernier facteur d'agrandissement appliqu�
	float lastScale;
	// Bool�en qui indique si cest la vue orthographioque ou perspective est activ�e
	bool vueOrthographique_;

};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline vue::Vue* FacadeModele::obtenirVue()
///
/// Cette fonction retourne la vue qui est pr�sentement utilis�e pour
/// voir la sc�ne.
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
/// Cette fonction retourne l'arbre de rendu de la sc�ne (version constante
/// de la fonction).
///
/// @return L'arbre de rendu de la sc�ne.
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
/// Cette fonction retourne l'arbre de rendu de la sc�ne (version non constante
/// de la fonction).
///
/// @return L'arbre de rendu de la sc�ne.
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
/// Cette fonction retourne l'�tat du mod�le
///
/// @return L'�tat du mod�le.
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
