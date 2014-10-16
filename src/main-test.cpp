#include <UnitTest++.h>
#include "formule.hpp"
#include "parser.hpp"
#include "dimacs.hpp"
#include <iostream>
#include <sstream>

// Un test simple qui réussit
TEST(test1) {
  CHECK(2 == 1+1);
}

// Un test simple qui échoue
//~ TEST(test2) {
  //~ CHECK(2 == 1+2);
//~ }

// Exemple de test des fonctions de lecture et d'écriture au format dimacs
TEST(lit_ecrit_dimacs) {
    cnf_t cnf;
    cnf.push_back({1,3,4,7});
    cnf.push_back({2,3});
    ostringstream out;
    for(auto it = cnf.cbegin(); it != cnf.cend(); ++it) {
        ecrit_clause_dimacs(out,*it);
    }
    istringstream in(out.str());
    dimacs d;
    lit_dimacs(in,d);
    auto it1 = cnf.cbegin();
    auto it2 = d.cnf.cend();
    while (it1 != cnf.cend() && it2 != d.cnf.cend()) {
        CHECK(*it1 == *it2);
        ++it1;
        ++it2;
    }
    CHECK(d.nbVars == 4);
}


int main()
{
	lit_t a = 12;
	lit_t b = 1;
	lit_t c = 7;
	lit_t d = 9;
	lit_t e = 3;
	lit_t f = 99;
	cls_t listeA = {a, b, c};
	cls_t listeB = {d, e, f};
	cls_t listeC = {a, e, c};
	cnf_t vect = {listeA, listeB};
	//~ cout << vect << '\n';
	if(est_dans(listeC, vect)) cout << "ok" << endl;
	else cout << "pas ok" << endl;
	return UnitTest::RunAllTests(); // un peu magique: lance tous les tests
}
