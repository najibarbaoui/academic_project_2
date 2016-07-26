//////////////////////////////////////////////////////////////////////////////
/// @file VisiteurSelectionTest.cpp
/// @author Najib Arbaoui
/// @date 2014-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#include "VisiteurSelectionTest.h"

#include "NoeudAbstrait.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION( VisiteurSelectionTest );

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurSelectionTest::setUp()
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
void VisiteurSelectionTest::setUp()
{
	m_oArbreRenduINF2990 = new ArbreRenduINF2990();
	m_oArbreRenduINF2990->initialiser();

	/// Cr�ation des noeuds
	m_mapInstanceNoeud.insert(pair<string, NoeudAbstrait*>(ArbreRenduINF2990::NOM_ASTEROIDE, m_oArbreRenduINF2990->creerNoeud(ArbreRenduINF2990::NOM_ASTEROIDE)));
	m_mapInstanceNoeud.insert(pair<string, NoeudAbstrait*>(ArbreRenduINF2990::NOM_BARRIEREPROTECTRICE, m_oArbreRenduINF2990->creerNoeud(ArbreRenduINF2990::NOM_BARRIEREPROTECTRICE)));
	m_mapInstanceNoeud.insert(pair<string, NoeudAbstrait*>(ArbreRenduINF2990::NOM_BONUSACCELERATEUR, m_oArbreRenduINF2990->creerNoeud(ArbreRenduINF2990::NOM_BONUSACCELERATEUR)));
	m_mapInstanceNoeud.insert(pair<string, NoeudAbstrait*>(ArbreRenduINF2990::NOM_PORTAIL, m_oArbreRenduINF2990->creerNoeud(ArbreRenduINF2990::NOM_PORTAIL)));
	m_mapInstanceNoeud.insert(pair<string, NoeudAbstrait*>(ArbreRenduINF2990::NOM_POSITIONDEPART, m_oArbreRenduINF2990->creerNoeud(ArbreRenduINF2990::NOM_POSITIONDEPART)));
	m_mapInstanceNoeud.insert(pair<string, NoeudAbstrait*>(ArbreRenduINF2990::NOM_PROJECTILE, m_oArbreRenduINF2990->creerNoeud(ArbreRenduINF2990::NOM_PROJECTILE)));
	m_mapInstanceNoeud.insert(pair<string, NoeudAbstrait*>(ArbreRenduINF2990::NOM_STATIONSPATIALE, m_oArbreRenduINF2990->creerNoeud(ArbreRenduINF2990::NOM_STATIONSPATIALE)));
	m_mapInstanceNoeud.insert(pair<string, NoeudAbstrait*>(ArbreRenduINF2990::NOM_VAISSEAU, m_oArbreRenduINF2990->creerNoeud(ArbreRenduINF2990::NOM_VAISSEAU)));
	m_mapInstanceNoeud.insert(pair<string, NoeudAbstrait*>(ArbreRenduINF2990::NOM_ZONEJEU, m_oArbreRenduINF2990->creerNoeud(ArbreRenduINF2990::NOM_ZONEJEU)));
	m_mapInstanceNoeud.insert(pair<string, NoeudAbstrait*>(ArbreRenduINF2990::NOM_ZONEPASSAGE, m_oArbreRenduINF2990->creerNoeud(ArbreRenduINF2990::NOM_ZONEPASSAGE)));

	// On ajoute chaque noeud � l'arbre
	m_oArbreRenduINF2990->ajouter(m_mapInstanceNoeud[ArbreRenduINF2990::NOM_ASTEROIDE]);
	m_oArbreRenduINF2990->ajouter(m_mapInstanceNoeud[ArbreRenduINF2990::NOM_BARRIEREPROTECTRICE]);
	m_oArbreRenduINF2990->ajouter(m_mapInstanceNoeud[ArbreRenduINF2990::NOM_BONUSACCELERATEUR]);
	m_oArbreRenduINF2990->ajouter(m_mapInstanceNoeud[ArbreRenduINF2990::NOM_PORTAIL]);
	m_oArbreRenduINF2990->ajouter(m_mapInstanceNoeud[ArbreRenduINF2990::NOM_POSITIONDEPART]);
	m_oArbreRenduINF2990->ajouter(m_mapInstanceNoeud[ArbreRenduINF2990::NOM_PROJECTILE]);
	m_oArbreRenduINF2990->ajouter(m_mapInstanceNoeud[ArbreRenduINF2990::NOM_STATIONSPATIALE]);
	m_oArbreRenduINF2990->ajouter(m_mapInstanceNoeud[ArbreRenduINF2990::NOM_VAISSEAU]);
	m_oArbreRenduINF2990->ajouter(m_mapInstanceNoeud[ArbreRenduINF2990::NOM_ZONEJEU]);
	m_oArbreRenduINF2990->ajouter(m_mapInstanceNoeud[ArbreRenduINF2990::NOM_ZONEPASSAGE]);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurSelectionTest::tearDown()
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
void VisiteurSelectionTest::tearDown()
{
	delete m_oArbreRenduINF2990;
	typedef std::map<std::string, NoeudAbstrait*>::iterator it_type;
	for(it_type iterator = m_mapInstanceNoeud.begin(); iterator != m_mapInstanceNoeud.end(); iterator++) {
		// Lorsque l'arbre de rendu se fait d�tuire, il se fait vider de tous ses enfants
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurSelectionTest::test_SelectionnableUnique()
///
/// Cas de test: Test si la s�lection d'un objet s�lectionnable unique est possible.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void  VisiteurSelectionTest::test_SelectionnableUnique()
{
	// Assigner une position relative au noeud diff�rente de la position relative par d�faut qui est de (0, 0)
	m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_ASTEROIDE)->assignerPositionRelative(Vecteur3(2, 3, 0));

	// Le noeud ast�roide n'est pas s�lectionn�
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_ASTEROIDE)->estSelectionne());

	// Cr�er un visiteur pour s�lection le noeud derni�rement cr�er
	m_oVisiteurSelection = new VisiteurSelection(Vecteur3(1, 2, 0), Vecteur3(2, 4, 0), false);
	m_oArbreRenduINF2990->accepter(*m_oVisiteurSelection);

	// Le noeud ast�roides devrait �tre s�lectionn�
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_ASTEROIDE)->estSelectionne());

	delete m_oVisiteurSelection;
}
