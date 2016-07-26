//////////////////////////////////////////////////////////////////////////////
/// @file AIController.h
/// @author Najib Arbaoui
/// @date 2014-03-24
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef __APPLICATION_JEU_CONTROLLER_AICONTROLLER_H__
#define __APPLICATION_JEU_CONTROLLER_AICONTROLLER_H__

#include "Controller.h"

#include "NoeudAsteroide.h"

enum EtatAI {RECHERCHE, APPROCHE, ATTAQUE};

class AIController : public Controller
{
protected:
	NoeudVaisseau* getVaisseau();

	EtatAI etatAI_;
	NoeudVaisseau* vaisseau_;
	NoeudAsteroide* cible_;
	
	bool accelerer_;
	bool demitour_;
	bool tournerGauche_;
	bool tournerDroite_;
	bool tirer_;

public:
	AIController();
	~AIController();

	virtual void update(float temps);
	virtual void keyPressed(int keyCode);
	virtual void keyReleased(int keyCode);

	virtual bool getCommand(PlayerAction action);

	void updateRecherche(float temps);
	void updateApproche(float temps);
	void updateAttaque(float temps);
	
	bool getCommandRecherche(PlayerAction action);
	bool getCommandApproche(PlayerAction action);
	bool getCommandAttaque(PlayerAction action);

	void AIController::SortieConsole() const;
	std::string AIController::TimeToString() const;
};

#endif // __APPLICATION_JEU_CONTROLLER_AICONTROLLER_H__

//////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////