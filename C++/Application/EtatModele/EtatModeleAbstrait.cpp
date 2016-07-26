#include "EtatModeleAbstrait.h"

int EtatModeleAbstrait::getEtatId()
{
	return etatId_;
}
	
bool EtatModeleAbstrait::DoWeDrawScene() const
{ 
	return m_bDrawScene;
}