//////////////////////////////////////////////////////////////////////////////
/// @file EtatActionRectangleElastique.cpp
/// @author Olivier Cotte
/// @date 2014-02-06
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////


#include "EtatActionRectangleElastique.h"


///////////////////////////////////////////////////////////////////////////////
EtatActionRectangleElastique::EtatActionRectangleElastique() 
{
	this->id_ = RECTANGLE_ELASTIQUE;
}


///////////////////////////////////////////////////////////////////////////////
void EtatActionRectangleElastique::mousePressed(int pointAncrageX, int pointAncrageY, int button, bool ctrlPressed)
{
	Vecteur3 pointAncrage3;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(pointAncrageX, pointAncrageY, pointAncrage3);
	Vecteur2i pointAncrage2(pointAncrage3[0], pointAncrage3[1]);
	aidegl::initialiserRectangleElastique(pointAncrage2);

	m_iLastX = m_iAncrageX = pointAncrageX;
	m_iLastY = m_iAncrageY = pointAncrageY;
}


///////////////////////////////////////////////////////////////////////////////
void EtatActionRectangleElastique::mouseReleased(int pointFinalX, int pointFinalY, int button, bool ctrlPressed)
{
	Vecteur3 pointAncrage3, pointFinal3;

	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(m_iAncrageX, m_iAncrageY, pointAncrage3);
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(pointFinalX, pointFinalY, pointFinal3);

	Vecteur2i pointAncrage2(pointAncrage3[0], pointAncrage3[1]);
	Vecteur2i pointFinal2(pointFinal3[0], pointFinal3[1]);

	aidegl::terminerRectangleElastique(pointAncrage2, pointFinal2);
}


///////////////////////////////////////////////////////////////////////////////
void EtatActionRectangleElastique::mouseDragged(int pointApresX, int pointApresY, int dx, int dy, bool ctrlPressed)
{
	Vecteur3 pointAncrage3, pointAvant3, pointFinal3;

	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(m_iAncrageX, m_iAncrageY, pointAncrage3);
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(m_iLastX, m_iLastY, pointAvant3);
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(pointApresX, pointApresY, pointFinal3);

	Vecteur2i pointAncrage2(pointAncrage3[0], pointAncrage3[1]);
	Vecteur2i pointAvant2(pointAvant3[0], pointAvant3[1]);
	Vecteur2i pointFinal2(pointFinal3[0], pointFinal3[1]);

	aidegl::mettreAJourRectangleElastique(pointAncrage2, pointAvant2, pointFinal2);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////