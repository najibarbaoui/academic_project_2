//////////////////////////////////////////////////////////////////////////////
/// @file NoeudCompositeTest.cpp
/// @author Najib Arbaoui
/// @date 2014-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#include "NoeudCompositeTest.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION( NoeudCompositeTest );

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::setUp()
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
void NoeudCompositeTest::setUp()
{
	m_oArbreRenduINF2990 = new ArbreRenduINF2990();

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
/// @fn void NoeudCompositeTest::tearDown()
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
void NoeudCompositeTest::tearDown()
{
	delete m_oArbreRenduINF2990;
	typedef std::map<std::string, NoeudAbstrait*>::iterator it_type;
	for(it_type iterator = m_mapInstanceNoeud.begin(); iterator != m_mapInstanceNoeud.end(); iterator++) {
		// Lorsque l'arbre de rendu se fait d�tuire, il se fait vider de tous ses enfants
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::test_effacer()
///
/// Cas de test: On efface les noeuds un � un dans l'arbre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::test_effacer()
{
	m_oArbreRenduINF2990->effacer(m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_ASTEROIDE));
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_ASTEROIDE));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->obtenirNombreEnfants () == 9);

	m_oArbreRenduINF2990->effacer(m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_BARRIEREPROTECTRICE));
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_BARRIEREPROTECTRICE)); 
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->obtenirNombreEnfants () == 8);

	m_oArbreRenduINF2990->effacer(m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_BONUSACCELERATEUR));
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_BONUSACCELERATEUR));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->obtenirNombreEnfants () == 7);

	m_oArbreRenduINF2990->effacer(m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_PORTAIL));
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_PORTAIL));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->obtenirNombreEnfants () == 6);

	m_oArbreRenduINF2990->effacer(m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_POSITIONDEPART));
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_POSITIONDEPART));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->obtenirNombreEnfants () == 5);

	m_oArbreRenduINF2990->effacer(m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_PROJECTILE));
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_PROJECTILE));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->obtenirNombreEnfants () == 4);

	m_oArbreRenduINF2990->effacer(m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_STATIONSPATIALE));
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_STATIONSPATIALE));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->obtenirNombreEnfants () == 3);

	m_oArbreRenduINF2990->effacer(m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_VAISSEAU));
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_VAISSEAU));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->obtenirNombreEnfants () == 2);

	m_oArbreRenduINF2990->effacer(m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_ZONEJEU));
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_ZONEJEU));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->obtenirNombreEnfants () == 1);

	m_oArbreRenduINF2990->effacer(m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_ZONEPASSAGE));
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_ZONEPASSAGE));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->obtenirNombreEnfants () == 0);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::test_selectionnerTout()
///
/// Cas de test: On s�lectionne l'arbre en entier. Certains noeuds ne sont pas s�lectionnable.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::test_selectionnerTout()
{
	// Initialement tous les noeuds sont d�s�lectionn�s
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_ASTEROIDE)->estSelectionne());
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_BARRIEREPROTECTRICE)->estSelectionne());
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_BONUSACCELERATEUR)->estSelectionne());
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_PORTAIL)->estSelectionne());
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_POSITIONDEPART)->estSelectionne());
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_PROJECTILE)->estSelectionne());
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_STATIONSPATIALE)->estSelectionne());
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_VAISSEAU)->estSelectionne());
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_ZONEJEU)->estSelectionne());
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_ZONEPASSAGE)->estSelectionne());

	m_oArbreRenduINF2990->selectionnerTout();

	// Ce noeud ne peut pas �tre s�lectionn�
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_ZONEJEU)->estSelectionne());

	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_ASTEROIDE)->estSelectionne());
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_BARRIEREPROTECTRICE)->estSelectionne());
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_BONUSACCELERATEUR)->estSelectionne());
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_PORTAIL)->estSelectionne());
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_POSITIONDEPART)->estSelectionne());
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_PROJECTILE)->estSelectionne());
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_STATIONSPATIALE)->estSelectionne());
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_VAISSEAU)->estSelectionne());
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_ZONEPASSAGE)->estSelectionne());
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::test_selectionnerTout()
///
/// Cas de test: On s�lectionne l'arbre en entier, et on le d�s�lectionne. Certains noeuds sont non-s�lectionnable.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::test_deselectionnerTout()
{
	m_oArbreRenduINF2990->selectionnerTout();

	// Ce noeud ne peut pas �tre s�lectionn�
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_ZONEJEU)->estSelectionne());

	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_ASTEROIDE)->estSelectionne());
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_BARRIEREPROTECTRICE)->estSelectionne());
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_BONUSACCELERATEUR)->estSelectionne());
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_PORTAIL)->estSelectionne());
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_POSITIONDEPART)->estSelectionne());
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_PROJECTILE)->estSelectionne());
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_STATIONSPATIALE)->estSelectionne());
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_VAISSEAU)->estSelectionne());
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_ZONEPASSAGE)->estSelectionne());

	m_oArbreRenduINF2990->deselectionnerTout();

	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_ASTEROIDE)->estSelectionne());
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_BARRIEREPROTECTRICE)->estSelectionne());
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_BONUSACCELERATEUR)->estSelectionne());
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_PORTAIL)->estSelectionne());
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_POSITIONDEPART)->estSelectionne());
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_PROJECTILE)->estSelectionne());
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_STATIONSPATIALE)->estSelectionne());
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_VAISSEAU)->estSelectionne());
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_ZONEJEU)->estSelectionne());
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_ZONEPASSAGE)->estSelectionne());
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::test_obtenirNombreEnfants()
///
/// Cas de test: Le noeud composite (l'arbre de rendu inf2990) contient les 10 enfants que nous lui avons rajout�.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::test_obtenirNombreEnfants()
{
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->obtenirNombreEnfants () == 10);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::test_effacerSelection()
///
/// Cas de test: On vide l'arbre gr�ce � la s�lection. Puisque la zone de jeu ne peut pas �tre s�lectionn�, c'est le seul noeud restant.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::test_effacerSelection()
{
	m_oArbreRenduINF2990->selectionnerTout();
	//m_oArbreRenduINF2990->effacerSelection();

	// La zone de jeu ne peut pas �tre s�lectionn�
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->obtenirNombreEnfants () == 10);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////