////////////////////////////////////////////////////////////////////////////////////
/// @file GestionnaireJeu.cpp
/// @author Najib Arbaoui
/// @date 2014-02-27
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "GestionnaireJeu.h"
#include "FacadeModele.h"
#include "Visiteurs\VisiteurReinitialiserNoeuds.h"

#include "EtatModele\EtatModelePartieRapide.h"
#include "EtatModele\EtatModeleCampagne.h"

SINGLETON_DECLARATION_CPP(GestionnaireJeu);

GestionnaireJeu::GestionnaireJeu()
{
	this->player1_ = NULL;
	this->player2_ = NULL;
}

GestionnaireJeu::~GestionnaireJeu()
{
	
}

void GestionnaireJeu::InitialiserJeu(bool isModeTest)//, bool isSolo, bool isHumain)
{
	
	if (isModeTest)
	{
		partieSolo_ = true;
	}
	//recupere la permission d afficher des textes uniquement dans le jeu
	FacadeModele::obtenirInstance()->setAffichableTimer(!isModeTest);
	// Le jeu d�marre sans �tre en pause
	paused_ = false;

	// On met � jour les points de vie pour les stations
	mettreAjourPointDeVieStationSpatiale();

	//on met invisible les noeuds position de depart en mode jeu
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getNoeudPositionDeDepart1()->assignerAffiche(false);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getNoeudPositionDeDepart2()->assignerAffiche(false);
	
	// Cr�� les deux joueurs
	this->player1_ = new Player(1, true);

	if (!partieSolo_)
	{
		this->player2_ = new Player(2, partieCoopHumain_);
	}
	
	// initialiser les param�tres pour les asteroides
	nbrAsteroide = 0;
	
	// Le temps entre la creation de deux asteroides, les valeurs sont r�cup�r�es dans le menu Fichier -> Proprietes	
	
	tempsApparaitionAsteroide = static_cast<float>((FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getAsterpsec() ) <= 0 ? 1 : (60 / FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getAsterpsec() )) ;
	tempsCumuleAsteroide = tempsApparaitionAsteroide;
	
	// fixer les vitesses limites de l' Asteroide
	fixerVitesseMaxMinAsteroide(vitesseMinAsteroide ,vitesseMaxAsteroide , FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getDifficulte() );
	/*vitesseMinAsteroide = 149.0; 
	vitesseMaxAsteroide = 150.0 ;*/
	
	// Zone de passage
	 zoneDePassage = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->creerNoeud("zonePassage");
	 FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(zoneDePassage);
	 zoneDePassage->assignerAffiche(ConfigJeu::obtenirInstance()->isZonePassage()); // ????livrable 3 pas la peine des les afficher

	// Cadre de depart
	 cadreDepart = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->creerNoeud("cadreDepart");
	 FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(cadreDepart);
	 cadreDepart->assignerAffiche(ConfigJeu::obtenirInstance()->isCadreDepart());// ?????livrable 3 pas la peine des les afficher

	// Param�tres Partie et nombre des stations spatiales

	float tempsPartie = (static_cast<float>(ConfigJeu::obtenirInstance()->gettimer()) >= 30) ? static_cast<float>(ConfigJeu::obtenirInstance()->gettimer()) : 60  ;

	// Nombre de stations pour que la partie soit consid�r�e gagnante, les valeurs sont r�cup�r�es dans le menu Fichier -> Proprietes
	int NbrStationPourGagnerPartie = (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getNbstatsauv()) <= 0 ? 1 : FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getNbstatsauv();
	//partie = new Partie(tempsPartie,NbrStationPourGagnerPartie);
	Partie::obtenirInstance()->setPartie(tempsPartie,NbrStationPourGagnerPartie);

	  // Cache la zone de jeu en mode partie
	  static_cast<NoeudZoneJeu*>(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirZoneJeu())->assignerAfficherSiVaisseauLoin(false);
	// initialiser la variable isModeTest pour verifie est ce que nous sommes dans le modele test
	this->isModeTest_ = isModeTest ;

	// Jouer la musique d'arriere plan pour les modes partie rapide et compagnie
		if(!isModeTest_)
		{
			GestionnaireAudio::obtenirInstance()->jouerAudioArrierePlan();
		}
		
		
	
}

void GestionnaireJeu::DesinitialiserJeu()
{
	// on le remet a false l affichage des textes
	FacadeModele::obtenirInstance()->setAffichableTimer(false);
	//on r�affiche les noeuds position de d�part dans le mode editeur
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getNoeudPositionDeDepart1()->assignerAffiche(true);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getNoeudPositionDeDepart2()->assignerAffiche(true);

	// Reinitialiser l'�tat des noeuds qui ont �t� modifi�s pendant le jeu
	VisiteurReinitialiserNoeuds v;
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(v);

	// D�truire les deux joueurs, le destructeur s'occupe de lib�rer les vaisseaux et les projectiles associ�s
	delete player1_;
	player1_ = NULL;
	if (player2_ != NULL)
	{
		delete player2_;
		player2_ = NULL;
	}

	// effacer les asteroides de la liste
	effacerTousAsteroide();

	// effacer toutes les animations
	effacerTousAnimation();
	// effacer l'objet Partie
	//delete partie;
	Partie::libererInstance();

	// Cache la zone de jeu en mode partie
	static_cast<NoeudZoneJeu*>(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirZoneJeu())->assignerAfficherSiVaisseauLoin(true);
	// effacer zone de passage et cadre de dpart
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(zoneDePassage);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(cadreDepart);

		
	// arreter les sons joues
	GestionnaireAudio::obtenirInstance()->arreterAudio();


}

////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireJeu::TogglePauseGame()
///
/// Cette fonction met en pause ou active le jeu
///
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void GestionnaireJeu::TogglePauseGame()
{
	paused_ = !paused_;

}
////////////////////////////////////////////////////////////////////////
///
/// @fn bool GestionnaireJeu::obtenirEtatPause()
///
/// Cette fonction renvoie l'etat de la variable pause vrai si c pause sino faux
///
///
/// @return bool vrai si c est la pause sino faux.
///
////////////////////////////////////////////////////////////////////////
bool GestionnaireJeu::obtenirEtatPause()
{
	return paused_;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn Player* GestionnaireJeu::getPlayer(int i)
///
/// Cette fonction renvoie le joueur choisi indiqu� par l'argument i
///
///	@arg int i : numero du joueur
/// @return Player un pointeur qui indique le joueur.
///
////////////////////////////////////////////////////////////////////////
Player* GestionnaireJeu::getPlayer(int i)
{
	switch(i)
	{
	case 1:
		return player1_;
	case 2:
		return player2_;
	default:
		return NULL;
	}
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireJeu::update(float temps)
///
/// Cette fonction met � jour le jeu
///
///	@arg float temps : la variable temps
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void GestionnaireJeu::update(float temps)
{

	if (!paused_)
	{
		
		player1_->update(temps);
		if (player2_ != NULL)
		{
			player2_->update(temps);
		}

		genererAsteroide(temps);
		verifieIsAsteroideEnable();
		effacerAsteroide();
		

	
		
		// gestion de la partie
		Partie::obtenirInstance()->updateTempsPartie(temps);
		Partie::obtenirInstance()->supprimerStationSpatiale();
		
		if(Partie::obtenirInstance()->isTermine() && !isModeTest_)
		{
			paused_ = true;
		}

		// Mettre a jour les animations des explosions
		updateAnimation(temps);
	   // effacer les animations jouees
		effacerAnimation();

		
		
	}
	
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireJeu::keyPressed(int keyCode)
///
/// Cette fonction controle le jeu suivant la touche du clavier presser
///	27 pour mettre en pause
/// 8 pour initialiser
/// autre pour controler le vaisseau
///
///	@arg int keyCode : la valeur de la touche clavier
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void GestionnaireJeu::keyPressed(int keyCode)
{
	// Si la touche appuy� est "backspace"
	if (keyCode == 8)
	{
		// On red�marre le jeu
		DesinitialiserJeu();
		InitialiserJeu(isModeTest_);
	}
	// Pause 27
	else if (keyCode == 27)
	{
		TogglePauseGame();
	}
	else
	{
		// Chacun des joeurs recoivent le keycode, celui qui a une action associ�e l'utilisera
		player1_->keyPressed(keyCode);
		if (player2_ != NULL)
		{
			player2_->keyPressed(keyCode);
		}
	}
	if(keyCode == 74){
		FacadeModele::obtenirInstance()->setLumiereAmbiante(!FacadeModele::obtenirInstance()->getLumiereAmbiante());
	}
	if(keyCode == 75){
		FacadeModele::obtenirInstance()->setLumiereDirectionnelle(!FacadeModele::obtenirInstance()->getLumiereDirectionnelle());
	}
	if(keyCode == 76){
		FacadeModele::obtenirInstance()->setLumiereSpot(!FacadeModele::obtenirInstance()->getLumiereSpot());
	}
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireJeu::keyReleased(int keyCode)
///
/// Cette fonction controle le jeu suivant la touche du clavier relacher
/// pour controler le vaisseau
///
///	@arg int keyCode : la valeur de la touche clavier
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void GestionnaireJeu::keyReleased(int keyCode)
{

	// Chacun des joeurs recoivent le keycode, celui qui a une action associ�e l'utilisera
	player1_->keyReleased(keyCode);
		if (player2_ != NULL)
		{
			player2_->keyReleased(keyCode);
		}
	
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireJeu::getIsGagne()
///
/// Cette fonction definit si le jour a gagn� ou perdu
///
///
/// @return bool vrai s'il a gagn� sinon false.
///
////////////////////////////////////////////////////////////////////////
bool GestionnaireJeu::getIsGagne()
{
	return Partie::obtenirInstance()->getIsGagne();
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireJeu::isTermine()
///
/// Cette fonction definit la terminaison du jeu
///
///
/// @return bool vrai si le jeu est termin� sinon false.
///
////////////////////////////////////////////////////////////////////////
bool  GestionnaireJeu::isTermine()
{
	return Partie::obtenirInstance()->isTermine();
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireJeu::genererAsteroide(float temps)
///
/// Cette fonction permet de generer des asteroides au cadre de depart
///
/// @param[in] temps : Intervalle de temps sur lequel effectuer le calcul.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void GestionnaireJeu::genererAsteroide(float temps)
{
	tempsCumuleAsteroide += temps;

	if( tempsCumuleAsteroide >= tempsApparaitionAsteroide &&  nbrAsteroide <100 )
	{
		NoeudAbstrait* asteroide = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->creerNoeud("asteroide");
		 
		float taille = generAleatoireSelonLoiNormal(); // taille asteroide entre 1 et 12 taille vaisseau

		asteroide->setEchelle(taille); 
		
		assignerPositionVitesseAsteroide(asteroide);

		// Assigner la masse et les points de vie selon la taille
		int pointsDeVie;
		
		pointsDeVie = (taille <= 1.0f) ? 1 : (2 * static_cast<int>(taille) ) ;

		static_cast<NoeudAsteroide*> (asteroide)-> setPointsDeVie((int)pointsDeVie);
		static_cast<NoeudAsteroide*> (asteroide)->assignerMasse(taille*100);

		listeAsteroide.push_back(asteroide);
		
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(asteroide);
		
		if(ConfigJeu::obtenirInstance()->isApparitionAsteroid())
			static_cast<NoeudAsteroide*>(asteroide)->SortieConsole();
		nbrAsteroide ++;
			
		tempsCumuleAsteroide = 0;
	
	}
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireJeu:: verifieIsAsteroideEnable()
/// Cette fonction changer l etat enable d un asteroide
///
/// @param[in] : aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void GestionnaireJeu:: verifieIsAsteroideEnable()
{

		Vecteur3 CadreDepartAsteroideMaxXY , CadreDepartAsteroideMinXY ;
					
		obtenirCadreDepartAsteroide(CadreDepartAsteroideMinXY , CadreDepartAsteroideMaxXY );


	for(unsigned int i = 0 ; i < FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirNombreEnfants() ; i++ )
	{
		if(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(i)->obtenirType()=="asteroide")
		{
			Vecteur3 position = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(i)->obtenirPositionRelative();

			if( static_cast<NoeudAsteroide*> (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(i))->getPointsDeVie() <= 0 )
			{
				// simuler une explosion 
  				simulerExplosion(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(i), 1,"asteroide") ;
				static_cast<NoeudAsteroide*> (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(i))->setEnabled(false);
				nbrAsteroide = (nbrAsteroide > 0) ? (nbrAsteroide - 1) : 0 ;
			}
			else
			{
			
				
					if( position[0] > CadreDepartAsteroideMaxXY[0] || position[0] < CadreDepartAsteroideMinXY[0] || position[1] < CadreDepartAsteroideMinXY[1] ||  position[1] > CadreDepartAsteroideMaxXY[1])
					{
						static_cast<NoeudAsteroide*> (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(i))->setEnabled(false);

						nbrAsteroide = (nbrAsteroide > 0) ? (nbrAsteroide - 1) : 0 ;
					}
					
							
			
			}
			
		}
	
	}
	

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireJeu:: effacerAsteroide()
/// Cette fonction parcourit la liste des asteroides et efface ceux qui sont disable
///
/// @param[in] : aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void GestionnaireJeu::effacerAsteroide()
{
	for(int i = 0 ; i < listeAsteroide.size() ; i++)
	{
		if(!static_cast<NoeudAsteroide*> (listeAsteroide[i])->isEnabled())
		{
			
			FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(listeAsteroide[i]);
			listeAsteroide.erase( listeAsteroide.begin() + i );
		}
	
	}
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireJeu::effacerTousAsteroide()
/// Cette fonction efface tous les asteroides dans la liste
///
/// @param[in] : aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////


void GestionnaireJeu::effacerTousAsteroide()
{
	for(int i = 0 ; i < listeAsteroide.size() ; i++)
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(listeAsteroide[i]);
	}

	listeAsteroide.clear();
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireJeu::generAleatoireSelonLoiNormal()
/// Cette fonction genere un double al�atoire selon une loi nominale
///
/// @param[in] : aucun
///
/// @return double.
///
////////////////////////////////////////////////////////////////////////


float  GestionnaireJeu::generAleatoireSelonLoiNormal()
{
	std::random_device rd;
    std::mt19937 gen(rd());
 
    // values near the mean are the most likely
    // standard deviation affects the dispersion of generated values from the mean
	// www.cppfrance.com
    std::normal_distribution<> d(2,4);
	float number = static_cast<float>(d(gen));
    
    
	if ((number>=0.2)&&(number<=5)) 
		return  number ;
	else 
		return 1;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireJeu::generAleatoire(int min , int max)
/// Cette fonction genere un entier al�atoire entre min et max
///
/// @param[in] : int min , int max
///
/// @return int.
///
////////////////////////////////////////////////////////////////////////
double  GestionnaireJeu::generAleatoire(double min , double max)
{
	int modulus = static_cast<int>(max - min);
	double random = rand()%(modulus);
	random += min +1;
	return random;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireJeu::obtenirCadreDepartAsteroide(Vecteur3 &minXY , Vecteur3 &maxXY )
/// Cette fonction renvoie les coordon�es du cadre de depart
///
/// @param[in] : Vecteur3 &minXY , Vecteur3 &maxXY
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////

void  GestionnaireJeu::obtenirCadreDepartAsteroide(Vecteur3 &minXY , Vecteur3 &maxXY )
{
	Vecteur3 zoneMinXY , zoneMaxXY ;
		
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirZoneJeu()->obtenirBoiteEnglobante(zoneMinXY , zoneMaxXY);

	double hauteurZoneJeu = 0 , largeurZoneJeu = 0 ;

	largeurZoneJeu = abs(zoneMaxXY[0] - zoneMinXY [0]);
	hauteurZoneJeu = abs(zoneMaxXY[1] - zoneMinXY [1]);

	minXY[0] = zoneMinXY [0] - ( 0.3 * largeurZoneJeu )/2;
	maxXY[0] = zoneMaxXY [0] + ( 0.3 * largeurZoneJeu )/2;

	minXY[1] = zoneMinXY [1] - ( 0.3 * largeurZoneJeu )/2;
	maxXY[1] = zoneMaxXY [1] + ( 0.3 * largeurZoneJeu )/2;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireJeu::obtenirCadreDepartAsteroide(Vecteur3 &minXY , Vecteur3 &maxXY )
/// Cette fonction renvoie les coordon�es de la zone de passage
///
/// @param[in] : Vecteur3 &minXY , Vecteur3 &maxXY
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////

void  GestionnaireJeu::obtenirZoneDePassageAsteroide(Vecteur3 &minXY , Vecteur3 &maxXY )
{
	Vecteur3 zoneMinXY , zoneMaxXY ;
		
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirZoneJeu()->obtenirBoiteEnglobante(zoneMinXY , zoneMaxXY);

	double hauteurZoneJeu = 0 , largeurZoneJeu = 0 ;

	largeurZoneJeu = abs(zoneMaxXY[0] - zoneMinXY [0]);
	hauteurZoneJeu = abs(zoneMaxXY[1] - zoneMinXY [1]);

	minXY[0] = -( 0.7 * largeurZoneJeu )/2;
	maxXY[0] =  ( 0.7 * largeurZoneJeu )/2;

	minXY[1] = -( hauteurZoneJeu - 0.3 * largeurZoneJeu )/2;
	maxXY[1] =  ( hauteurZoneJeu - 0.3 * largeurZoneJeu )/2;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireJeu::assignerPositionVitesseAsteroide(NoeudAbstrait * asteroide)
/// Cette fonction assigne position et vitesse a l asteroide
///
/// @param[in] : NoeudAbstrait * asteroide
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////

void GestionnaireJeu::assignerPositionVitesseAsteroide(NoeudAbstrait * asteroide)
{
	Vecteur3 zoneMinXY , zoneMaxXY , position , vitesse, CadreDepartAsteroideMaxXY , CadreDepartAsteroideMinXY , ZoneDePassageAsteroideMaxXY, ZoneDePassageAsteroideMinXY;
				
	obtenirCadreDepartAsteroide(CadreDepartAsteroideMinXY , CadreDepartAsteroideMaxXY );

	obtenirZoneDePassageAsteroide(ZoneDePassageAsteroideMinXY , ZoneDePassageAsteroideMaxXY);

	int coteCadreDepart = static_cast<int>(generAleatoire(1.0, 4.0));		
	double vitesseAsteroide = generAleatoire(vitesseMinAsteroide, vitesseMaxAsteroide) ;

	switch (coteCadreDepart)
	{
		case 1 :
			static_cast<NoeudAsteroide*> (asteroide)->setCoteOuCree(1);
			position[0] = generAleatoire(CadreDepartAsteroideMinXY[0], CadreDepartAsteroideMaxXY [0] ) ;
			position[1] = CadreDepartAsteroideMaxXY[1];
				
		break;

		case 2 :
				
			static_cast<NoeudAsteroide*> (asteroide)->setCoteOuCree(2);
			position[0] = CadreDepartAsteroideMaxXY[0];
			position[1] = generAleatoire(CadreDepartAsteroideMinXY[1], CadreDepartAsteroideMaxXY [1] ) ;
	
		break;

		case 3 :
			static_cast<NoeudAsteroide*>(asteroide)->setCoteOuCree(3);
			position[0] = generAleatoire(CadreDepartAsteroideMinXY[0], CadreDepartAsteroideMaxXY [0] ) ;
			position[1] = CadreDepartAsteroideMinXY[1];
				
	    break;

		case 4 :
			static_cast<NoeudAsteroide*> (asteroide)->setCoteOuCree(4);
			position[0] = CadreDepartAsteroideMinXY[0];
			position[1] = generAleatoire(CadreDepartAsteroideMinXY[1], CadreDepartAsteroideMaxXY [1] ) ;
				
			
		break;
	}

	asteroide->assignerPositionRelative(position);

	vitesse = genererDirectionNormalise(position)* vitesseAsteroide ;

	static_cast<NoeudAsteroide*> (asteroide)-> setVitesse(vitesse);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireJeu::genererDirectionNormalise( Vecteur3 positionAsteroide)
/// Cette fonction assigne la direction normalise a un asteroide
///
/// @param[in] : Vecteur3 positionAsteroide
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////

Vecteur3 GestionnaireJeu::genererDirectionNormalise( Vecteur3 positionAsteroide)
{
	Vecteur3 pointDansZonePassage , directionNormalise ;
	Vecteur3 ZoneDePassageAsteroideMaxXY, ZoneDePassageAsteroideMinXY;
	
	obtenirZoneDePassageAsteroide(ZoneDePassageAsteroideMinXY , ZoneDePassageAsteroideMaxXY);

	pointDansZonePassage [0] = generAleatoire(ZoneDePassageAsteroideMinXY [0] , ZoneDePassageAsteroideMaxXY [0]);
	pointDansZonePassage [1] = generAleatoire(ZoneDePassageAsteroideMinXY [1] , ZoneDePassageAsteroideMaxXY [1]);


	directionNormalise = pointDansZonePassage - positionAsteroide ;
	directionNormalise.normaliser();

	return directionNormalise;



}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireJeu::fixerVitesseMaxMinAsteroide(float&vitesseMin ,float&vitesseMax , int difficulte )
/// Cette fonction qui fixe la vitesse maximale et minimale d'un asteroide selon le niveau de difficulte de la partie
///
/// @param[in] : float&vitesseMin ,float&vitesseMax , int difficulte
///
/// @return aucun.
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void GestionnaireJeu::fixerVitesseMaxMinAsteroide(float&vitesseMin ,float&vitesseMax , int difficulte )
{
	if(difficulte >= 1 && difficulte <=10)
	{
		vitesseMax = static_cast<float>(difficulte * 15);
		vitesseMin = vitesseMax - 15 ;
	}
	else if(difficulte <1)
	{
		vitesseMax = 15.0f ;
		vitesseMin = vitesseMax - 15 ;
	}
	else
	{
		vitesseMax = 150.0f ;
		vitesseMin = vitesseMax - 15 ;
	}

	
}


//Partie * GestionnaireJeu::getPartie()
//{
//	return this->partie ;
//}

void GestionnaireJeu::assignerPartieSolo(bool value)
{
	partieSolo_ = value;
}

void GestionnaireJeu::assignerPartieCoopHumain(bool value)
{
	partieCoopHumain_ = value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireJeu::mettreAjourPointDeVieStationSpatiale(int pointDeVie)
/// Cette fonction qui met a jour les poins de vie des stations dans la zone de jeu
///
/// @param[in] : int pointDeVie
///
/// @return aucun.
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void GestionnaireJeu::mettreAjourPointDeVieStationSpatiale()
{
	int pointDeVie= (ConfigJeu::obtenirInstance()->getptvie() >= 1) ? ConfigJeu::obtenirInstance()->getptvie() : 1;
	for(unsigned int i = 0 ; i < FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirNombreEnfants(); i ++ )
	{
		if(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(i)->obtenirType()=="stationSpatiale")
		{
			static_cast <NoeudStationSpatiale* > (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(i))->setPointDeVie(pointDeVie);
			
		}
	}

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireJeu::simulerExplosion(NoeudAbstrait * noeudAnimation)
/// Cette fonction 
///
/// @param[in] : 
///
/// @return aucun.
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void GestionnaireJeu::simulerExplosion(NoeudAbstrait * noeud, float tempsAnimation , string typeNoeud)
{
		NoeudAbstrait * noeudAnimation = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->creerNoeud("animation");
		noeudAnimation->setEchelle(noeud->getEchelle() / 2);
 		noeudAnimation->assignerPositionRelative( noeud->obtenirPositionRelative() );
		static_cast <NoeudAnimation*>(noeudAnimation)->assignerDuree( tempsAnimation );
		listeAnimation.push_back(noeudAnimation);
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter( noeudAnimation );
		if(typeNoeud == "asteroide")
			GestionnaireAudio::obtenirInstance()->jouerAudioDestructionAsteroide();
		else
			GestionnaireAudio::obtenirInstance()->jouerAudioDestructionStationSpatiale();
		
		
		

		
}
	

void GestionnaireJeu::updateAnimation(float temps)
{
	for(int i = 0 ; i < listeAnimation.size() ; i++)
	{
		static_cast <NoeudAnimation*>(listeAnimation [i])->assignerDuree(static_cast <NoeudAnimation*>(listeAnimation [i])->obtenirDuree() - temps );
		
	}
	
	for(int i = 0 ; i < listeAnimation.size() ; i++)
	{
		if(static_cast <NoeudAnimation*>(listeAnimation [i])->obtenirDuree() <= 0.0 )
		{
 			listeAnimation [i]->assignerAffiche(false);
				
		}
	}
	//if( listeAnimation.size() > 0)
	//{
	//	// mettre � jour la dur�e des noeuds d'animation  de la liste
	//	for(int i = 0 ; i < listeAnimation.size() ; i++)
	//	{
	//		static_cast <NoeudAnimation*>(listeAnimation [i])->assignerDuree(static_cast <NoeudAnimation*>(listeAnimation [i])->obtenirDuree() - temps );
	//		
	//	}
	//	// effacer les animations dont la dur�e s'est �coul�e 
	//	for(int i = 0 ; i < listeAnimation.size() ; i++)
	//	{
	//		if(static_cast <NoeudAnimation*>(listeAnimation [i])->obtenirDuree() <= 0.0 )
	//		{
	//	
	//			//FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(listeAnimation [i]);
	//			listeAnimation.erase(listeAnimation.begin()+i);

	//		}
	//	}
	//}

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireJeu:: effacerAsteroide()
/// Cette fonction parcourit la liste des asteroides et efface ceux qui sont disable
///
/// @param[in] : aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void GestionnaireJeu::effacerAnimation()
{
	/*for(int i = 0 ; i < listeAnimation.size() ; i++)
	{
 		if(!listeAnimation[i]->estAffiche())
		{
			
  			FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(listeAnimation[i]);
			listeAnimation.erase( listeAnimation.begin() + i );
		}
	
	}*/
  for(unsigned int i = 0 ; i < FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirNombreEnfants() ; i++)
  {
	 
	  if(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirType() == "animation")
		if( !FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->estAffiche() )
		{
			NoeudAbstrait * noeud ;
			noeud = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher( i );
			FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer( noeud );
		}
  }


}


////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireJeu::effacerTousAsteroide()
/// Cette fonction efface tous les asteroides dans la liste
///
/// @param[in] : aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////


void GestionnaireJeu::effacerTousAnimation()
{
	for(int i = 0 ; i < listeAnimation.size() ; i++)
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(listeAnimation[i]);
	}

	listeAnimation.clear();
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////