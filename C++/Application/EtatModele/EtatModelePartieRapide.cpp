//////////////////////////////////////////////////////////////////////////////
/// @file EtatModelePartieRapide.cpp
/// @author Najib Arbaoui
/// @date 2014-03- 20
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#include "EtatModelePartieRapide.h"
#include "GestionnaireJeu.h"

EtatModelePartieRapide::EtatModelePartieRapide() 
{
	this->etatId_ = ETATPARTIERAPIDE;
	m_mapInstance.insert(pair<string, EtatActionPartie >("Solo",SOLO));
	m_mapInstance.insert(pair<string, EtatActionPartie >("Humain", HUMAIN));
	m_mapInstance.insert(pair<string, EtatActionPartie >("Virtuel", VIRTUEL));

}

void EtatModelePartieRapide::mouseMoved(int x, int y, bool ctrlPressed, bool altPressed)
{
}
	
void EtatModelePartieRapide::mousePressed(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
}
	
void EtatModelePartieRapide::mouseClicked(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
}
	
void EtatModelePartieRapide::mouseDragged(int x, int y, int dx, int dy, bool ctrlPressed, bool altPressed)
{
}
	
void EtatModelePartieRapide::mouseReleased(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatModelePartieRapide::buttonPressed(string action)
///
/// Cette fonction fournit les parties possibles solo ou cooperative
/// avec humain ou avec virtuel
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void EtatModelePartieRapide::buttonPressed(string action)
{
	it = m_mapInstance.end();
	it = m_mapInstance.find(action);
	if(it != m_mapInstance.end()){
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