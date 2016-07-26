///////////////////////////////////////////////////////////////////////////
/// @file VisiteurAfficherTexte.cpp
/// @author Ousmane
/// @date 2014-04-11
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "VisiteurAfficherTexte.h"

#include "ArbreRenduINF2990.h"
#include "FacadeModele.h"

VisiteurAfficherTexte::VisiteurAfficherTexte()
{
	afficherTexte_ = new AfficherTexte();
	afficherTexte_->Prog_Init(15);
}

VisiteurAfficherTexte::~VisiteurAfficherTexte()
{
	delete afficherTexte_;
}



void VisiteurAfficherTexte::visiter(NoeudAbstrait& noeudAbstrait)
{
}

void VisiteurAfficherTexte::visiter(NoeudComposite& noeudComposite)
{
	for(unsigned int i = 0; i < noeudComposite.obtenirNombreEnfants(); ++i)
	{
		noeudComposite.chercher(i)->accepter(*this);
	}
}

void VisiteurAfficherTexte::visiter(NoeudAsteroide & noeudAsteroide)
{
}

void VisiteurAfficherTexte::visiter(NoeudBarriereProtectrice & noeudBarriereProtectrice)
{
}

void VisiteurAfficherTexte::visiter(NoeudBonusAccelerateur & noeudBonusAccelerateur )
{
}

void VisiteurAfficherTexte::visiter(NoeudPortail & noeudPortail)
{		
}

void VisiteurAfficherTexte::visiter(NoeudPositionDepart & noeudPositionDepart )
{
}

void VisiteurAfficherTexte::visiter(NoeudProjectile & noeudProjectile ) 
{
}

void VisiteurAfficherTexte::visiter(NoeudStationSpatiale & noeudStationSpatiale)
{
	
	Vecteur3 minXY, maxXY;
	noeudStationSpatiale.obtenirBoiteEnglobante(minXY, maxXY);
		stringstream ss (stringstream::in | stringstream::out);
		int ptVie = noeudStationSpatiale.obtenirPtVie();
		ss << "Vie : ";
		ss << ptVie;
		std::string temps = ss.str();
		ss.clear();
		if(ptVie != 0){
		 afficherTexte_->Prog_Loop(minXY[0]+5,minXY[1]-1.5,false,temps);
		}
}

void VisiteurAfficherTexte::visiter(NoeudVaisseau & noeudVaisseau)
{
}

void VisiteurAfficherTexte::visiter(NoeudZoneJeu & noeudZoneJeu )
{
	stringstream ss (stringstream::in | stringstream::out);
	float tempsPartie = Partie::obtenirInstance()->getTempsPartie();
	int minute = tempsPartie/60;
	int seconde = (int)tempsPartie % 60;
	if(minute < 10)
		ss << 0;
	ss << minute;
	ss << ":";
	if(seconde < 10)
		ss << 0;
	ss << seconde;
	std::string temps = ss.str();
	ss.clear();
	Vecteur3 minXY, maxXY;
	noeudZoneJeu.obtenirBoiteEnglobante(minXY,maxXY);
	afficherTexte_->Prog_Loop(0.0,0.0,true,temps);
}

void VisiteurAfficherTexte::visiter(NoeudZonePassage & noeudZonePassage )
{

	/*Vecteur3 minXY, maxXY;
	noeudZonePassage.obtenirBoiteEnglobante(minXY,maxXY);
	if(Partie::obtenirInstance()->isTermine())
	{
		if(Partie::obtenirInstance()->getIsGagne()){
				std::string score = "Bravo! Tu as gagné.\n";
				afficherTexte_->Prog_Loop(0.0,minXY[1]-1,false,score.c_str());
				
		}else
		{
				std::string score = "OH! Tu as perdu.";
				afficherTexte_->Prog_Loop(0.0,minXY[1]-1,false,score.c_str());
		}
	}*/
}
void VisiteurAfficherTexte::visiter(NoeudAnimation & noeudAnimation )
{

}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////