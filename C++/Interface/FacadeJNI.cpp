///////////////////////////////////////////////////////////////////////////////
/// @file FacadeJNI.cpp
/// @author Martin Bisson
/// @date 2007-08-14
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <GL/gl.h>
#include <iostream>

#include "jawt_md.h"
#include "JAWT_Info.h"
#include "FreeImage.h"

#include "UtilitaireINF2990.h"

#include "FacadeJNI.h"
#include "Vecteur.h"
#include "FacadeModele.h"
#include "GestionnaireJeu.h"
#include "Vue.h"
#include "AideGL.h"
#include "ArbreRenduINF2990.h"
#include "CompteurAffichage.h"
#include "ProjectionOrtho.h"
#include "EtatModele\EtatModeleAbstrait.h"
#include "EtatModele\EtatModeleEditeur.h"

#include "BancTests.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1initialiserOpenGL(JNIEnv* env, jclass, jobject canvas)
///
/// Cette fonction initialise un contexte OpenGL dans la fen�tre
/// identifi�e par le canvas AWT pass� en param�tre.  Cette fonction doit
/// �tre la premi�re � �tre appel�e, car la cr�ation de l'objet du mod�le
/// C++ s'attend � avoir un contexte OpenGL valide.
///
/// @param[in] env    : L'environnement Java.
/// @param[in] canvas : Le canvas dans lequel cr�er le contexte OpenGL.
///
/// @return Aucune.
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1initialiserOpenGL
  (JNIEnv* env, jclass, jobject canvas)
{
   // Obtenir la poign�e ("handle") vers la fen�tre.
   JAWT_Info info(env, canvas);
   HWND hWnd = (HWND)info.getHWND();
	
   // On pourrait lancer une exception � la place...
   if(hWnd == 0)
      return;

	FacadeModele::obtenirInstance()->initialiserOpenGL(hWnd);
}




////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1libererOpenGL(JNIEnv* env, jclass, jobject canvas)
///
/// Cette fonction lib�re le contexte OpenGL dans la fen�tre identifi�e
/// par le canvas AWT pass� en param�tre.  Cette fonction doit �tre la
/// derni�re � �tre appel�e, car elle lib�re �galement l'objet du mod�le
/// C++.
///
/// @param[in] env    : L'environnement Java.
/// @param[in] canvas : Le canvas dans lequel cr�er le contexte OpenGL.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1libererOpenGL
  (JNIEnv* env, jclass, jobject canvas)
{
   // Ce code v�rouille le canvas et ne doit donc pas �tre enlev�, m�me s'il
   // semble inutile � premi�re vue.
   JAWT_Info info(env, canvas);
   HWND hWnd = (HWND)info.getHWND();

   // On pourrait lancer une exception � la place...
   if(hWnd == 0)
      return;

   FacadeModele::obtenirInstance()->libererOpenGL();
	
	
   // D�sinitialisation de la fa�ade.  Le fait de le faire apr�s la
   // d�sinitialisation du contexte OpenGL aura pour cons�quence que la
   // lib�ration des listes d'affichages, par cpp_FacadeCpp, sera faite une fois que
   // le contexte n'existera plus, et sera donc sans effet.
   FacadeModele::libererInstance();
}




////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1dessinerOpenGL(JNIEnv* env, jclass, jobject canvas)
///
/// Cette fonction affiche la sc�ne dans la fen�tre identifi�e par le
/// canvas AWT pass� en param�tre.
///
/// @param[in] env    : L'environnement Java.
/// @param[in] canvas : Le canvas dans lequel cr�er le contexte OpenGL.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1dessinerOpenGL
  (JNIEnv* env, jclass, jobject canvas)
{
	bool bEtatEditeur = FacadeModele::obtenirInstance()->obtenirEtat()->getEtatId() == ETATEDITEUR;
	bool bRectangleElastique = FacadeModele::obtenirInstance()->obtenirEtat()->DoWeDrawScene() == false;

	bool bEtatModeTest = FacadeModele::obtenirInstance()->obtenirEtat()->getEtatId() == ETATMODETEST;

	bool bEtatModeJeu = FacadeModele::obtenirInstance()->obtenirEtat()->getEtatId() == ETATJEU;

	if(!(bEtatEditeur && bRectangleElastique) || bEtatModeTest || bEtatModeJeu) {
		// Ce code v�rouille le canvas et ne doit donc pas �tre enlev�, m�me s'il
		// semble inutile � premi�re vue.
		JAWT_Info info(env, canvas);
		HWND hWnd = (HWND)info.getHWND();

		if(hWnd == 0)
			return;

		// Affiche la sc�ne.
		FacadeModele::obtenirInstance()->afficher();
		// Temporaire: pour d�tecter les erreurs OpenGL
		aidegl::verifierErreurOpenGL();
	}
}




////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1redimensionnerFenetre(JNIEnv*, jclass, jint largeur, jint hauteur)
///
/// Cette fonction doit �tre appel�e lorsque la fen�tre est
/// redimensionn�e afin d'ajuster les param�tres de la machine � �tats
/// d'OpenGL pour correspondre aux nouvelles dimensions de la fen�tre.
///
/// @param[in] largeur : La nouvelle largeur de la fen�tre.
/// @param[in] hauteur : La nouvelle hauteur de la fen�tre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1redimensionnerFenetre
  (JNIEnv*, jclass, jint largeur, jint hauteur)
{
   FacadeModele::obtenirInstance()->obtenirVue()->redimensionnerFenetre(
      Vecteur2i(0,0),
      Vecteur2i(largeur, hauteur)
      );

   FacadeModele::obtenirInstance()->rafraichirFenetre();
}




////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1animer(JNIEnv*, jclass, jfloat temps)
///
/// Cette fonction effectue les diff�rents calculs d'animations
/// n�cessaires pour le mode jeu, tel que les diff�rents calculs de
/// physique du jeu.
///
/// @param[in] temps : Intervalle de temps sur lequel effectuer le calcul.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1animer
  (JNIEnv*, jclass, jfloat temps)
{
	// Si mode jeu, animer jeu
	int etatId = FacadeModele::obtenirInstance()->obtenirEtat()->getEtatId();
	if (etatId = ETATMODETEST || etatId == ETATJEU)
	{
		if(!GestionnaireJeu::obtenirInstance()->obtenirEtatPause())
		{
			GestionnaireJeu::obtenirInstance()->update(temps);
			FacadeModele::obtenirInstance()->animer(temps);
		}
	}
}



////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1zoomIn(JNIEnv*, jclass)
///
/// Cette fonction applique un zoom avant sur le pr�sent volume de vision.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1zoomIn
  (JNIEnv*, jclass)
{
   FacadeModele::obtenirInstance()->obtenirVue()->zoomerIn();
   FacadeModele::obtenirInstance()->rafraichirFenetre();
}




////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1zoomOut(JNIEnv*, jclass)
///
/// Cette fonction applique un zoom arri�re sur le pr�sent volume de vision.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1zoomOut
  (JNIEnv*, jclass)
{
   FacadeModele::obtenirInstance()->obtenirVue()->zoomerOut();
   FacadeModele::obtenirInstance()->rafraichirFenetre();
}




////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_obtenirAffichagesParSeconde(JNIEnv*, jclass)
///
/// Cette fonction permet d'obtenir le nombre d'affichages par seconde.
///
/// @return Le nombre d'affichage par seconde.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_obtenirAffichagesParSeconde
  (JNIEnv*, jclass)
{
   return utilitaire::CompteurAffichage::obtenirInstance()->obtenirAffichagesSeconde();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_obtenirEtatActionId(JNIEnv*, jclass)
///
/// Cette fonction permet d'obtenir l'identifiant de l'�tat action pour l'�tat menu.
///
/// @return L'identifiant de l'�tat action.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1obtenirEtatActionId
  (JNIEnv *, jclass)
{
	// Cette fonction sera toujours appel�e en mode EtatModeleEditeur
	return ((EtatModeleEditeur*)FacadeModele::obtenirInstance()->obtenirEtat())->getEtatActionId();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1executerTests(JNIEnv*, jclass)
///
/// Cette fonction permet d'ex�cuter l'ensemble des tests unitaires
///
/// @return 0 si tous les tests ont r�ussi, 1 si au moins un test a �chou�
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1executerTests
  (JNIEnv *, jclass)
{
   bool reussite = BancTests::obtenirInstance()->executer();

   // Visual Studio interpr�te le code de retour 0 comme une r�ussite et le code
	// de retour 1 comme un �chec. Nous transmettons le code de retour � Java
	// qui le transmet directement comme code de sortie du programme.
   return reussite ? 0 : 1;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1mouseMoved(JNIEnv *, jclass, jint, jint, jboolean, jboolean)
///
/// Cette fonction est le handler de l'�venement "Mouse moved". Ce n'est pas un �venement qui
/// ex�cute une action, mais certaines actions ont besoin de savoir si la souris a boug�e
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1mouseMoved
  (JNIEnv *, jclass, jint x, jint y, jboolean ctrlPressed, jboolean altPressed)
{
	FacadeModele::obtenirInstance()->obtenirEtat()->mouseMoved(x, y, ctrlPressed != 0, altPressed != 0);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1mouseClicked(JNIEnv *, jclass, jint, jint, jint, jboolean)
///
/// Cette fonction est le handler de l'�venement "Mouse pressed". Ce n'est pas un �venement qui
/// ex�cute une action, mais certaines actions ont besoin d'initialiser des valeurs au d�but du click
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1mousePressed
  (JNIEnv *, jclass, jint x, jint y, jint button, jboolean ctrlPressed, jboolean altPressed)
{
	FacadeModele::obtenirInstance()->obtenirEtat()->mousePressed(x, y, button, ctrlPressed != 0, altPressed != 0);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1mouseClicked(JNIEnv *, jclass, jint, jint, jint, jboolean)
///
/// Cette fonction est le handler de l'�venement "Mouse clicked".
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1mouseClicked
  (JNIEnv *, jclass, jint x, jint y, jint button, jboolean ctrlPressed, jboolean altPressed)
{
	FacadeModele::obtenirInstance()->obtenirEtat()->mouseClicked(x, y, button, ctrlPressed != 0, altPressed != 0);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1mouseDragged(JNIEnv *, jclass, jint, jint, jint, jint)
///
/// Cette fonction est le handler de l'�venement "Mouse dragged".
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1mouseDragged
  (JNIEnv *, jclass, jint x, jint y, jint dx, jint dy, jboolean ctrlPressed, jboolean altPressed)
{
	FacadeModele::obtenirInstance()->obtenirEtat()->mouseDragged(x, y, dx, dy, ctrlPressed != 0, altPressed != 0);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1mouseDragged(JNIEnv *, jclass, jint, jint, jint, jint)
///
/// Cette fonction est le handler de l'�venement "Mouse released". Ce n'est pas un �venement qui
/// ex�cute une action, mais certaines actions ont besoin de finaliser des valeurs � la fin du click
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1mouseReleased
  (JNIEnv *, jclass, jint x, jint y, jint button, jboolean ctrlPressed, jboolean altPressed)
{
	FacadeModele::obtenirInstance()->obtenirEtat()->mouseReleased(x, y, button, ctrlPressed != 0, altPressed != 0);
}

/*
 * Class:     ca_polymtl_inf2990_cpp_FacadeCpp
 * Method:    keyPressed
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_keyPressed
  (JNIEnv *, jclass, jint keyCode)
{
	GestionnaireJeu::obtenirInstance()->keyPressed(keyCode);
}

/*
 * Class:     ca_polymtl_inf2990_cpp_FacadeCpp
 * Method:    keyReleased
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_keyReleased
  (JNIEnv *, jclass, jint keyCode)
{
	GestionnaireJeu::obtenirInstance()->keyReleased(keyCode);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1buttonPressed(JNIEnv *, jclass, jstring)
///
/// Cette fonction est le handler de l'�venement "Button pressed".
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1buttonPressed
  (JNIEnv * env, jclass, jstring jaction)
{
	string action = utilitaire::obtenirChaineISO(env, jaction);

	FacadeModele::obtenirInstance()->obtenirEtat()->buttonPressed(action);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1obtenirEtat(JNIEnv *, jclass)
///
/// Cette fonction retourne l'�tat courant
///
/// @return L'identificateur de l'�tat courant.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT jint JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1obtenirEtat
  (JNIEnv *, jclass)
{
	return FacadeModele::obtenirInstance()->obtenirEtat()->getEtatId();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1changerEtat(JNIEnv *, jclass, jint)
///
/// Cette fonction modifie l'�tat courant
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1changerEtat
  (JNIEnv *, jclass, jint etatModele)
{
	FacadeModele::obtenirInstance()->ChangerEtat(etatModele);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT jboolean JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1ouvrirFichier(JNIEnv *, jclass, jstring)
///
/// Fonction qui ouvre le niveau dans le fichier sp�cifi�.
///
/// @return Vrai si l'ouverture est un succ�s, faux sinon.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT jboolean JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1ouvrirFichier
  (JNIEnv* env, jclass, jstring jFilePath)
{
	// Converti la chaine de caract�re java en chaine de caract�re c++
	string filePath = utilitaire::obtenirChaineISO(env, jFilePath);

	// Charge le fichier xml
	FacadeModele::obtenirInstance()->chargerXml(filePath);
	
	// Assigne le nom du fichier de sauvegarde
	FacadeModele::obtenirInstance()->assignerFichierSauvegarde(filePath);

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1sauvegarderFichier(JNIEnv *, jclass, jstring)
///
/// Fonction qui sauvegarde le niveau dans le fichier sp�cifi�.
///
/// @return Vrai si la sauvegarde s'est effectu� avec succ�s, faux sinon.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT jboolean JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1sauvegarderFichier
  (JNIEnv* env, jclass, jstring jFilePath)
{
	// Converti la chaine de caract�re java en chaine de caract�re c++
	string filePath = utilitaire::obtenirChaineISO(env, jFilePath);

	// Enregistre le fichier xml
	FacadeModele::obtenirInstance()->enregistrerXml(filePath);

	return true;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT jboolean JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1fichierSauvegardeEstDefini(JNIEnv *, jclass)
///
/// Fonction qui retourne si le fichier de sauvegarde est d�fini
///
/// @return Vrai si le fichier de sauvegarde est d�fini, faux sinon
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT jboolean JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1fichierSauvegardeEstDefini
  (JNIEnv *, jclass)
{
	return FacadeModele::obtenirInstance()->fichierSauvegardeEstDefini();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT jobject JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1obtenirNomFichierSauvegarde(JNIEnv *, jclass)
///
/// Fonction qui retourne le nom du fichier de sauvegarde
///
/// @return String Le nom du fichier de sauvegarde, s'il y a lieu
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT jstring JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1obtenirNomFichierSauvegarde
  (JNIEnv* env, jclass)
{
	jstring str = env->NewStringUTF(FacadeModele::obtenirInstance()->obtenirNomFichierSauvegarde().c_str());

	return str;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT jobject JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1obtenirSeulNoeudSelectionne(JNIEnv *, jclass)
///
/// Fonction qui retourne le seul noeud s�lectionn�.
///
/// @return Le noeud s�lectionn� s'il y en a un, null sinon
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT jobject JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1obtenirSeulNoeudSelectionne
  (JNIEnv* env, jclass)
{
	// Aller chercher le noeud
	NoeudAbstrait* noeudSelectionne = FacadeModele::obtenirInstance()->noeudSelectionUnique;
	if (noeudSelectionne != NULL)
	{
		// Obtenir les proprietes du noeud
		jstring type = env->NewStringUTF(noeudSelectionne->obtenirType().c_str());;
		jdouble positionX = noeudSelectionne->getPosition()[0];
		jdouble positionY = noeudSelectionne->getPosition()[1];
		jdouble rotation = noeudSelectionne->getAngleRotation();
		jdouble echelle = noeudSelectionne->getEchelle();
	
		jclass classe = env->FindClass("ca/polymtl/inf2990/modele/ProprietesNoeud"); 
	
		// La m�thode du constructeur est nomm� <init>
		jmethodID mid = env->GetMethodID(classe, "<init>", "(Ljava/lang/String;DDDD)V"); 

		// Appel du constructeur
		jobject newObj = env->NewObject(classe, mid, type, positionX, positionY, rotation, echelle);

		return newObj;
	}
	else
	{
		return NULL;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1modifierSeulNoeudSelectionne(JNIEnv *, jclass, jobject)
///
/// Fonction qui modifie le seul noeud s�lectionn�.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1modifierSeulNoeudSelectionne
  (JNIEnv* env, jclass, jobject proprietesNoeud)
{
	// Aller chercher le noeud
	NoeudAbstrait* noeudSelectionne = FacadeModele::obtenirInstance()->noeudSelectionUnique;

	if (noeudSelectionne != NULL)
	{
		// Chercher la classe de l'objet
		jclass classe = env->GetObjectClass(proprietesNoeud);

		// Chercher l'identificateur des m�thode de l'objet
		jmethodID getPositionXid = env->GetMethodID(classe, "getPositionX", "()D");
		jmethodID getPositionYid = env->GetMethodID(classe, "getPositionY", "()D");
		jmethodID getRotationid = env->GetMethodID(classe, "getRotation", "()D");
		jmethodID getEchelleid = env->GetMethodID(classe, "getEchelle", "()D");

		// Appeler la m�thode sur l'objet permettant d'obtenir les propri�t�s voulus du noeud
		jdouble positionX = env->CallDoubleMethod(proprietesNoeud, getPositionXid);
		jdouble positionY = env->CallDoubleMethod(proprietesNoeud, getPositionYid);
		jdouble rotation = env->CallDoubleMethod(proprietesNoeud, getRotationid);
		jdouble echelle = env->CallDoubleMethod(proprietesNoeud, getEchelleid);
		
		// Calcul du d�placement � faire
		double deplacementX = positionX - noeudSelectionne->obtenirPositionRelative()[0];
		double deplacementY = positionY - noeudSelectionne->obtenirPositionRelative()[1];
		FacadeModele::obtenirInstance()->deplacerObjet(Vecteur3(deplacementX, deplacementY, 0));

		// Calcul de la rotation � faire
		double deltaAngle = rotation - noeudSelectionne->getAngleRotation();

		// Centre de rotation est la position actuelle du noeud
		FacadeModele::obtenirInstance()->faireRotation(deltaAngle, noeudSelectionne->obtenirPositionRelative());

		// Calcul de la mise � �chelle � faire
		//double deltaEchelle = echelle/noeudSelectionne->getEchelle();
		FacadeModele::obtenirInstance()->miseAEchelle(static_cast<float>(noeudSelectionne->getEchelle()), static_cast<float>(echelle));
	}
	else
	{
		// Si on se rend ici, gros probl�me
		int zero = 0;
		int plante = 4/zero;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1move(JNIEnv *, jclass, jint)
///
/// Fonction qui d�place la cam�ra.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1move
  (JNIEnv *, jclass, jint direction)
{
	// Appliquer le d�placement
	FacadeModele::obtenirInstance()->obtenirVue()->move(direction);
}
///////////////////////////////////////////////////////////////////////////////
/*
 * Class:     ca_polymtl_inf2990_cpp_FacadeCpp
 * Method:    fctC_obtenirProprietesJeu
 * Signature: ()Lca/polymtl/inf2990/modele/ProprietesJeu;
 */
JNIEXPORT jobject JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1obtenirProprietesJeu
  (JNIEnv * env, jclass)
{
	// Obtenir les proprietes du noeud
	//FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->setNbstatsauv(9);
	
		jint victoire =FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getNbstatsauv(); 
		jint frequence =FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getAsterpsec();
		jint acceleration =FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getAccelbonus();
		jint difficulte= FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getDifficulte();
			
		jclass classe = env->FindClass("ca/polymtl/inf2990/modele/ProprietesJeu"); 
	
		// La m�thode du constructeur est nomm� <init>
		jmethodID mid = env->GetMethodID(classe, "<init>", "(IIII)V"); 

		// Appel du constructeur
		jobject newObj = env->NewObject(classe, mid, victoire,frequence,acceleration,difficulte);

		return newObj;
}

JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1modifierProprietesJeu
	(JNIEnv *env, jclass, jobject proprietejeu)
{
		// Chercher la classe de l'objet
		jclass classe = env->GetObjectClass(proprietejeu);

		// Chercher l'identificateur des m�thode de l'objet
		jmethodID getVictoire = env->GetMethodID(classe, "getVictoire", "()I");
		jmethodID getFrequence = env->GetMethodID(classe, "getFrequence", "()I");
		jmethodID getAcceleration = env->GetMethodID(classe, "getAcceleration", "()I");
		jmethodID getDifficulte = env->GetMethodID(classe, "getDifficulte", "()I");

		// Appeler la m�thode sur l'objet permettant d'obtenir les propri�t�s voulus du noeud
		jint victoire = env->CallIntMethod(proprietejeu, getVictoire);
		jint frequence = env->CallIntMethod(proprietejeu, getFrequence);
		jint acceleration = env->CallIntMethod(proprietejeu, getAcceleration);
		jint difficulte = env->CallIntMethod(proprietejeu, getDifficulte);
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->setNbstatsauv(victoire);
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->setAsterpsec(frequence);
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->setAccelbonus(acceleration);
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->setDifficulte(difficulte);
}



JNIEXPORT jboolean JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1getIsGagne
  (JNIEnv *, jclass)
{
	return GestionnaireJeu::obtenirInstance()->getIsGagne();
}

JNIEXPORT jboolean JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1isTermine
  (JNIEnv *, jclass)
{
	 if(GestionnaireJeu::obtenirInstance()->isTermine())
		 return true;
	 else
		 return false;
}
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1obtenirOptionDebogage
  (JNIEnv *, jclass, jboolean affichedebug, jboolean apparitionaster , jboolean changementjoueur, jboolean eclairage, jboolean cible, jboolean cadredepart, jboolean zonepassage, jboolean limiteattrport)
{
	ConfigJeu::obtenirInstance()->setAfficheDebug(affichedebug != 0);
	ConfigJeu::obtenirInstance()->setApparitionAsteroid(apparitionaster != 0);
	ConfigJeu::obtenirInstance()->setCadreDepart(cadredepart != 0);
	ConfigJeu::obtenirInstance()->setChangementJoueurVirtuel(changementjoueur != 0);
	ConfigJeu::obtenirInstance()->setCible(cible != 0);
	ConfigJeu::obtenirInstance()->setEclairage(eclairage != 0);
	ConfigJeu::obtenirInstance()->setLimiteAttractionPortails(limiteattrport != 0);
	ConfigJeu::obtenirInstance()->setZonePassage(zonepassage != 0);
}


JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1obtenirControles
  (JNIEnv *, jclass, jint avancer1, jint demi1, jint droite1, jint gauche1, jint tir1, jint avancer2, jint demi2, jint droite2, jint gauche2, jint tir2)
{
	ConfigJeu::obtenirInstance()->setprop1(avancer1);
	ConfigJeu::obtenirInstance()->setman1801(demi1);
	ConfigJeu::obtenirInstance()->setrothor1(droite1);
	ConfigJeu::obtenirInstance()->setrotantihor1(gauche1);
	ConfigJeu::obtenirInstance()->settir1(tir1);

	ConfigJeu::obtenirInstance()->setprop2(avancer2);
	ConfigJeu::obtenirInstance()->setman1802(demi2);
	ConfigJeu::obtenirInstance()->setrothor2(droite2);
	ConfigJeu::obtenirInstance()->setrotantihor2(gauche2);
	ConfigJeu::obtenirInstance()->settir2(tir2);
}
/*
 * Class:     ca_polymtl_inf2990_cpp_FacadeCpp
 * Method:    fctC_obtenirInfoPartie
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1obtenirInfoPartie
	(JNIEnv *, jclass, jint duree, jint ptvie)
{
	ConfigJeu::obtenirInstance()->settimer(duree);
	ConfigJeu::obtenirInstance()->setptvie(ptvie);
}

/*
 * Class:     ca_polymtl_inf2990_cpp_FacadeCpp
 * Method:    fctC_activerVuePerspective
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1activerVuePerspective
  (JNIEnv *, jclass)
{
	FacadeModele::obtenirInstance()->activerVuePerspective();
}

/*
 * Class:     ca_polymtl_inf2990_cpp_FacadeCpp
 * Method:    fctC_activerVueOrthogonale
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ca_polymtl_inf2990_cpp_FacadeCpp_fctC_1activerVueOrthogonale
  (JNIEnv *, jclass)
{
	FacadeModele::obtenirInstance()->activerVueOrthogonale();
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
