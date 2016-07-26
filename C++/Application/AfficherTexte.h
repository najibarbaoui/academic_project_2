///////////////////////////////////////////////////////////////////////////////
/// @file AfficherTexte.h
/// @author Najib Arbaoui
/// @date 08 - 04 - 2014
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_AFFICHERTEXTE_H__
#define __ARBRE_NOEUDS_AFFICHERTEXTE_H__


#include "FacadeModele.h"
#include "..\Application\Jeu\Partie.h"
#include <string>



class AfficherTexte 
{
public:
	/// constructeur par d�faut
	AfficherTexte();
	/// destructeur
	~AfficherTexte();
	void Prog_Loop(float posX, float posY, bool minuterie, string texte)const;
	bool Prog_Init(int tailleFont)const;
private:
	HWND hWndMain;
	HDC g_hdc;
	HGLRC g_hrc; 
	int font_list_base_3d;
	int font_list_base_2d;
	
};
#endif // __ARBRE_NOEUDS_AFFICHERTEXTE_H__
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////