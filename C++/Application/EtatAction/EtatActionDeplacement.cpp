#include "EtatActionDeplacement.h"

#include "Vue.h"

EtatActionDeplacement::EtatActionDeplacement()
{
	this->id_ = 1;
	this->utiliseRectangleElastique_ = false;
}

void EtatActionDeplacement::Activer()
{
}

void EtatActionDeplacement::Desactiver()
{
}

void EtatActionDeplacement::mouseMoved(int x, int y, bool ctrlPressed, bool altPressed)
{
}

void EtatActionDeplacement::mousePressed(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
	lastDragX = x;
	lastDragY = y;
}

void EtatActionDeplacement::mouseClicked(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
}

void EtatActionDeplacement::mouseDragged(int x, int y, int dx, int dy, bool ctrlPressed, bool altPressed)
{
	Vecteur3 anciennePosition, nouvellePosition;
	
	// Convertir les positions relatives
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, nouvellePosition);
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(lastDragX, lastDragY, anciennePosition);

	// Calculer le déplacement
	Vecteur3 deplacement = nouvellePosition - anciennePosition;
	
	// Déplacer l'objet
	FacadeModele::obtenirInstance()->deplacerObjet(deplacement);

	lastDragX = x;
	lastDragY = y;
}

void EtatActionDeplacement::mouseReleased(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
}

void EtatActionDeplacement::buttonPressed(string action)
{
}