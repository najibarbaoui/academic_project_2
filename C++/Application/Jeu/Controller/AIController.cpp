//////////////////////////////////////////////////////////////////////////////
/// @file AIController.cpp
/// @author Najib Arbaoui
/// @date 2014-03-24
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#include "AIController.h"

#include <time.h>
#include <sys/timeb.h>

#include "FacadeModele.h"
#include "GestionnaireJeu.h"
#include "Visiteurs\VisiteurAIChercheCible.h"
#include "Visiteurs\VisiteurAIStationDansFace.h"
#include "Visiteurs\VisiteurNoeudExiste.h"
#include "Visiteurs\VisiteurAIStationDansFace.h"

NoeudVaisseau* AIController::getVaisseau()
{
	if (vaisseau_ == NULL)
	{
		vaisseau_ = GestionnaireJeu::obtenirInstance()->getPlayer(2)->getVaisseau();;
	}

	return vaisseau_;
}

AIController::AIController()
{
	// Initialis� en mode approche
	etatAI_ = RECHERCHE;
	SortieConsole();

	vaisseau_ = NULL;

	cible_ = NULL;

	// Actions
	accelerer_ = false;
	demitour_ = false;
	tournerGauche_ = false;
	tournerDroite_ = false;
	tirer_ = false;
}

AIController::~AIController()
{
}

void AIController::update(float temps)
{
	switch (etatAI_)
	{
	case RECHERCHE:
		updateRecherche(temps);
		break;
	case APPROCHE:
		updateApproche(temps);
		break;
	case ATTAQUE:
		updateAttaque(temps);
		break;
	}
}

void AIController::keyPressed(int keyCode)
{
	// On ignore les key events
}

void AIController::keyReleased(int keyCode)
{
	// On ignore les key events
}

bool AIController::getCommand(PlayerAction action)
{
	switch (etatAI_)
	{
	case RECHERCHE:
		return getCommandRecherche(action);
	case APPROCHE:
		return getCommandApproche(action);
	case ATTAQUE:
		return getCommandAttaque(action);
	default:
		return false;
	}
}
	
void AIController::updateRecherche(float temps)
{
	if (cible_ == NULL)
	{
		VisiteurAIChercheCible v(getVaisseau());
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(v);

		cible_ = v.obtenirCible();
			
		if (cible_ != NULL)
		{
			// Changer d'�tat
			this->etatAI_ = APPROCHE;
			SortieConsole();
			this->updateApproche(temps);
			return;
		}
	}
}

void AIController::updateApproche(float temps)
{
	VisiteurNoeudExiste v(cible_);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(v);

	if (!v.obtenirExiste())
	{
		cible_ = NULL;
		// Changer d'�tat
		this->etatAI_ = RECHERCHE;
		SortieConsole();
		this->updateRecherche(temps);
		return;
	}
	else
	{
		Vecteur3 minXY, maxXY;
		cible_->obtenirBoiteEnglobante(minXY, maxXY);
		bool estDansZoneJeu = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->estDansZoneJeu(minXY, maxXY);

		if (!estDansZoneJeu)
		{
			cible_ = NULL;
			// Changer d'�tat
			this->etatAI_ = RECHERCHE;
			SortieConsole();
			this->updateRecherche(temps);
			return;
		}
		else
		{
			// Si assez proche, on passe en mode attaque
			if ((cible_->obtenirPositionRelative() - getVaisseau()->obtenirPositionRelative()).norme() < 100)
			{
				tirer_ = false;
				// Changer d'�tat
				this->etatAI_ = ATTAQUE;
				SortieConsole();
				this->updateAttaque(temps);
				return;
			}
			else
			{
				// Calcule la diff�rence d'angle, et s'assure que l'angle est entre -180 et 180 degr�s
				Vecteur3 direction = (cible_->obtenirPositionRelative() - getVaisseau()->obtenirPositionRelative());
				double angleVersCible = utilitaire::RAD_TO_DEG(direction.lireTheta());
				double angleVaisseau = getVaisseau()->getAngleRotation();
				double differenceAngle = angleVersCible - angleVaisseau;// + 90;
				differenceAngle = fmod(differenceAngle, 360);
				if (differenceAngle > 180)
				{
					differenceAngle -= 360;
				}
				else if (differenceAngle < -180)
				{
					differenceAngle += 360;
				}
		
				assert (differenceAngle < 180 && differenceAngle > -180);

				// On g�re le demi tour
				if (abs(differenceAngle) > 90)
				{
					demitour_ = true;
				}

				// On gere l'acceleration
				if (abs(differenceAngle) < 45)
				{
					accelerer_ = true;
				}
				else
				{
					accelerer_ = false;
				}

				if (differenceAngle < 5 && differenceAngle > -5)
				{
					tournerGauche_ = false;
					tournerDroite_ = false;
				}
				else if (differenceAngle > 0)
				{
					tournerGauche_ = true;
					tournerDroite_ = false;
				}
				else
				{
					tournerGauche_ = false;
					tournerDroite_ = true;
				}
			}
		}
	}
}

void AIController::updateAttaque(float temps)
{
	VisiteurNoeudExiste v(cible_);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(v);

	if (!v.obtenirExiste())
	{
		cible_ = NULL;
		// Changer d'�tat
		this->etatAI_ = RECHERCHE;
		SortieConsole();
		this->updateRecherche(temps);
		return;
	}
	else
	{
		Vecteur3 minXY, maxXY;
		cible_->obtenirBoiteEnglobante(minXY, maxXY);
	
		if (!FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->estDansZoneJeu(minXY, maxXY))
		{
			cible_ = NULL;
			// Changer d'�tat
			this->etatAI_ = RECHERCHE;
			SortieConsole();
			this->updateRecherche(temps);
			return;
		}
		else
		{
			// Calcule la diff�rence d'angle, et s'assure que l'angle est entre -180 et 180 degr�s
			Vecteur3 direction = (cible_->obtenirPositionRelative() - getVaisseau()->obtenirPositionRelative());
			double angleVersCible = utilitaire::RAD_TO_DEG(direction.lireTheta());
			double angleVaisseau = getVaisseau()->getAngleRotation();
			double differenceAngle = angleVersCible - angleVaisseau;// + 90;
			differenceAngle = fmod(differenceAngle, 360);
			if (differenceAngle > 180)
			{
				differenceAngle -= 360;
			}
			else if (differenceAngle < -180)
			{
				differenceAngle += 360;
			}
		
			assert (differenceAngle < 180 && differenceAngle > -180);

			if (differenceAngle < 2 && differenceAngle > -2)
			{
				tournerGauche_ = false;
				tournerDroite_ = false;
			}
			else if (differenceAngle > 0)
			{
				tournerGauche_ = true;
				tournerDroite_ = false;
			}
			else
			{
				tournerGauche_ = false;
				tournerDroite_ = true;
			}

			// Verifie si le AI doit tirer
			VisiteurAIStationDansFace v(this->getVaisseau());
			FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepter(v);

			if (v.obtenirStationDansFace())
			{
				tirer_ = false;
			}
			else
			{
				tirer_ = true;
			}
		}
	}
}

bool AIController::getCommandRecherche(PlayerAction action)
{
	// On ne fait rien lorsqu'en mode recherche
	return false;
}

bool AIController::getCommandApproche(PlayerAction action)
{
	assert(cible_ != NULL);

	switch (action)
	{
	case ACCELERER:
		return accelerer_;
	case DEMITOUR:
		if (demitour_)
		{
			demitour_ = false;
			return true;
		}
		else
		{
			return false;
		}
	case GAUCHE:
		return tournerGauche_;
	case DROITE:
		return tournerDroite_;
	case TIRER:
		return false;
	default:
		return false;
	}
}

bool AIController::getCommandAttaque(PlayerAction action)
{
	assert(cible_ != NULL);

	switch (action)
	{
	case ACCELERER:
		return false;
	case DEMITOUR:
		return false;
	case GAUCHE:
		return tournerGauche_;
	case DROITE:
		return tournerDroite_;
	case TIRER:
		return tirer_;
	default:
		return false;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn std::string AIController::TimeToString() const 
///
/// Permet d'avoir le temps courant dans le format "HH:MM:SS:mm" que le stocke dans un std::string.
///
/// Sert � imprimer le temps dans le format "HH:MM:SS:mm" � la console.
///
/// @param Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
std::string AIController::TimeToString() const 
{
    timeval tp;
    //gettimeofday(&tp, 0);
	struct _timeb timebuffer;
	_ftime_s (&timebuffer);
	tp.tv_sec = static_cast<long>(timebuffer.time);
	tp.tv_usec = timebuffer.millitm * 1000;

    time_t curtime = tp.tv_sec;
    tm *t = localtime(&curtime);
	char timeString[80];  // space for "HH:MM:SS:mm\0"
    sprintf_s(timeString, "%02d:%02d:%02d:%02d", t->tm_hour, t->tm_min, t->tm_sec, tp.tv_usec/1000);

	return std::string(timeString);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAsteroide::SortieConsole() const
///
/// Quand un ast�ro�de est cr��, la ligne suivante doit �tre affich�e � la console:
/// HH:MM:SS:mm Cr�ation d'ast�ro�de x: POSX	y: POSY	vi: VI	t: T
///
/// O� POSX repr�sente la position en x, POSY la position en Y, VI le module de la vitesse initiale, T la taille de l�ast�ro�de.
///
/// @param Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void AIController::SortieConsole() const
{
	if(ConfigJeu::obtenirInstance()->isChangementJoueurVirtuel()) {
		string modeStr;
		switch (etatAI_)
		{
		case RECHERCHE:
			modeStr = "RECHERCHE";
			break;
		case APPROCHE:
			modeStr = "APPROCHE";
			break;
		case ATTAQUE:
			modeStr = "ATTAQUE";
			break;
		}

		const char* tab = "\t";
		std::string strTime = TimeToString();
		cout << strTime << " - " << "JV passage au mode : " <<  modeStr << endl;
	}
	
}

//////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////