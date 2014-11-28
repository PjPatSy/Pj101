#include <UnitTest++.h>
#include <iostream>
#include <sstream>

#include "formule.hpp"
#include "parser.hpp"
#include "dimacs.hpp"
#include "sat.hpp"

TEST(estDans){
	cls_t cls1 = {1, 4, 7, 6};
	cls_t cls2 = {1, 4, 9, 10};
	cls_t cls3 = {1, 2, 3, 4};
	cnf_t cnf = {cls1, cls2};
	CHECK(est_dans(cls1, cnf));
	CHECK(est_dans(cls2, cnf));
	CHECK(!est_dans(cls3, cnf));
}

TEST(var2lit){
	CHECK(var2lit(2) == 4);
	CHECK(var2lit(2, false) == 5);
	CHECK(var2lit(5, true) == 10);
	CHECK(var2lit(5, false) == 11);
}

TEST(lit2var){
	CHECK(lit2var(4) == 2);
	CHECK(lit2var(5) == 2);
	CHECK(lit2var(10) == 5);
	CHECK(lit2var(11) == 5);
}


TEST(neg){
	CHECK(neg(2) == 3);
	CHECK(neg(3) == 2);
	CHECK(neg(7) == 6);
}
TEST(positif){
	CHECK(positif(4));
	CHECK(!positif(5));
	CHECK(positif(0));
}

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

TEST(clause1){
	cls_t cl1 = {1, 4, 7, 6};
	cls_t cl2 = {1, 4, 9, 10};
	CHECK(cl1 != cl2);
	CHECK(cl2 != cl1);
	CHECK(cl1 == cl1);
	CHECK(cl2 == cl2);
}

TEST(valeur_lit){
	vector<val_t> valeurs = {VRAI, INDETERMINEE, FAUX};
	CHECK(valeur_lit(valeurs, 0) == VRAI);
	CHECK(valeur_lit(valeurs, 5) == FAUX);
	CHECK(valeur_lit(valeurs, 3) == INDETERMINEE);
	CHECK(valeur_lit(valeurs, 6) == INDETERMINEE);
}

TEST(valeur_clause){
	vector<val_t> valeurs = {VRAI, INDETERMINEE, FAUX, FAUX, INDETERMINEE, FAUX};
	CHECK(valeur_clause(valeurs, cls_t {0, 3, 5, 9}) == VRAI);
	CHECK(valeur_clause(valeurs, cls_t {4, 5, 6, 7, 10, 11}) == FAUX);
	CHECK(valeur_clause(valeurs, cls_t {3, 5, 9}) == INDETERMINEE);
	CHECK(valeur_clause(valeurs, cls_t {4, 5, 6, 7, 10, 11, 12}) == INDETERMINEE);
}

TEST(valeur_cnf){
	vector<val_t> valeurs = {VRAI, INDETERMINEE, FAUX, FAUX, INDETERMINEE, FAUX};
	cls_t clauseVraie = {0, 3, 5, 9};
	cls_t clauseFaux = {4, 5, 6, 7, 10, 11};
	cls_t clauseIndet = {3, 5, 9};
	CHECK(valeur_cnf(valeurs, cnf_t {clauseVraie, clauseVraie}) == VRAI);
	CHECK(valeur_cnf(valeurs, cnf_t {clauseVraie, clauseFaux, clauseIndet}) == FAUX);
	CHECK(valeur_cnf(valeurs, cnf_t {clauseVraie, clauseIndet}) == INDETERMINEE);
	CHECK(valeur_cnf(valeurs, cnf_t {clauseIndet}) == INDETERMINEE);
}

int main(){	
	return UnitTest::RunAllTests();
}
