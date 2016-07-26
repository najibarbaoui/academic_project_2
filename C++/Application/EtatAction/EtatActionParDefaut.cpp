#include "EtatActionParDefaut.h"

#include "Vue.h"

EtatActionParDefaut::EtatActionParDefaut()
{
	this->id_ = -1;
	this->utiliseRectangleElastique_ = false;
}

void EtatActionParDefaut::Activer()
{
}

void EtatActionParDefaut::Desactiver()
{
}

void EtatActionParDefaut::mouseMoved(int x, int y, bool ctrlPressed, bool altPressed)
{
}

void EtatActionParDefaut::mousePressed(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
}

void EtatActionParDefaut::mouseClicked(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
}

void EtatActionParDefaut::mouseDragged(int x, int y, int dx, int dy, bool ctrlPressed, bool altPressed)
{
}

void EtatActionParDefaut::mouseReleased(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
}

void EtatActionParDefaut::buttonPressed(string action)
{
}
