#include "EtatModeleModeTest.h"

#include "EtatAction\EtatActionModeTest.h"
#include "GestionnaireJeu.h"
#include "FacadeModele.h"
#include "Vue\Vue.h"

EtatModeleModeTest::EtatModeleModeTest()
{
	this->etatId_ = ETATMODETEST;
}
	
void EtatModeleModeTest::mouseMoved(int x, int y, bool ctrlPressed, bool altPressed)
{
}
	
void EtatModeleModeTest::mousePressed(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
	button_ = button;
	
	if (button_ == BOUTONDROIT)
	{
		lastDragX = x;
		lastDragY = y;
	}
}
	
void EtatModeleModeTest::mouseClicked(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
}
	
void EtatModeleModeTest::mouseDragged(int x, int y, int dx, int dy, bool ctrlPressed, bool altPressed)
{
	if (button_ == BOUTONDROIT)
	{
		FacadeModele::obtenirInstance()->obtenirVue()->deplacerCamera(x, y, lastDragX, lastDragY);

		lastDragX = x;
		lastDragY = y;
	}
}
	
void EtatModeleModeTest::mouseReleased(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
}

void EtatModeleModeTest::buttonPressed(string action)
{
	if (action == "start")
	{
		GestionnaireJeu::obtenirInstance()->InitialiserJeu(true);
	}
}

