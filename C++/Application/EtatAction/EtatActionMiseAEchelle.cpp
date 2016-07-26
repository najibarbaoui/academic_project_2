#include "EtatActionMiseAEchelle.h"

#include "Vue.h"

EtatActionMiseAEchelle::EtatActionMiseAEchelle()
{
	this->id_ = 3;
	this->utiliseRectangleElastique_ = false;
}

void EtatActionMiseAEchelle::Activer()
{
}

void EtatActionMiseAEchelle::Desactiver()
{
}

void EtatActionMiseAEchelle::mouseMoved(int x, int y, bool ctrlPressed, bool altPressed)
{
}

void EtatActionMiseAEchelle::mousePressed(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
	lastScale = 1.0f;
}

void EtatActionMiseAEchelle::mouseClicked(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
}

void EtatActionMiseAEchelle::mouseDragged(int x, int y, int dx, int dy, bool ctrlPressed, bool altPressed)
{
	// Convertir les positions relatives
	Vecteur3 anciennePosition, nouvellePosition;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, nouvellePosition);
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x - dx, y - dy, anciennePosition);

	// Calculer le d�placement
	double deplacement = nouvellePosition[1] - anciennePosition[1];
	// On calcule un pourcentage d'agrandissement � l'aide du d�placement
	// On divise par 40 pour qu'un d�plassement de 1 donne un facteur de 5% (100/20)
	float percentScale = 1 + (float)abs(deplacement)/20;

	float scale;
	// Si le d�placement de la souris est n�gatif, on inverse le facteur d'agrandissement
	if (dy < 0)
	{
		scale = 1/percentScale;
	}
	// Sinon, on l'utilise comme tel
	else
	{
		scale = percentScale;
	}
	
	// On applique le nouveau facteur d'agrandissement
	FacadeModele::obtenirInstance()->miseAEchelle(lastScale, scale);

	// Enregistrer la derni�re �chelle
	lastScale = scale;
}

void EtatActionMiseAEchelle::mouseReleased(int x, int y, int button, bool ctrlPressed, bool altPressed)
{
}

void EtatActionMiseAEchelle::buttonPressed(string action)
{
}