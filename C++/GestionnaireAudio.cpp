////////////////////////////////////////////////
/// @file   GestionnaireAudio.cpp
/// @author Najib Arbaoui
/// @date   2014-04-09
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#include "GestionnaireAudio.h"



	// canaux [0] = audioActivationBonusAccelerateur ;
	// canaux [1] = audioCollision ;
	// canaux [2] = audioDestructionAsteroide ;
	// canaux [3] = audioDestructionStationSpatiale ;
	// canaux [4] = audioTirProjectile ;
	// canaux [5] = audioUtilisationPortail ;
	// canaux [6] = audioArrierePlan ;


SINGLETON_DECLARATION_CPP(GestionnaireAudio);

////////////////////////////////////////////////////////////////////////
///
/// @fn GestionnaireAudio::GestionnaireAudio()
///
/// Constructeur par defaut, initialise le systeme de son
///
/// @return aucun.
///
//////////////////////////////////////////////////////////////////////// 
GestionnaireAudio::GestionnaireAudio() 
{
	
	// canaux [0] = audioActivationBonusAccelerateur ;
	// canaux [1] = audioCollision ;
	// canaux [2] = audioDestructionAsteroide ;
	// canaux [3] = audioDestructionStationSpatiale ;
	// canaux [4] = audioTirProjectile ;
	// canaux [5] = audioUtilisationPortail ;
	// canaux [6] = audioArrierePlan ;

	FMOD_System_Create(&systeme);
	FMOD_System_Init(systeme,10, FMOD_INIT_NORMAL, NULL);

	FMOD_System_CreateSound(systeme, "media/audio/mp3/activationBonusAccelerateur.mp3", FMOD_DEFAULT, 0, &audioActivationBonusAccelerateur);
	FMOD_System_CreateSound(systeme, "media/audio/mp3/collision.mp3", FMOD_DEFAULT, 0, &audioCollision);
	FMOD_System_CreateSound(systeme, "media/audio/mp3/destructionAsteroide.mp3", FMOD_DEFAULT, 0, &audioDestructionAsteroide );
	FMOD_System_CreateSound(systeme, "media/audio/mp3/destructionStationSpatiale.mp3", FMOD_DEFAULT, 0, &audioDestructionStationSpatiale);
	FMOD_System_CreateSound(systeme, "media/audio/mp3/tirProjectile.mp3", FMOD_DEFAULT, 0, &audioTirProjectile);
	FMOD_System_CreateSound(systeme, "media/audio/mp3/utilisationPortail.mp3", FMOD_DEFAULT, 0, &audioUtilisationPortail );
	FMOD_System_CreateSound(systeme, "media/audio/mp3/arrierePlan.mp3", FMOD_DEFAULT|FMOD_LOOP_NORMAL, 0, &audioArrierePlan);

	for (int i = 0; i < 7; ++i)
	{
		
		FMOD_System_GetChannel(systeme, i, &canaux[i]);
		
	}

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireAudio::~GestionnaireAudio();
///
/// destructeur, libere le systeme de son
///
/// @return aucun.
///
//////////////////////////////////////////////////////////////////////// 
GestionnaireAudio::~GestionnaireAudio()
{
	
	FMOD_Sound_Release(audioActivationBonusAccelerateur) ;
	FMOD_Sound_Release(audioCollision);
	FMOD_Sound_Release(audioDestructionAsteroide);
	FMOD_Sound_Release(audioDestructionStationSpatiale);
	FMOD_Sound_Release(audioTirProjectile);
	FMOD_Sound_Release(audioUtilisationPortail);
	FMOD_Sound_Release(audioArrierePlan);
	FMOD_System_Close(systeme);
	FMOD_System_Release(systeme);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireAudio::
///
/// Cette fonction
///
/// @param[in]   :
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////

void GestionnaireAudio::jouerAudioActivationBonusAccelerateur()
{

	FMOD_CHANNEL * canal;
	FMOD_System_PlaySound(systeme, FMOD_CHANNEL_FREE, audioActivationBonusAccelerateur, 0, &canal); 
	canaux[0] = canal ; // canaux [0] = audioActivationBonusAccelerateur 
	FMOD_System_Update(systeme);


	
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireAudio::
///
/// Cette fonction
///
/// @param[in]   :
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void GestionnaireAudio::jouerAudioCollision()
{

	FMOD_CHANNEL * canal;
	FMOD_System_PlaySound(systeme, FMOD_CHANNEL_FREE, audioCollision, 0, &canal); 
	canaux[1] = canal ; // canaux [1] = audioCollision  
	FMOD_System_Update(systeme);

}
////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireAudio::
///
/// Cette fonction
///
/// @param[in]   :
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void GestionnaireAudio::jouerAudioDestructionAsteroide()
{

	FMOD_CHANNEL * canal;
	FMOD_System_PlaySound(systeme, FMOD_CHANNEL_FREE, audioDestructionAsteroide, 0, &canal); 
	canaux[2] = canal ; // canaux [2] = audioDestructionAsteroide ; 
	FMOD_System_Update(systeme);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireAudio::
///
/// Cette fonction
///
/// @param[in]   :
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void GestionnaireAudio::jouerAudioDestructionStationSpatiale()
{

	FMOD_CHANNEL * canal;
	FMOD_System_PlaySound(systeme, FMOD_CHANNEL_FREE, audioDestructionStationSpatiale, 0, &canal); 
	canaux[3] = canal ; // canaux [3] = audioDestructionStationSpatiale 
	FMOD_System_Update(systeme);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireAudio::
///
/// Cette fonction
///
/// @param[in]   :
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void GestionnaireAudio::jouerAudioTirProjectile() 
{
	FMOD_CHANNEL * canal;
	FMOD_System_PlaySound(systeme, FMOD_CHANNEL_FREE, audioTirProjectile, 0, &canal); 
	FMOD_Channel_SetVolume(canal, 0.2);
	canaux[4] = canal ; // canaux [4] = audioTirProjectile ;
	FMOD_System_Update(systeme);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireAudio::
///
/// Cette fonction
///
/// @param[in]   :
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void GestionnaireAudio::jouerAudioUtilisationPortail()
{
	
	FMOD_CHANNEL * canal;
	FMOD_System_PlaySound(systeme, FMOD_CHANNEL_FREE, audioUtilisationPortail, 0, &canal); 
	canaux[5] = canal ; // canaux [5] = audioUtilisationPortail 
	FMOD_System_Update(systeme);

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireAudio::
///
/// Cette fonction
///
/// @param[in]   :
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void GestionnaireAudio::jouerAudioArrierePlan()
{
	
	FMOD_CHANNEL * canal;
	FMOD_System_PlaySound(systeme, FMOD_CHANNEL_FREE, audioArrierePlan, 0,&canal);
	canaux[6] = canal ; // canaux [6] = audioArrierePlan ;
	FMOD_Channel_SetVolume(canaux[6], 0.2);
	FMOD_System_Update(systeme);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireAudio::
///
/// Cette fonction
///
/// @param[in]   :
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void GestionnaireAudio::mettreAudioArrierePlanPause(bool estPause)
{
	// canaux [6] = audioArrierePlan ;
	FMOD_Channel_SetPaused(canaux[6],estPause);
	

}
////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireAudio::
///
/// Cette fonction
///
/// @param[in]   :
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void GestionnaireAudio::arreterAudioArrierePlan()
{
	// canaux [6] = audioArrierePlan ;
	FMOD_Channel_Stop(canaux[6]);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireAudio::
///
/// Cette fonction
///
/// @param[in]   :
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void GestionnaireAudio::arreterAudio()
{
	for(int i = 0 ; i <7 ; i++)
	{
		FMOD_Channel_Stop(canaux[i]);
	}
}

//////////////////////////////////////////////////////////////////////////////