////////////////////////////////////////////////////////////////////////////////////
/// @file ModelManager.cpp
/// @author Najib Arbaoui
/// @date 2014-03-17
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "ModelManager.h"

#include <cassert>

#include "ArbreRenduINF2990.h"

SINGLETON_DECLARATION_CPP(ModelManager);

ModelManager::ModelManager()
{
	modelsMap.insert(pair<string, int>(ArbreRenduINF2990::NOM_VAISSEAU, 0));
	modelsMap.insert(pair<string, int>(ArbreRenduINF2990::NOM_PROJECTILE, 1));
	modelsMap.insert(pair<string, int>(ArbreRenduINF2990::NOM_PORTAIL, 2));
	modelsMap.insert(pair<string, int>(ArbreRenduINF2990::NOM_BONUSACCELERATEUR, 3));
	modelsMap.insert(pair<string, int>(ArbreRenduINF2990::NOM_STATIONSPATIALE, 4));
	modelsMap.insert(pair<string, int>(ArbreRenduINF2990::NOM_CURSEURCROIX, 5));
	modelsMap.insert(pair<string, int>(ArbreRenduINF2990::NOM_ASTEROIDE, 6));
	modelsMap.insert(pair<string, int>(ArbreRenduINF2990::NOM_POSITIONDEPART, 7));
	modelsMap.insert(pair<string, int>(ArbreRenduINF2990::NOM_ANIMATION, 8));
}

void ModelManager::loadModels()
{
	string modelFileName[] =
	{
		"media/vaisseau.obj",
		"media/projectile.obj",
		"media/Beigne.obj",
		"media/Pyramid.obj",
		"media/station.obj",
		"media/croix.obj",
		"media/asteroide.obj",
		"media/positiondepart.obj",
		"media/animation.obj"
	};

	models_ = new Modele3D*[modelsMap.size()];
	for (int i=0; i<modelsMap.size(); i++)
	{
		models_[i] = new Modele3D();
		models_[i]->charger(modelFileName[i]);
	}

	this->createDisplayLists();
}

void ModelManager::unloadModels()
{
	this->deleteDisplayLists();

	models_ = new Modele3D*[modelsMap.size()];
	for (int i=0; i<modelsMap.size(); i++)
	{
		delete models_[i];
	}

	delete models_;
	models_ = 0;
}

Modele3D* ModelManager::getModel(const std::string& nom)
{
	assert(models_ != 0);
	return models_[modelsMap[nom]];
}

GLuint ModelManager::getDisplayList(const std::string& nom)
{
	assert(lists_ != 0);
	return lists_[modelsMap[nom]];
}

void ModelManager::createDisplayLists()
{
	lists_ = new GLuint[modelsMap.size()];
	for (int i=0; i<modelsMap.size(); i++)
	{
		lists_[i] = glGenLists(1);
		glNewList(lists_[i], GL_COMPILE);
			models_[i]->dessiner();		
		glEndList();
	}
}

void ModelManager::deleteDisplayLists()
{
	for (int i=0; i<modelsMap.size(); i++)
	{
		glDeleteLists(lists_[i], 1);
	}
	lists_ = 0;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////