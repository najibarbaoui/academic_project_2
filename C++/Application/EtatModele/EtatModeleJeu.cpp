#include "EtatModeleJeu.h"

#include "GestionnaireJeu.h"
#include "FacadeModele.h"
#include "Vue\Vue.h"

EtatModeleJeu::EtatModeleJeu()
{
	this->etatId_ = ETATJEU;
}
	
void EtatModeleJeu::mouseMoved(int x, int y, bool ctrlPressed, bool altPressed)
{
}
	
void EtatModeleJeu::mousePressed(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
	button_ = button;
	
	if (button_ == BOUTONDROIT)
	{
		lastDragX = x;
		lastDragY = y;
	}
}
	
void EtatModeleJeu::mouseClicked(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
}
	
void EtatModeleJeu::mouseDragged(int x, int y, int dx, int dy, bool ctrlPressed, bool altPressed)
{
	if (button_ == BOUTONDROIT)
	{
		FacadeModele::obtenirInstance()->obtenirVue()->deplacerCamera(x, y, lastDragX, lastDragY);

		lastDragX = x;
		lastDragY = y;
	}
}
	
void EtatModeleJeu::mouseReleased(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
}

void EtatModeleJeu::buttonPressed(string action)
{	
	if (action == "start")
	{
		GestionnaireJeu::obtenirInstance()->InitialiserJeu(false);
	}
}