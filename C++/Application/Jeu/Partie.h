//////////////////////////////////////////////////////////////////////////////
/// @file Partie.h
/// @author Najib Arbaoui
/// @date 2014-03-22
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef __APPLICATION_JEU_PARTIE_H__
#define __APPLICATION_JEU_PARTIE_H__

#include "Singleton.h"

#include "NoeudStationSpatiale.h"

#include <vector>
#include <iostream>


class Partie : public Singleton<Partie>
{
	SINGLETON_DECLARATION_CLASSE_SANS_CONSTRUCTEUR(Partie);
	public:
		Partie();
		~Partie();
		Partie( float tempsPartie , int nbrStationSpatiale);
		void setPartie( float tempsPartie , int nbrStationSpatiale);
		void setIsGagne(bool value);
		bool getIsGagne();
		void setIsValide(bool value);
		bool getIsValide();
		void ajouterStationSpatiale(NoeudAbstrait* noeud);
		void supprimerStationSpatiale();
		int  getNombreStationSpatialeRestante();
		void setTempsPartie(float temps );

		void setNombreStationSpatialePourGagner(int nombreStation);
		int getNombreStationSpatialePourGagner();


		float getTempsPartie();
		bool  isTermine();
		void updateTempsPartie(float temps);
		void supprimertoutesStationsSpatiales();

		vector <NoeudStationSpatiale*> getlisteStationSpatiale();

	private :
		bool isGagne_ ;
		bool isValide_ ;
		int nbrStationSpatialePourGagnerPartie_;
		vector <NoeudAbstrait*> listeStationSpatiale_ ;
		float tempsPartie_ ;

};


#endif