//////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrthoTest.cpp
/// @author Najib Arbaoui
/// @date 2014-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#include "ProjectionOrthoTest.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION( ProjectionOrthoTest );

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::setUp()
///
/// Effectue l'initialisation pr�alable � l'ex�cution de l'ensemble des
/// cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets doivent �tre construits, il est conseill� de le
/// faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::setUp()
{
	int xMinCloture = 0;	// coordonn�e minimale en @a x de la cl�ture.
	int xMaxCloture = 500;	// coordonn�e maximale en @a x de la cl�ture.
	int yMinCloture = 0;	// coordonn�e minimale en @a y de la cl�ture.
	int yMaxCloture = 500;	// coordonn�e maximale en @a y de la cl�ture.
	
	double zAvant			= 1;		// distance du plan avant (en @a z).
	double zArriere			= 1000;		// distance du plan arri�re (en @a z).
	double zoomInMax		= 1;		// facteur de zoom in maximal.
	double zoomOutMax		= 10000;	// facteur de zoom out maximal.
	double incrementZoom	= 1.25;		// distance du plan arri�re (en @a z).

	double xMinFenetre = -200;	// coordonn�e minimale en @a x de la fen�tre virtuelle.
	double xMaxFenetre = 200;	// coordonn�e maximale en @a x de la fen�tre virtuelle.
	double yMinFenetre = -200;	// coordonn�e minimale en @a y de la fen�tre virtuelle.
	double yMaxFenetre = 200;	// coordonn�e maximale en @a y de la fen�tre virtuelle.

	m_oProjectionOrtho = new vue::ProjectionOrtho(
		xMinCloture, xMaxCloture, yMinCloture, yMaxCloture, 
		zAvant, zArriere, zoomInMax, zoomOutMax, 
		incrementZoom, 
		xMinFenetre, xMaxFenetre, yMinFenetre, yMaxFenetre
		);

	m_dIncrementZoom = incrementZoom;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::tearDown()
///
/// Effectue les op�rations de finalisation n�cessaires suite � l'ex�cution
/// de l'ensemble des cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets ont �t� allou�s � l'initialisation, ils doivent �tre
/// d�sallou�s, et il est conseill� de le faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::tearDown()
{
	delete m_oProjectionOrtho;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::test_rapportAspect()
///
/// Cas de test: Il faut alors que la projection corrige le rapport d'aspect de la fen�tre virtuelle en fonction de la cl�ture.
/// Pour ce test on redimmensionne la fen�tre en 640x480 (4:3).
/// Le rapport d'aspect de la cl�ture et de la fen�tre virtuelle est doit ensuite �tre �gale.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::test_rapportAspect()
{
	// On passe en HD (640�480 (4:3))
	Vecteur2i coinMin(0, 0), coinMax(640, 480);
	m_oProjectionOrtho->redimensionnerFenetre(coinMin, coinMax);

	Vecteur2 vec2FenetreMin, vec2FenetreMax;
	Vecteur2i vec2iDimensionCloture, vec2iClotureMin, vec2iClotureMax;
	double dRapportAspectVirtuel, dRapportAspectCloture;

	obtenirInformationsFenetreVirtuelle(vec2FenetreMin, vec2FenetreMax, dRapportAspectVirtuel);
	obtenirInformationsCloture(vec2iDimensionCloture, vec2iClotureMin, vec2iClotureMax, dRapportAspectCloture);
	validerRapportAspect(vec2iDimensionCloture, vec2FenetreMin, vec2FenetreMax);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::test_zoomerIn()
///
/// Cas de test: Zoom in sur la fen�tre virtuelle.
/// La cl�ture et la fen�tre virtuelle doivent garder le m�me rapport d'aspect.
/// Seul les coordonn�es de la fen�tre virtuelle doivent changer. La cl�ture doit rester identique.
/// De plus, le rappetissement de la fen�tre virtuelle est proportionelle � l'incr�ment du zoom.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::test_zoomerIn()
{
	// Coordon�es de la cl�ture et de la fen�tre virtuelle avant le zoom in
	// Calcul des rapports d'aspects
	Vecteur2i vec2iDimensionClotureAvantZoomIn;
	Vecteur2 vec2FenetreMinAvantZoomIn, vec2FenetreMaxAvantZoomIn;
	Vecteur2i vec2iClotureMinAvantZoomIn, vec2iClotureMaxAvantZoomIn;
	double dRapportAspectVirtuelAvantZoomIn, dRapportAspectClotureAvantZoomIn;

	obtenirInformationsFenetreVirtuelle(
		vec2FenetreMinAvantZoomIn, vec2FenetreMaxAvantZoomIn,
		dRapportAspectVirtuelAvantZoomIn
		);

	obtenirInformationsCloture(
		vec2iDimensionClotureAvantZoomIn,
		vec2iClotureMinAvantZoomIn, vec2iClotureMaxAvantZoomIn,
		dRapportAspectClotureAvantZoomIn
		);

	// M�thode � tester
	m_oProjectionOrtho->zoomerIn();

	// Coordon�es de la cl�ture et de la fen�tre virtuelle apr�s le zoom in
	// Calcul des rapports d'aspects
	Vecteur2i vec2iDimensionClotureApresZoomIn;
	Vecteur2 vec2FenetreMinApresZoomIn, vec2FenetreMaxApresZoomIn;
	Vecteur2i vec2iClotureMinApresZoomIn, vec2iClotureMaxApresZoomIn;
	double dRapportAspectVirtuelApresZoomIn, dRapportAspectClotureApresZoomIn;

	obtenirInformationsFenetreVirtuelle(
		vec2FenetreMinApresZoomIn, vec2FenetreMaxApresZoomIn,
		dRapportAspectVirtuelApresZoomIn
		);

	obtenirInformationsCloture(
		vec2iDimensionClotureApresZoomIn,
		vec2iClotureMinApresZoomIn, vec2iClotureMaxApresZoomIn,
		dRapportAspectClotureApresZoomIn
		);

	// V�rifie que la cl�ture reste la m�me
	CPPUNIT_ASSERT (vec2iDimensionClotureAvantZoomIn == vec2iDimensionClotureApresZoomIn);
	CPPUNIT_ASSERT (vec2iClotureMinAvantZoomIn == vec2iClotureMinApresZoomIn);
	CPPUNIT_ASSERT (vec2iClotureMaxAvantZoomIn == vec2iClotureMaxApresZoomIn);

	// Les rapports d'aspects ne doivent pas changer
	CPPUNIT_ASSERT (dRapportAspectClotureApresZoomIn == dRapportAspectVirtuelApresZoomIn);
	CPPUNIT_ASSERT (dRapportAspectClotureApresZoomIn == dRapportAspectClotureAvantZoomIn);
	CPPUNIT_ASSERT (dRapportAspectClotureApresZoomIn == dRapportAspectVirtuelAvantZoomIn);
	CPPUNIT_ASSERT (dRapportAspectVirtuelApresZoomIn == dRapportAspectClotureAvantZoomIn);
	CPPUNIT_ASSERT (dRapportAspectVirtuelApresZoomIn == dRapportAspectVirtuelAvantZoomIn);

	// Le rappetissement de la fen�tre virtuelle est proportionelle � l'incr�ment du zoom
	CPPUNIT_ASSERT ((vec2FenetreMinAvantZoomIn / m_dIncrementZoom) == vec2FenetreMinApresZoomIn);
	CPPUNIT_ASSERT ((vec2FenetreMaxAvantZoomIn / m_dIncrementZoom) == vec2FenetreMaxApresZoomIn);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::test_zoomerOut()
///
/// Cas de test: Zoom out sur la fen�tre virtuelle.
/// La cl�ture et la fen�tre virtuelle doivent garder le m�me rapport d'aspect.
/// Seul les coordonn�es de la fen�tre virtuelle doivent changer. La cl�ture doit rester identique.
/// De plus, le rappetissement de la fen�tre virtuelle est proportionelle � l'incr�ment du zoom.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::test_zoomerOut() 
{
	// Coordon�es de la cl�ture et de la fen�tre virtuelle avant le zoom in
	// Calcul des rapports d'aspects
	Vecteur2i vec2iDimensionClotureAvantZoomOut;
	Vecteur2 vec2FenetreMinAvantZoomOut, vec2FenetreMaxAvantZoomOut;
	Vecteur2i vec2iClotureMinAvantZoomOut, vec2iClotureMaxAvantZoomOut;
	double dRapportAspectVirtuelAvantZoomOut, dRapportAspectClotureAvantZoomOut;

	obtenirInformationsFenetreVirtuelle(
		vec2FenetreMinAvantZoomOut, vec2FenetreMaxAvantZoomOut,
		dRapportAspectVirtuelAvantZoomOut
		);

	obtenirInformationsCloture(
		vec2iDimensionClotureAvantZoomOut,
		vec2iClotureMinAvantZoomOut, vec2iClotureMaxAvantZoomOut,
		dRapportAspectClotureAvantZoomOut
		);

	// M�thode � tester
	m_oProjectionOrtho->zoomerOut();

	// Coordon�es de la cl�ture et de la fen�tre virtuelle apr�s le zoom in
	// Calcul des rapports d'aspects
	Vecteur2i vec2iDimensionClotureApresZoomOut;
	Vecteur2 vec2FenetreMinApresZoomOut, vec2FenetreMaxApresZoomOut;
	Vecteur2i vec2iClotureMinApresZoomOut, vec2iClotureMaxApresZoomOut;
	double dRapportAspectVirtuelApresZoomOut, dRapportAspectClotureApresZoomOut;

	obtenirInformationsFenetreVirtuelle(
		vec2FenetreMinApresZoomOut, vec2FenetreMaxApresZoomOut,
		dRapportAspectVirtuelApresZoomOut
		);

	obtenirInformationsCloture(
		vec2iDimensionClotureApresZoomOut,
		vec2iClotureMinApresZoomOut, vec2iClotureMaxApresZoomOut,
		dRapportAspectClotureApresZoomOut
		);

	// V�rifie que la cl�ture reste la m�me
	CPPUNIT_ASSERT (vec2iDimensionClotureAvantZoomOut == vec2iDimensionClotureApresZoomOut);
	CPPUNIT_ASSERT (vec2iClotureMinAvantZoomOut == vec2iClotureMinApresZoomOut);
	CPPUNIT_ASSERT (vec2iClotureMaxAvantZoomOut == vec2iClotureMaxApresZoomOut);

	// Les rapports d'aspects ne doivent pas changer
	CPPUNIT_ASSERT (dRapportAspectClotureApresZoomOut == dRapportAspectVirtuelApresZoomOut);
	CPPUNIT_ASSERT (dRapportAspectClotureApresZoomOut == dRapportAspectClotureAvantZoomOut);
	CPPUNIT_ASSERT (dRapportAspectClotureApresZoomOut == dRapportAspectVirtuelAvantZoomOut);
	CPPUNIT_ASSERT (dRapportAspectVirtuelApresZoomOut == dRapportAspectClotureAvantZoomOut);
	CPPUNIT_ASSERT (dRapportAspectVirtuelApresZoomOut == dRapportAspectVirtuelAvantZoomOut);

	// Le rappetissement de la fen�tre virtuelle est proportionelle � l'incr�ment du zoom
	CPPUNIT_ASSERT ((vec2FenetreMinAvantZoomOut * m_dIncrementZoom) == vec2FenetreMinApresZoomOut );
	CPPUNIT_ASSERT ((vec2FenetreMaxAvantZoomOut * m_dIncrementZoom) == vec2FenetreMaxApresZoomOut);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::test_redimensionnerFenetre()
///
/// Cas de test: Redimensionne la fen�tre avec un autre rapport d'aspect pour la cl�ture.
/// La cl�ture et la fen�tre virtuelle doivent garder le m�me rapport d'aspect.
/// On s'assure que la cl�ture prend bien la dimension donn�e en param�tre.
/// C'est la fen�tre virtuelle qui s'ajuste en fonction de la cl�ture.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::test_redimensionnerFenetre()
{
	// Initialement on est en 640x480 (4:3)
	// Coordon�es de la cl�ture et de la fen�tre virtuelle avant le zoom in
	// Calcul des rapports d'aspects
	Vecteur2i vec2iDimensionClotureAvantRedimensionnement;
	Vecteur2 vec2FenetreMinAvantRedimensionnement, vec2FenetreMaxAvantRedimensionnement;
	Vecteur2i vec2iClotureMinAvantRedimensionnement, vec2iClotureMaxAvantRedimensionnement;
	double dRapportAspectVirtuelAvantRedimensionnement, dRapportAspectClotureAvantRedimensionnement;

	obtenirInformationsFenetreVirtuelle(
		vec2FenetreMinAvantRedimensionnement, vec2FenetreMaxAvantRedimensionnement,
		dRapportAspectVirtuelAvantRedimensionnement
		);

	obtenirInformationsCloture(
		vec2iDimensionClotureAvantRedimensionnement,
		vec2iClotureMinAvantRedimensionnement, vec2iClotureMaxAvantRedimensionnement,
		dRapportAspectClotureAvantRedimensionnement
		);

	// On passe en HD (1280�720 (16:9))
	Vecteur2i coinMin(0, 0), coinMax(1280, 720);
	m_oProjectionOrtho->redimensionnerFenetre(coinMin, coinMax);

	// Coordon�es de la cl�ture et de la fen�tre virtuelle apr�s le redimensionnement
	// Calcul des rapports d'aspects
	Vecteur2i vec2iDimensionClotureApresRedimensionnement;
	Vecteur2 vec2FenetreMinApresRedimensionnement, vec2FenetreMaxApresRedimensionnement;
	Vecteur2i vec2iClotureMinApresRedimensionnement, vec2iClotureMaxApresRedimensionnement;
	double dRapportAspectVirtuelApresRedimensionnement, dRapportAspectClotureApresRedimensionnement;

	obtenirInformationsFenetreVirtuelle(
		vec2FenetreMinApresRedimensionnement, vec2FenetreMaxApresRedimensionnement,
		dRapportAspectVirtuelApresRedimensionnement
		);

	obtenirInformationsCloture(
		vec2iDimensionClotureApresRedimensionnement,
		vec2iClotureMinApresRedimensionnement, vec2iClotureMaxApresRedimensionnement,
		dRapportAspectClotureApresRedimensionnement
		);

	// Les coordonn�es de la cl�ture ont pas �t� modifi� avec les nouvelle valeurs
	CPPUNIT_ASSERT (!(vec2iClotureMinAvantRedimensionnement == vec2FenetreMinApresRedimensionnement));
	CPPUNIT_ASSERT (!(vec2iClotureMaxAvantRedimensionnement == vec2iClotureMaxApresRedimensionnement));
	CPPUNIT_ASSERT (!(vec2iDimensionClotureAvantRedimensionnement == vec2iDimensionClotureApresRedimensionnement));
	CPPUNIT_ASSERT (coinMin == vec2iClotureMinApresRedimensionnement);
	CPPUNIT_ASSERT (coinMax == vec2iClotureMaxApresRedimensionnement);

	// Le nouveau rapport d'aspect doit �tre celui du 16 : 9
	CPPUNIT_ASSERT (dRapportAspectClotureApresRedimensionnement == dRapportAspectVirtuelApresRedimensionnement);

	// Les rapports avant et apr�s ne sont plus sens� �tre �quivalent
	CPPUNIT_ASSERT (dRapportAspectClotureApresRedimensionnement	!= dRapportAspectClotureAvantRedimensionnement);
	CPPUNIT_ASSERT (dRapportAspectClotureApresRedimensionnement	!= dRapportAspectVirtuelAvantRedimensionnement);
	CPPUNIT_ASSERT (dRapportAspectVirtuelApresRedimensionnement	!= dRapportAspectVirtuelAvantRedimensionnement);
	CPPUNIT_ASSERT (dRapportAspectVirtuelApresRedimensionnement	!= dRapportAspectClotureAvantRedimensionnement);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::test_zoomerInElastique()
///
/// Cas de test: La nouvelle fen�tre virtuelle sp�cifi� devient la fen�tre virtuelle. On v�rifie le rapport d'aspect.
/// La cl�ture et la fen�tre virtuelle doivent garder le m�me rapport d'aspect.
/// C'est la fen�tre virtuelle qui s'ajuste en fonction de la cl�ture.
/// La cl�ture doit rester identique.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::test_zoomerInElastique()
{
	// Coordon�es de la cl�ture et de la fen�tre virtuelle avant le zoom in
	// Calcul des rapports d'aspects
	Vecteur2i vec2iDimensionClotureAvantZoomIn;
	Vecteur2 vec2FenetreMinAvantZoomIn, vec2FenetreMaxAvantZoomIn;
	Vecteur2i vec2iClotureMinAvantZoomIn, vec2iClotureMaxAvantZoomIn;
	double dRapportAspectVirtuelAvantZoomIn, dRapportAspectClotureAvantZoomIn;

	obtenirInformationsFenetreVirtuelle(
		vec2FenetreMinAvantZoomIn, vec2FenetreMaxAvantZoomIn,
		dRapportAspectVirtuelAvantZoomIn
		);

	obtenirInformationsCloture(
		vec2iDimensionClotureAvantZoomIn,
		vec2iClotureMinAvantZoomIn, vec2iClotureMaxAvantZoomIn,
		dRapportAspectClotureAvantZoomIn
		);

	// On prend le tier de la fen�tre virtuelle comme nouvelle fen�tre virtuelle
	Vecteur2i vec2iPointAncrage( vec2FenetreMinAvantZoomIn );
	Vecteur2i vec2iPointFinal(vec2FenetreMaxAvantZoomIn / 3);
	m_oProjectionOrtho->zoomerIn(vec2iPointAncrage, vec2iPointFinal);

	// Coordon�es de la cl�ture et de la fen�tre virtuelle apr�s le zoom in
	// Calcul des rapports d'aspects
	Vecteur2i vec2iDimensionClotureApresZoomIn;
	Vecteur2 vec2FenetreMinApresZoomIn, vec2FenetreMaxApresZoomIn;
	Vecteur2i vec2iClotureMinApresZoomIn, vec2iClotureMaxApresZoomIn;
	double dRapportAspectVirtuelApresZoomIn, dRapportAspectClotureApresZoomIn;

	obtenirInformationsFenetreVirtuelle(
		vec2FenetreMinApresZoomIn, vec2FenetreMaxApresZoomIn,
		dRapportAspectVirtuelApresZoomIn
		);

	obtenirInformationsCloture(
		vec2iDimensionClotureApresZoomIn,
		vec2iClotureMinApresZoomIn, vec2iClotureMaxApresZoomIn,
		dRapportAspectClotureApresZoomIn
		);

	double dEpsilon = 0.00001;

	// Les coordonn�es de la cl�ture n'ont pas �t� modifi�
	CPPUNIT_ASSERT (vec2iClotureMinApresZoomIn == vec2iClotureMinApresZoomIn);
	CPPUNIT_ASSERT (vec2iClotureMaxApresZoomIn == vec2iClotureMaxApresZoomIn);
	CPPUNIT_ASSERT (vec2iDimensionClotureApresZoomIn == vec2iDimensionClotureApresZoomIn);

	// Les rapports d'aspects ne doivent pas changer
	CPPUNIT_ASSERT (dRapportAspectClotureApresZoomIn == dRapportAspectVirtuelAvantZoomIn);
	CPPUNIT_ASSERT (dRapportAspectClotureApresZoomIn == dRapportAspectVirtuelApresZoomIn);
	CPPUNIT_ASSERT (dRapportAspectClotureApresZoomIn == dRapportAspectClotureAvantZoomIn);
	CPPUNIT_ASSERT (dRapportAspectVirtuelApresZoomIn == dRapportAspectClotureAvantZoomIn);
	CPPUNIT_ASSERT (dRapportAspectVirtuelApresZoomIn == dRapportAspectVirtuelAvantZoomIn);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::test_zoomerOutElastique()
///
/// Cas de test: La nouvelle fen�tre virtuelle sp�cifi� devient la fen�tre virtuelle, mais toute l'ancienne fen�tre doi maintenant �tre scal� � l'int�rieur (zoom out). 
/// On v�rifie le rapport d'aspect.
/// La cl�ture et la fen�tre virtuelle doivent garder le m�me rapport d'aspect.
/// C'est la fen�tre virtuelle qui s'ajuste en fonction de la cl�ture.
/// La cl�ture doit rester identique.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::test_zoomerOutElastique()
{
	// On se remet en 640x480
	Vecteur2i coinMin(0, 0), coinMax(640, 480);
	m_oProjectionOrtho->redimensionnerFenetre(coinMin, coinMax);

	// Coordon�es de la cl�ture et de la fen�tre virtuelle avant le zoom in
	// Calcul des rapports d'aspects
	Vecteur2i vec2iDimensionClotureAvantZoomOut;
	Vecteur2 vec2FenetreMinAvantZoomOut, vec2FenetreMaxAvantZoomOut;
	Vecteur2i vec2iClotureMinAvantZoomOut, vec2iClotureMaxAvantZoomOut;
	double dRapportAspectVirtuelAvantZoomOut, dRapportAspectClotureAvantZoomOut;

	obtenirInformationsFenetreVirtuelle(
		vec2FenetreMinAvantZoomOut, vec2FenetreMaxAvantZoomOut,
		dRapportAspectVirtuelAvantZoomOut
		);

	obtenirInformationsCloture(
		vec2iDimensionClotureAvantZoomOut,
		vec2iClotureMinAvantZoomOut, vec2iClotureMaxAvantZoomOut,
		dRapportAspectClotureAvantZoomOut
		);

	// On prend la moiti� de la fen�tre virtuelle comme nouvelle fen�tre virtuelle
	Vecteur2i vec2iPointAncrage(static_cast<const int>(vec2FenetreMinAvantZoomOut[0] / 2), static_cast<const int>(vec2FenetreMaxAvantZoomOut[0] / 2));
	Vecteur2i vec2iPointFinal(static_cast<const int>(vec2FenetreMinAvantZoomOut[1] / 2), static_cast<const int>(vec2FenetreMaxAvantZoomOut[1] / 2));
	m_oProjectionOrtho->zoomerIn(vec2iPointAncrage, vec2iPointFinal);

	// Coordon�es de la cl�ture et de la fen�tre virtuelle apr�s le zoom in
	// Calcul des rapports d'aspects
	Vecteur2i vec2iDimensionClotureApresZoomOut;
	Vecteur2 vec2FenetreMinApresZoomOut, vec2FenetreMaxApresZoomOut;
	Vecteur2i vec2iClotureMinApresZoomOut, vec2iClotureMaxApresZoomOut;
	double dRapportAspectVirtuelApresZoomOut, dRapportAspectClotureApresZoomOut;

	obtenirInformationsFenetreVirtuelle(
		vec2FenetreMinApresZoomOut, vec2FenetreMaxApresZoomOut,
		dRapportAspectVirtuelApresZoomOut
		);

	obtenirInformationsCloture(
		vec2iDimensionClotureApresZoomOut,
		vec2iClotureMinApresZoomOut, vec2iClotureMaxApresZoomOut,
		dRapportAspectClotureApresZoomOut
		);

	// Les coordonn�es de la cl�ture n'ont pas �t� modifi�
	CPPUNIT_ASSERT (vec2iClotureMinApresZoomOut == vec2iClotureMinApresZoomOut);
	CPPUNIT_ASSERT (vec2iClotureMaxApresZoomOut == vec2iClotureMaxApresZoomOut);
	CPPUNIT_ASSERT (vec2iDimensionClotureApresZoomOut == vec2iDimensionClotureApresZoomOut);

	// Les rapports d'aspects ne doivent pas changer
	CPPUNIT_ASSERT (dRapportAspectClotureApresZoomOut == dRapportAspectVirtuelApresZoomOut);
	CPPUNIT_ASSERT (dRapportAspectClotureApresZoomOut == dRapportAspectClotureAvantZoomOut);
	CPPUNIT_ASSERT (dRapportAspectVirtuelApresZoomOut == dRapportAspectVirtuelAvantZoomOut);
	CPPUNIT_ASSERT (dRapportAspectVirtuelApresZoomOut == dRapportAspectClotureAvantZoomOut);
	CPPUNIT_ASSERT (dRapportAspectClotureApresZoomOut == dRapportAspectVirtuelAvantZoomOut);
}

void ProjectionOrthoTest::obtenirInformationsFenetreVirtuelle(
	Vecteur2& vec2Min, Vecteur2& vec2Max,
	double& dAspectRatio
	)
{
	// Coordonn�es de la fen�tre virtuelle
	m_oProjectionOrtho->obtenirCoordonneesFenetreVirtuelle(vec2Min[0], vec2Max[0], vec2Min[1], vec2Max[1]);

	// Rapport d'aspect de la fen�tre virtuelle
	dAspectRatio = (vec2Max[0] - vec2Min[0]) / (vec2Max[1] - vec2Min[1]);
}

void ProjectionOrthoTest::obtenirInformationsCloture(
	Vecteur2i& vec2iDimensionCloture,
	Vecteur2i& vec2Min, Vecteur2i& vec2Max,
	double& dAspectRatio
	)
{
	// Coordon�es de la cl�ture
	m_oProjectionOrtho->obtenirCoordonneesCloture(vec2Min[0], vec2Max[0], vec2Min[1], vec2Max[1]);

	// Rapport d'aspect
	vec2iDimensionCloture = m_oProjectionOrtho->obtenirDimensionCloture();
	dAspectRatio = double(vec2iDimensionCloture[0]) / double(vec2iDimensionCloture[1]);
}

void ProjectionOrthoTest::validerRapportAspect(
	const Vecteur2i& vec2iDimensionCloture,
	const Vecteur2& vec2FenetreMin, const Vecteur2& vec2FenetreMax
	)
{
	// Normalement, le rapport d'aspect de la fen�tre virtuelle devrait �tre le m�me.
	// Puisque l'on compare des entiers flottants, il faut le faire comparativement � un seuil.
	double dEpsilon = 0.00001;
	double dRapportAspectCloture = double(vec2iDimensionCloture[0]) / double(vec2iDimensionCloture[1]);
	double dRapportAspectVirtuel = (vec2FenetreMax[0] - vec2FenetreMin[0]) / (vec2FenetreMax[1] - vec2FenetreMin[1]);
	CPPUNIT_ASSERT( abs(dRapportAspectCloture - dRapportAspectVirtuel) < dEpsilon );
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////