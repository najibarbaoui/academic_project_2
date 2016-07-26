//#include "stdafx.h"
#include "AfficherTexte.h"
#include "AideGl.h"

// Source : http://glasnost.itcarlow.ie/~powerk/technology/opengl/displaylistsandarrays/fonts.htm
// tmp_opengl.cpp : Defines the <span id="w1x42nh0em_3" class="w1x42nh0em">entry point</span> for the application.
//
// ---------------------------------------------------------------
// Draw 3d text using wglUuseFontoutlines
// ---------------------------------------------------------------
//
// -------------------N.B.------------
// You must tell your linker to link to the openGl libraries:
// ++++++++++++++++
// Visual C++
// ++++++++++++++++
// In Visual C++ go to Project, Settings, and then click on the LINK tab.
// Under "Object/Library Modules" at the beginning of the line (before kernel32.lib) add OpenGL32.lib GLu32.lib and GLaux.lib.
// Once you've done this click  OK.
//
// pre-complied header for Visual C++, comment this out for other compilers

//
// ++++++++++++++++
// Dev-C++
// ++++++++++++++++
// In DevC++ select Project_Menu -> Project_options -> Parameters_Tab, type:
// -lopengl32 -lglu32 -lglaux
// in the "linker Box"
//
// Other Compilers will have diferent methods for specifing the link files
 
 
 
//////////////////////////////////////////////////////////////////////////////
//INCLUDES
//////////////////////////////////////////////////////////////////////////////
 
#include <windows.h>  
#include <gl/gl.h> //Standard OpenGL Header
#include <gl/glu.h> //OpenGL utilities



////////////////////////////////////////////////////////////////////////
///
/// @fn AfficherTexte::AfficherTexte()
///
/// Constructeur
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
AfficherTexte::AfficherTexte()
{
	g_hdc = FacadeModele::obtenirInstance()->obtenirContexte();
	//g_hrc = FacadeModele::obtenirInstance()->obtenirContexteHglrc();
	//hWndMain = FacadeModele::obtenirInstance()->obtenirContexteHwnd();
	font_list_base_3d=1000;
	font_list_base_2d=2000;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn AfficherTexte::~AfficherTexte()
///
/// Le destructeur 
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
AfficherTexte::~AfficherTexte()
{
	
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool AfficherTexte::Prog_Init(int tailleFont)const
///
/// Elle permet d initialiser la taille du texte
///	@param tailleFont : la taille de la police
/// @return bool 
///
////////////////////////////////////////////////////////////////////////
 
bool AfficherTexte::Prog_Init(int tailleFont)const
{
    ////////////////////////////////////
    //your initialization code goes here
    ////////////////////////////////////
 
    glEnable(GL_DEPTH_TEST); // check for depth
     
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);	
     
    glEnable(GL_LIGHTING); // switch on lighting
    glEnable(GL_LIGHT0); // switch on light0
 
     
    GLfloat light_color[]={1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[]={10.0, 10.0, 10.0,0.0};
 
 
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color); // set color of diffuse component
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_color); // set color of specular component
 
 
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);   // set position
 
 
    glEnable(GL_NORMALIZE);
 
 
 
     LPCWSTR pszFaceName;
	 pszFaceName = L"Times New Roman";
    // create and select the font we want to use
    HFONT font = CreateFont(tailleFont, 0, 0, 0,
                           FW_EXTRABOLD, FALSE, FALSE, FALSE,
                           1, 0,
                            0,0,0,L"Clarendon"); // can only use true type fonts
 
    SelectObject(g_hdc, font);
 
 
    wglUseFontOutlines(g_hdc,0,255,font_list_base_3d, 0.0f, 0.1f,WGL_FONT_LINES,NULL);
        // generate a display list for every character (up to ascii 127)
        // generate as accurately as possible (0.0f deviation)
        // extrude by 0.1 units
        // generate polygons (not lines) to render the fonts
 
    /*DeleteObject(font);
 
    font = CreateFont(0, 0, 0, 0,
                           FW_NORMAL, FALSE, FALSE, FALSE,
                           ANSI_CHARSET, 0,
                            0, 0,0,"Courier New"); // can only use true type fonts
 
 
*/
    wglUseFontBitmaps(g_hdc,0,255,font_list_base_2d);
     
 
    return(true);//return success
}
 

////////////////////////////////////////////////////////////////////////
///
/// @fn void AfficherTexte::Prog_Loop(double posX, double posY, int tailleFont, string timer)const
/// Elle affiche le texte 
/// 
/// @param posX : la position suivant l axe des X
/// @param posY : la position suivant l axe des Y
///	@param tailleFont : la taille de la police
/// @param texte : le texte à afficher
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
 
void AfficherTexte::Prog_Loop(float posX, float posY,bool minuterie, string texte)const
{
	Vecteur3 minXY, maxXY;
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirZoneJeu()->obtenirBoiteEnglobante(minXY,maxXY);
   float decalage = -10.0;
	//glColor3f(1.0,0.1,0.0); ne faut pas toucher
	if(!minuterie){
    glPushMatrix(); // save transforms
	glRasterPos3f(posX,posY,5.0);
    glListBase(font_list_base_2d); //start of our font lists
	glCallLists(strlen(texte.c_str()), GL_UNSIGNED_BYTE, texte.c_str());
	 glPopMatrix(); // restore transforms
	}else{
     glPushMatrix(); // save transforms
	 glTranslatef(decalage,maxXY[1]+5,0.0);
	 glScalef(12.0,12.0,12.0);
	 glListBase(font_list_base_3d);
	 glCallLists(strlen(texte.c_str()), GL_UNSIGNED_BYTE, texte.c_str());
	 glPopMatrix(); // restore transforms
	}
	//glCallLists(strlen(texte.c_str()), GL_UNSIGNED_BYTE, texte.c_str());
     
    //glPopMatrix(); // restore transforms
 
    //SwapBuffers(g_hdc); // bring back buffer foreground
}
 
 
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////