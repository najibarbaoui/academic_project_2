#include "Player.h"

#include "FacadeModele.h"
#include "Controller\PlayerController.h"
#include "Controller\AIController.h"

#include <iostream>

using namespace std;

Player::Player(int id, bool human)
{
	vaisseau_ =  (NoeudVaisseau*)FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->creerNoeud(ArbreRenduINF2990::NOM_VAISSEAU);

	// Assigner joueur 1 ou 2
	this->id_ = id;
	this->human_ = human;

	if (human_)
	{
		controller_ = new PlayerController();
	}
	else
	{
		controller_ = new AIController();
	}

	// Assigner les touches par défaut
	this->touchesParDefaut();

	// Créer le vaisseau
	NoeudPositionDepart* noeudPositionDepart;
	switch(id_)
	{
	case 1:
		noeudPositionDepart = FacadeModele::obtenirInstance()->positionUnPositionDepart();
		break;
	case 2:
		noeudPositionDepart = FacadeModele::obtenirInstance()->positionDeuxPositionDepart();
		break;
	}

	Vecteur3 v = noeudPositionDepart->obtenirPositionRelative();
	this->vaisseau_ = static_cast<NoeudVaisseau*>(FacadeModele::obtenirInstance()->creerNoeud(v[0], v[1], ArbreRenduINF2990::NOM_VAISSEAU));
	this->vaisseau_->setAngleRotation(noeudPositionDepart->getAngleRotation());

	// Tant qu'il est supérieur à 0.2, la valeur n'importe pas
	this->tempsDernierTir_ = 0.3f;
}

Player::~Player()
{
	if(vaisseau_) {
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(vaisseau_);
	}
}

void Player::assignerTouches(int boutonAccelerer, int boutonVirage180, int boutonGauche, int boutonDroite, int boutonTirer)
{
	controller_->assignerTouches(boutonAccelerer, boutonVirage180, boutonGauche, boutonDroite, boutonTirer);
}

void Player::touchesParDefaut()
{
	switch(id_)
	{
	case 1:
		// Touches par défaut (W, S, A, D, Space)
		this->assignerTouches(87, 83, 65, 68, 32);
		break;
	case 2:
		// Touches par défaut (8, 5, 4, 6, 0)
		this->assignerTouches(104, 101, 100, 102, 96);
		break;
	}
}

void Player::update(float temps)
{
	// Avancer le temps
	tempsDernierTir_ += temps;

	controller_->update(temps);

	if (controller_->getCommand(ACCELERER))
	{
		vaisseau_->setAcceleration(120);
	}
	else
	{
		vaisseau_->setAcceleration(0);
	}

	if (controller_->getCommand(DEMITOUR))
	{
		vaisseau_->effectuerDemiTour();
	}

	const float vitesseRotation = 270;
	if (controller_->getCommand(DROITE) && !controller_->getCommand(GAUCHE))
	{
		vaisseau_->setVitesseRotation(-vitesseRotation);
	}
	else if (controller_->getCommand(GAUCHE) && !controller_->getCommand(DROITE))
	{
		vaisseau_->setVitesseRotation(vitesseRotation);
	}
	else
	{
		vaisseau_->setVitesseRotation(0);
	}

	if (controller_->getCommand(TIRER))
	{
		if (tempsDernierTir_ > 0.2)
		{
			// Si le temps est supérieur à notre rythme de tir (5 tir/secondes), on tire
			vaisseau_->tirer();

			// Réinitialiser le compteur depuis le dernier tir
			tempsDernierTir_ = 0;
		}
	}
}

void Player::keyPressed(int keyCode)
{	
	controller_->keyPressed(keyCode);
}

void Player::keyReleased(int keyCode)
{
	controller_->keyReleased(keyCode);
}

PlayerActionState* Player::getPlayerActionState()
{
	return controller_->getActionState();
}


NoeudVaisseau* Player::getVaisseau()
{
	return vaisseau_;
}