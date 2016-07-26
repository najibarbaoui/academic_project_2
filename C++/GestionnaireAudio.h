//////////////////////////////////////////////////////////////////////////////
/// @file   GestionnaireAudio.h
/// @author Najib Arbaoui
/// @date   2014-04-09
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __APPLICATION_GESTIONNAIREAUDIO_H__
#define __APPLICATION_GESTIONNAIREAUDIO_H__


#include "Singleton.h"
#include "fmod.hpp"
//#include "FacadeModele.h"
//#include "GestionnaireJeu.h"
#include "Utilitaire.h"

 


// Classe gui gere les fichiers audios joues dans la partie rapide et compagne

class GestionnaireAudio: public Singleton<GestionnaireAudio>
{
	SINGLETON_DECLARATION_CLASSE_SANS_CONSTRUCTEUR(GestionnaireAudio);

private:
	FMOD_SYSTEM *systeme;
// les sons joues dans le jeu
	FMOD_SOUND *audioActivationBonusAccelerateur ;
	FMOD_SOUND *audioCollision ;
	FMOD_SOUND *audioDestructionAsteroide ;
	FMOD_SOUND *audioDestructionStationSpatiale ;
	FMOD_SOUND *audioTirProjectile ;
	FMOD_SOUND *audioUtilisationPortail ;
	FMOD_SOUND *audioArrierePlan ;
	FMOD_CHANNEL *canaux[7];


public :
	GestionnaireAudio();
	~GestionnaireAudio();
	void jouerAudioActivationBonusAccelerateur();
	void jouerAudioCollision();
	void jouerAudioDestructionAsteroide();
	void jouerAudioDestructionStationSpatiale();
	void jouerAudioTirProjectile();
	void jouerAudioUtilisationPortail();
	void jouerAudioArrierePlan();
	void mettreAudioArrierePlanPause(bool estPause);
	void arreterAudioArrierePlan();
	void arreterAudio();


};
#endif // __APPLICATION_GESTIONNAIREAUDIO_H__

////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////