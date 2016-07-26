#include "EtatActionRotation.h"

#include "Vue.h"

EtatActionRotation::EtatActionRotation()
{
	this->id_ = 2;
	this->utiliseRectangleElastique_ = false;
}

void EtatActionRotation::Activer()
{
}

void EtatActionRotation::Desactiver()
{
}

void EtatActionRotation::mouseMoved(int x, int y, bool ctrlPressed, bool altPressed)
{
}

void EtatActionRotation::mousePressed(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
	lastDragX = x;
	lastDragY = y;

	// Calculer le centre de rotation
	Vecteur3 minXY, maxXY;
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->trouverBornesSelection(minXY, maxXY);

	centreRotation[0] = (maxXY[0] + minXY[0])/2;
	centreRotation[1] = (maxXY[1] + minXY[1])/2;
}

void EtatActionRotation::mouseClicked(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
}

void EtatActionRotation::mouseDragged(int x, int y, int dx, int dy, bool ctrlPressed, bool altPressed)
{
	// Convertir les positions relatives
	Vecteur3 anciennePosition, nouvellePosition;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(lastDragX, lastDragY, anciennePosition);
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, nouvellePosition);

	// Calculer le déplacement
	double angle = anciennePosition[1] - nouvellePosition[1];

	// Appliquer la rotation
	FacadeModele::obtenirInstance()->faireRotation(angle, centreRotation);

	lastDragX = x;
	lastDragY = y;
}

void EtatActionRotation::mouseReleased(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
}

void EtatActionRotation::buttonPressed(string action)
{
}