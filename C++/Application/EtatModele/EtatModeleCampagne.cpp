//////////////////////////////////////////////////////////////////////////////
/// @file EtatModeleCampagne.cpp
/// @author Olivier Cotte
/// @date 2014-03-23
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#include "EtatModeleCampagne.h"
#include "GestionnaireJeu.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatModeleCampagne::EtatModeleCampagne() 
///
/// Inititialise l'état du modèle
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
EtatModeleCampagne::EtatModeleCampagne() 
{
	this->etatId_ = ETATCAMPAGNE;
	m_mapInstance.insert(pair<string, EtatActionPartie >("Solo",SOLO));
	m_mapInstance.insert(pair<string, EtatActionPartie >("Humain", HUMAIN));
	m_mapInstance.insert(pair<string, EtatActionPartie >("Virtuel", VIRTUEL));
}




////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatModeleCampagne::buttonPressed(string action)
///
/// Cette fonction fournit les parties possibles solo ou cooperative
/// avec humain ou avec virtuel
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void EtatModeleCampagne::buttonPressed(string action)
{
	std::map<string, EtatActionPartie>::iterator it;
	it = m_mapInstance.find(action);
	if(it != m_mapInstance.end()) {
		 if(m_mapInstance.find(action)->second == SOLO)
		 {
			 GestionnaireJeu::obtenirInstance()->assignerPartieSolo(true);
		 }
		 else if(m_mapInstance.find(action)->second == HUMAIN)
		 {
			 GestionnaireJeu::obtenirInstance()->assignerPartieSolo(false);
			 GestionnaireJeu::obtenirInstance()->assignerPartieCoopHumain(true);
		 }
		 else if(m_mapInstance.find(action)->second == VIRTUEL)
		 {
			 GestionnaireJeu::obtenirInstance()->assignerPartieSolo(false);
			 GestionnaireJeu::obtenirInstance()->assignerPartieCoopHumain(false);
		 }
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////