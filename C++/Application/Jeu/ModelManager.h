//////////////////////////////////////////////////////////////////////////////
/// @file ModelManager.h
/// @author Najib Arbaoui
/// @date 2014-03-17
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef __APPLICATION_JEU_MODELMANAGER_H__
#define __APPLICATION_JEU_MODELMANAGER_H__

#include "Singleton.h"

#include "Modele3D.h"

class ModelManager : public Singleton<ModelManager>
{
	SINGLETON_DECLARATION_CLASSE_SANS_CONSTRUCTEUR(ModelManager);

public:
	ModelManager();
	void loadModels();
	void unloadModels();

	Modele3D* getModel(const std::string& nom);
	GLuint getDisplayList(const std::string& nom);

private:
	map<string, int> modelsMap;

	Modele3D** models_;
	GLuint* lists_;

	void createDisplayLists();
	void deleteDisplayLists();
};

#endif // __APPLICATION_JEU_MODELMANAGER_H__

//////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////