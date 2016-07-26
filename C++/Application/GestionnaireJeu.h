//////////////////////////////////////////////////////////////////////////////
/// @file GestionnaireJeu.h
/// @author Najib Arbaoui
/// @date 2014-02-27
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef __APPLICATION_GESTIONNAIREJEU_H__
#define __APPLICATION_GESTIONNAIREJEU_H__

#include "Singleton.h"
#include "Jeu\Player.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
#include "Jeu\Partie.h"
#include "ConfigJeu.h"
#include "EtatModele\EtatModelePartieRapide.h"
#include "GestionnaireAudio.h"

//# define FREQUENCEAPPARAITIONGRANDASTEROIDE 20
class NoeudVaisseau;

class GestionnaireJeu : public Singleton<GestionnaireJeu>
{
	SINGLETON_DECLARATION_CLASSE_SANS_CONSTRUCTEUR(GestionnaireJeu);

private:
	GestionnaireJeu();
	~GestionnaireJeu();

	bool paused_;

	NoeudVaisseau* vaisseau1_;
	Player* player1_;
	Player* player2_;
	
	// Param�tres Asteroide
	unsigned int nbrAsteroide;
	float tempsCumuleAsteroide;
	float tempsApparaitionAsteroide ;
	unsigned int nbrAsteroideSelonLoiNominal ;
	float vitesseMinAsteroide, vitesseMaxAsteroide ;
	vector <NoeudAbstrait*> listeAsteroide ;
	vector <NoeudAbstrait*> listeAnimation ;
	//Partie *partie;

	NoeudAbstrait * zoneDePassage;
	NoeudAbstrait * cadreDepart ;
	// Verifier si on est en mode test
	bool isModeTest_;
	bool partieSolo_;
	bool partieCoopHumain_;
	
	
public:
	// Initialiser la partie
	void InitialiserJeu(bool isModeTest);
	// D�sinitialiser la partie
	void DesinitialiserJeu();
	// Mettre le jeu en pause
	void TogglePauseGame();
	bool obtenirEtatPause();

	Player* getPlayer(int i);

	void update(float temps);
	
	void keyPressed(int keyCode);
	void keyReleased(int keyCode);
	///////////////////////////
	bool getIsGagne();
	bool  isTermine();
	
	// Methodes des asteroides  
	 void genererAsteroide(float temps);
	 void verifieIsAsteroideEnable();
	 void effacerAsteroide();
	 void effacerTousAsteroide();
	 float generAleatoireSelonLoiNormal();
	 double generAleatoire(double min , double max);
	 void fixerVitesseMaxMinAsteroide(float&vitesseMin ,float&vitesseMax , int difficulte );
	 void obtenirCadreDepartAsteroide(Vecteur3 &minXY , Vecteur3 &maxXY );
	 void obtenirZoneDePassageAsteroide(Vecteur3 &minXY , Vecteur3 &maxXY );
	 void assignerPositionVitesseAsteroide(NoeudAbstrait * asteroide);
	 Vecteur3 genererDirectionNormalise( Vecteur3 positionAsteroide);
	 //Partie * getPartie();

	 void assignerPartieSolo(bool value);
	 void assignerPartieCoopHumain(bool value);
	 
	 void mettreAjourPointDeVieStationSpatiale();
	 // fonction qui permet de simuler l'animation de l'explosion, on ajoute le noeudAnimation � l'arbre. Apr�s un certain tempsAnimation on retire ce noeud.
	 void simulerExplosion(NoeudAbstrait * noeud, float tempsAnimation , string typeNoeud);
	
	 // Fonction qui met � jour l'animation
	 void updateAnimation(float temps);
	 // Fonctions qui effacer les animations jouees de l'arbre;
	  void effacerAnimation();
	 void effacerTousAnimation();
};

#endif // __APPLICATION_GESTIONNAIREJEU_H__

//////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////