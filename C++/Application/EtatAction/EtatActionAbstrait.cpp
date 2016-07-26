#include "EtatActionAbstrait.h"

#include "Vue.h"
#include <iostream>

EtatActionAbstrait::EtatActionAbstrait()
{
	compteClique_ = 0;
}

int EtatActionAbstrait::getEtatActionId()
{
	return id_;
}

bool EtatActionAbstrait::getUtiliseRectangleElastique()
{
	return utiliseRectangleElastique_;
}

int EtatActionAbstrait::getCompteClique()
{
	return compteClique_;
}