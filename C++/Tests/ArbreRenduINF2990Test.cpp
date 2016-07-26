////////////////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990.cpp
/// @author Najib Arbaoui
/// @date 2014-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#include "ArbreRenduINF2990Test.h"
#include "Utilitaire.h"

#include "UsineNoeud.h"

class UsineNoeudAsteroide;
class UsineNoeudBarriereProtectrice;

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION( ArbreRenduINF2990Test );

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990::setUp()
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
void ArbreRenduINF2990Test::setUp()
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
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990::tearDown()
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
void ArbreRenduINF2990Test::tearDown()
{
	delete m_oArbreRenduINF2990;
	typedef std::map<std::string, NoeudAbstrait* >::iterator it_type;
	for(it_type iterator = m_mapInstanceNoeud.begin(); iterator != m_mapInstanceNoeud.end(); iterator++) {
		// Lorsque l'arbre de rendu se fait d�tuire, il se fait vider de tous ses enfants
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990Test::test_creerNoeud()
///
/// Cas de test: On cr�er tous les types de noeuds possible. Si l'on est incapable de trouver l'usine pour le noeud, l'usine nous retourne que le noeud est NULL 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::test_creerNoeud()
{
	CPPUNIT_ASSERT (m_mapInstanceNoeud[ArbreRenduINF2990::NOM_ASTEROIDE]);
	CPPUNIT_ASSERT (m_mapInstanceNoeud[ArbreRenduINF2990::NOM_BARRIEREPROTECTRICE]);
	CPPUNIT_ASSERT (m_mapInstanceNoeud[ArbreRenduINF2990::NOM_BONUSACCELERATEUR]);
	CPPUNIT_ASSERT (m_mapInstanceNoeud[ArbreRenduINF2990::NOM_PORTAIL]);
	CPPUNIT_ASSERT (m_mapInstanceNoeud[ArbreRenduINF2990::NOM_POSITIONDEPART]);
	CPPUNIT_ASSERT (m_mapInstanceNoeud[ArbreRenduINF2990::NOM_PROJECTILE]);
	CPPUNIT_ASSERT (m_mapInstanceNoeud[ArbreRenduINF2990::NOM_STATIONSPATIALE]);
	CPPUNIT_ASSERT (m_mapInstanceNoeud[ArbreRenduINF2990::NOM_VAISSEAU]);
	CPPUNIT_ASSERT (m_mapInstanceNoeud[ArbreRenduINF2990::NOM_ZONEJEU]);
	CPPUNIT_ASSERT (m_mapInstanceNoeud[ArbreRenduINF2990::NOM_ZONEPASSAGE]);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990Test::test_chercherUsine()
///
/// Cas de test: V�rifie si toutes les usines possibles sont pr�sentent.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::test_chercherUsine()
{
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercherUsine(ArbreRenduINF2990::NOM_ASTEROIDE));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercherUsine(ArbreRenduINF2990::NOM_BARRIEREPROTECTRICE));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercherUsine(ArbreRenduINF2990::NOM_BONUSACCELERATEUR));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercherUsine(ArbreRenduINF2990::NOM_PORTAIL));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercherUsine(ArbreRenduINF2990::NOM_POSITIONDEPART));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercherUsine(ArbreRenduINF2990::NOM_PROJECTILE));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercherUsine(ArbreRenduINF2990::NOM_STATIONSPATIALE));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercherUsine(ArbreRenduINF2990::NOM_VAISSEAU));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercherUsine(ArbreRenduINF2990::NOM_ZONEJEU));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercherUsine(ArbreRenduINF2990::NOM_ZONEPASSAGE));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990Test::test_ajouter()
///
/// Cas de test: Voir si tous les noeuds possibles cr�es peuvent �tre ajout� � l'arbre de rendu.
/// On v�rifie qu'il se sont bien ajout�s � l'arbre;
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::test_ajouter()
{
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

	/// On a cr�e 10 noeud, chacun de profondeur 1
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->obtenirNombreEnfants() == 11);
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->calculerProfondeur() == 2);

	/// Les noeuds se sont t-ils rajout� � l'arbre
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_ASTEROIDE));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_BARRIEREPROTECTRICE));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_BONUSACCELERATEUR));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_PORTAIL));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_POSITIONDEPART));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_PROJECTILE));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_STATIONSPATIALE));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_VAISSEAU));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_ZONEJEU));
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->chercher(ArbreRenduINF2990::NOM_ZONEPASSAGE));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990Test::test_ajouterNouveauNoeud()
///
/// Cas de test: On va tent� d'ajouter des noeud � un noeud ne pouvant pas contenir d'enfants.
/// On v�rifie par la suite que l'arbre ne contient que lui-m�me (pas d'enfant et de profondeur 1).
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::test_ajouterNouveauNoeud()
{
	NoeudAbstrait *pZoneJeu = m_oArbreRenduINF2990->obtenirZoneJeu();

	m_oArbreRenduINF2990->ajouterNouveauNoeud(m_oArbreRenduINF2990->obtenirZoneJeu()->obtenirType(),  m_mapInstanceNoeud[ArbreRenduINF2990::NOM_ASTEROIDE]->obtenirType());
	m_oArbreRenduINF2990->ajouterNouveauNoeud(m_oArbreRenduINF2990->obtenirZoneJeu()->obtenirType(),  m_mapInstanceNoeud[ArbreRenduINF2990::NOM_BARRIEREPROTECTRICE]->obtenirType());
	m_oArbreRenduINF2990->ajouterNouveauNoeud(m_oArbreRenduINF2990->obtenirZoneJeu()->obtenirType(),  m_mapInstanceNoeud[ArbreRenduINF2990::NOM_BONUSACCELERATEUR]->obtenirType());
	m_oArbreRenduINF2990->ajouterNouveauNoeud(m_oArbreRenduINF2990->obtenirZoneJeu()->obtenirType(),  m_mapInstanceNoeud[ArbreRenduINF2990::NOM_PORTAIL]->obtenirType());
	m_oArbreRenduINF2990->ajouterNouveauNoeud(m_oArbreRenduINF2990->obtenirZoneJeu()->obtenirType(),  m_mapInstanceNoeud[ArbreRenduINF2990::NOM_POSITIONDEPART]->obtenirType());
	m_oArbreRenduINF2990->ajouterNouveauNoeud(m_oArbreRenduINF2990->obtenirZoneJeu()->obtenirType(),  m_mapInstanceNoeud[ArbreRenduINF2990::NOM_STATIONSPATIALE]->obtenirType());
	m_oArbreRenduINF2990->ajouterNouveauNoeud(m_oArbreRenduINF2990->obtenirZoneJeu()->obtenirType(),  m_mapInstanceNoeud[ArbreRenduINF2990::NOM_VAISSEAU]->obtenirType());
	m_oArbreRenduINF2990->ajouterNouveauNoeud(m_oArbreRenduINF2990->obtenirZoneJeu()->obtenirType(),  m_mapInstanceNoeud[ArbreRenduINF2990::NOM_ZONEJEU]->obtenirType());
	m_oArbreRenduINF2990->ajouterNouveauNoeud(m_oArbreRenduINF2990->obtenirZoneJeu()->obtenirType(),  m_mapInstanceNoeud[ArbreRenduINF2990::NOM_ZONEPASSAGE]->obtenirType());

	/// On a cr�e 10 noeud � la zone de jeu, chacun de profondeur 1
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->obtenirZoneJeu()->obtenirNombreEnfants() == 0); // Ce type de noeud ne peut pas avoir d'enfant
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->obtenirZoneJeu()->calculerProfondeur() == 1); // Noeud sans enfant

	/// Aucun noeud ne doit s'�tre rajout�. Le seul noeud qui doit �tre valide est lui-m�me (la zone de jeu).
	CPPUNIT_ASSERT (m_oArbreRenduINF2990->obtenirZoneJeu()->chercher(ArbreRenduINF2990::NOM_ZONEJEU));

	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->obtenirZoneJeu()->chercher(ArbreRenduINF2990::NOM_ASTEROIDE));
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->obtenirZoneJeu()->chercher(ArbreRenduINF2990::NOM_BARRIEREPROTECTRICE));
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->obtenirZoneJeu()->chercher(ArbreRenduINF2990::NOM_BONUSACCELERATEUR));
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->obtenirZoneJeu()->chercher(ArbreRenduINF2990::NOM_PORTAIL));
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->obtenirZoneJeu()->chercher(ArbreRenduINF2990::NOM_POSITIONDEPART));
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->obtenirZoneJeu()->chercher(ArbreRenduINF2990::NOM_PROJECTILE));
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->obtenirZoneJeu()->chercher(ArbreRenduINF2990::NOM_STATIONSPATIALE));
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->obtenirZoneJeu()->chercher(ArbreRenduINF2990::NOM_VAISSEAU));
	CPPUNIT_ASSERT (!m_oArbreRenduINF2990->obtenirZoneJeu()->chercher(ArbreRenduINF2990::NOM_ZONEPASSAGE));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990Test::test_obtenirType()
///
/// Cas de test: Les noeuds cr�er � partir des usines sont-ils du bons type?
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::test_obtenirType()
{
	CPPUNIT_ASSERT( m_mapInstanceNoeud[ArbreRenduINF2990::NOM_ASTEROIDE]->obtenirType() == ArbreRenduINF2990::NOM_ASTEROIDE );	
	CPPUNIT_ASSERT( m_mapInstanceNoeud[ArbreRenduINF2990::NOM_BARRIEREPROTECTRICE]->obtenirType() == ArbreRenduINF2990::NOM_BARRIEREPROTECTRICE );	
	CPPUNIT_ASSERT( m_mapInstanceNoeud[ArbreRenduINF2990::NOM_BONUSACCELERATEUR]->obtenirType() == ArbreRenduINF2990::NOM_BONUSACCELERATEUR );	
	CPPUNIT_ASSERT( m_mapInstanceNoeud[ArbreRenduINF2990::NOM_PORTAIL]->obtenirType() == ArbreRenduINF2990::NOM_PORTAIL );	
	CPPUNIT_ASSERT( m_mapInstanceNoeud[ArbreRenduINF2990::NOM_POSITIONDEPART]->obtenirType() == ArbreRenduINF2990::NOM_POSITIONDEPART );	
	CPPUNIT_ASSERT( m_mapInstanceNoeud[ArbreRenduINF2990::NOM_PROJECTILE]->obtenirType() == ArbreRenduINF2990::NOM_PROJECTILE );	
	CPPUNIT_ASSERT( m_mapInstanceNoeud[ArbreRenduINF2990::NOM_STATIONSPATIALE]->obtenirType() == ArbreRenduINF2990::NOM_STATIONSPATIALE );	
	CPPUNIT_ASSERT( m_mapInstanceNoeud[ArbreRenduINF2990::NOM_VAISSEAU]->obtenirType() == ArbreRenduINF2990::NOM_VAISSEAU );	
	CPPUNIT_ASSERT( m_mapInstanceNoeud[ArbreRenduINF2990::NOM_ZONEJEU]->obtenirType() == ArbreRenduINF2990::NOM_ZONEJEU );	
	CPPUNIT_ASSERT( m_mapInstanceNoeud[ArbreRenduINF2990::NOM_ZONEPASSAGE]->obtenirType() == ArbreRenduINF2990::NOM_ZONEPASSAGE );
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
