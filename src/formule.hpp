#ifndef Formule
#define Formule
#include <iostream>
// string est la classe des chaînes de caractères en C++ que l'on privilégie aux char * du C.
#include <string>
// set est la classe des ensembles de la STL du C++. set garantit l'unicité et
// le tri lors du parcours : le nombre et l'ordre des insertions ne compte pas.
// L'accès direct avec [] n'est pas possible : l'utilisation des itérateurs est obligatoire.
#include <set>
// vector est la classe des tableaux dynamiques de la STL du C++. vector ne 
// garantit PAS l'unicité et le tri lors du parcours : le nombre et l'ordre
// des insertions compte. L'accès direct avec [] est possible.
#include <vector>
// map est la classe des tableaux associatifs de la STL du C++.
#include <map>

using namespace std;


// Type des variables
typedef unsigned int  var_t;
// Type des littéraux 
typedef int           lit_t;
// Type des clauses, définies comme des ensembles de littéraux
typedef set<lit_t>    cls_t;
// Type des formules normales conjonctives (CNF), définies comme des tableaux
// dynamiques (vector en C++) de clauses
typedef vector<cls_t> cnf_t;
// Type des valeurs et constantes associées
typedef int           val_t;
#define VRAI 1
#define FAUX -1
#define INDETERMINEE 0

////////////////////////////////////////////////////////////////////////////////
//        A PARTIR D'ICI LES FONCTIONS SONT SIMPLEMENT DÉCLARÉES ET           //
//               DOIVENT ÊTRE IMPLÉMENTÉES DANS FORMULE.CPP                   //
////////////////////////////////////////////////////////////////////////////////
ostream& operator<<(ostream& out, const cls_t& cl);

ostream& operator<<(ostream& out, const cnf_t& c);

bool est_dans(const cls_t& cl, const cnf_t& c);

lit_t var2lit(var_t v, bool p = true);

var_t lit2var(lit_t l);

bool positif(lit_t l);

lit_t neg(lit_t l);

#endif
