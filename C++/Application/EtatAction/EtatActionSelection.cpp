#include "EtatActionSelection.h"

#include "Vue.h"

EtatActionSelection::EtatActionSelection()
{
	this->id_ = 0;
	this->utiliseRectangleElastique_ = true;
}

void EtatActionSelection::Activer()
{
}

void EtatActionSelection::Desactiver()
{
}

void EtatActionSelection::mouseMoved(int x, int y, bool ctrlPressed, bool altPressed)
{
}

void EtatActionSelection::mousePressed(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
	ctrlPressed_ = ctrlPressed;
	deplacementX = 0;
	deplacementY = 0;
}

void EtatActionSelection::mouseClicked(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
	Vecteur3 position;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, position);

	FacadeModele::obtenirInstance()->selectionObjet(position, position, ctrlPressed);
}

void EtatActionSelection::mouseDragged(int x, int y, int dx, int dy, bool ctrlPressed, bool altPressed)
{
	deplacementX = dx;
	deplacementY = dy;
}

void EtatActionSelection::mouseReleased(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
	// Convertir les coordonnées
	Vecteur3 anciennePosition, nouvellePosition;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x + deplacementX, y + deplacementY, anciennePosition);
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, nouvellePosition);

	// Trouver minXY et maxXY
	Vecteur3 minXY, maxXY;
	minXY[0] = min(anciennePosition[0], nouvellePosition[0]);
	minXY[1] = min(anciennePosition[1], nouvellePosition[1]);
	maxXY[0] = max(anciennePosition[0], nouvellePosition[0]);
	maxXY[1] = max(anciennePosition[1], nouvellePosition[1]);

	// Appliquer la sélection
	FacadeModele::obtenirInstance()->selectionObjet(minXY, maxXY, ctrlPressed_);
}

void EtatActionSelection::buttonPressed(string action)
{
}