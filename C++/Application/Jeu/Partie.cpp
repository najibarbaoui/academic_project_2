//////////////////////////////////////////////////////////////////////////////
/// @file Partie.cpp
/// @author Najib Arbaoui
/// @date 2014-03-22
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#include "Partie.h"

#include "ArbreRenduINF2990.h"
#include "FacadeModele.h"

SINGLETON_DECLARATION_CPP(Partie);
// constructeur par defaut
Partie::Partie( )
{
	isValide_ = true;
	tempsPartie_ = 0.0;
	nbrStationSpatialePourGagnerPartie_ = 0 ;

	for(unsigned int i = 0 ; i < FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirNombreEnfants(); i ++ )
	{
		if(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(i)->obtenirType()=="stationSpatiale")
		{
			ajouterStationSpatiale(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(i));
		}
	}

}
// destructeur	
Partie::~Partie( )
{
	

}
// constructeur par partie
Partie::Partie( float tempsPartie , int nbrStationSpatiale)
{
	isValide_ = true;
	tempsPartie_ = tempsPartie ;
	nbrStationSpatialePourGagnerPartie_ = nbrStationSpatiale;
	
	for(unsigned int i = 0 ; i < FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirNombreEnfants(); i ++ )
	{
		if(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(i)->obtenirType()=="stationSpatiale")
		{
			ajouterStationSpatiale(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(i));
		}
	}
}

// set par partie
void Partie::setPartie( float tempsPartie , int nbrStationSpatiale)
{
	isValide_ = true;
	tempsPartie_ = tempsPartie ;
	nbrStationSpatialePourGagnerPartie_ = nbrStationSpatiale;
	
	for(unsigned int i = 0 ; i < FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirNombreEnfants(); i ++ )
	{
		if(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(i)->obtenirType()=="stationSpatiale")
		{
			ajouterStationSpatiale(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(i));
		}
	}
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void Partie::setIsGagne(bool value)
///
/// Cette fonction permet mettre a jour l etat gagne de la partie
///
/// @param[in] value: valeur booleane
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////


void Partie::setIsGagne(bool value)
{
	isGagne_ = value ;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn bool Partie::getIsGagne()
///
/// Cette fonction renvoie la valeur de isGagne, true si partie est gagne et false si la partie est perdue
///
/// @param[in] : aucun 
///
/// @return booleane.
///
////////////////////////////////////////////////////////////////////////

bool Partie::getIsGagne()
{
	if(isTermine())
	{
		return isGagne_ = (getNombreStationSpatialeRestante()>= getNombreStationSpatialePourGagner()) ? true : false;
	}
	else
	{
		return false;
	}
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void Partie::setIsValide(bool value)
///
/// Cette fonction permet mettre a jour l etat valide de la partie
///
/// @param[in] value: valeur booleane
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Partie::setIsValide(bool value)
{
	isValide_ = value ;

}
////////////////////////////////////////////////////////////////////////
///
/// @fn bool Partie::getIsValide()
///
/// Cette fonction renvoie la valeur de isValide, true si partie est valide
///
/// @param[in] : aucun 
///
/// @return booleane.
///
////////////////////////////////////////////////////////////////////////
bool Partie::getIsValide()
{
	return isValide_ ;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void Partie::ajouterStationSpatiale(NoeudAbstrait* noeud)
///
/// Cette fonction ajoute station spatiale une liste qui contient les stations spatiales disponibles
/// dans la zone de jeu
/// @param[in] : NoeudAbstrait* noeud
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////

void Partie::ajouterStationSpatiale(NoeudAbstrait* noeud)
{
	listeStationSpatiale_.push_back(noeud);

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Partie::supprimerStationSpatiale()
///
/// Cette fonction supprime de la liste les stations spatiales detruites
/// 
/// @param[in] : aucun
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////

void Partie::supprimerStationSpatiale()
{
	for(int i = 0 ; i < listeStationSpatiale_.size() ; i++ )
		if(static_cast <NoeudStationSpatiale*>(listeStationSpatiale_[i])->obtenirPtVie() == 0 )
			listeStationSpatiale_.erase(listeStationSpatiale_.begin() + i );
}

vector <NoeudStationSpatiale*> Partie::getlisteStationSpatiale()
{
	vector <NoeudStationSpatiale*> liste;
	for(int i = 0 ; i < listeStationSpatiale_.size() ; i++ )
		liste.push_back(static_cast <NoeudStationSpatiale*>(listeStationSpatiale_[i]));
	return liste;
}
///////////////////////////////////////////////////////////////////////////
/// @fn int Partie::getNombreStationSpatialeRestante()
///
/// Cette fonction renvoie la valeur de isValide, true si partie est valide
///
/// @param[in] : aucun 
///
/// @return booleane.
///
////////////////////////////////////////////////////////////////////////
int Partie::getNombreStationSpatialeRestante()
{
	return static_cast<int>(listeStationSpatiale_.size());
}
///////////////////////////////////////////////////////////////////////////
/// @fn void Partie::setTempsPartie(float temps )
///
/// Cette fonction met a jour le temps de la partie
///
/// @param[in] : float temps 
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void Partie::setTempsPartie(float temps )
{
	tempsPartie_ = temps ;

}
///////////////////////////////////////////////////////////////////////////
/// @fn float  Partie::getTempsPartie()
///
/// Cette fonction renvoie le temps de la partie
///
/// @param[in] : aucun 
///
/// @return float.
///
////////////////////////////////////////////////////////////////////////
float Partie::getTempsPartie()
{
	return tempsPartie_;

}
///////////////////////////////////////////////////////////////////////////
/// @fn void Partie::updateTempsPartie(float temps)
///
/// Cette fonction mis a jour le temps de la partie
///
/// @param[in] : float temps
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////

void Partie::updateTempsPartie(float temps)
{
  
	tempsPartie_ = (tempsPartie_ - temps)>0 ?  tempsPartie_ - temps : 0;
	isGagne_ = (listeStationSpatiale_.size() >= nbrStationSpatialePourGagnerPartie_) ? true : false ;
}
///////////////////////////////////////////////////////////////////////////
/// @fn bool  Partie::isTermine()
///
/// Cette fonction verifie si la partie est terminee
///
/// @param[in] : aucun
///
/// @return bool.
///
////////////////////////////////////////////////////////////////////////

bool  Partie::isTermine()
{
	return (tempsPartie_ == 0) ? true : false;
}
///////////////////////////////////////////////////////////////////////////
/// @fn void Partie::supprimertoutesStationsSpatiales()
///
/// Cette fonction vide la liste des stations
///
/// @param[in] : aucun
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void Partie::supprimertoutesStationsSpatiales()
{
	listeStationSpatiale_.clear();

}
///////////////////////////////////////////////////////////////////////////
/// @fn void Partie::setNombreStationSpatialePourGagner(int nombreStation)
///
/// Cette fonction met a jour le nombre des stations spatiales pour gagner
///
/// @param[in] :int nombreStation
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void Partie::setNombreStationSpatialePourGagner(int nombreStation)
{
	nbrStationSpatialePourGagnerPartie_ = nombreStation ;

}
///////////////////////////////////////////////////////////////////////////
/// @fn int Partie::getNombreStationSpatialePourGagner()
///
/// Cette fonction renvoie  le nombre des stations spatiales pour gagner
///
/// @param[in] :aucun
///
/// @return int.
///
////////////////////////////////////////////////////////////////////////
int Partie::getNombreStationSpatialePourGagner()
{
	return nbrStationSpatialePourGagnerPartie_;
}

