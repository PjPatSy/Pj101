#ifndef Dimacs
#define Dimacs
#include "formule.hpp"
#include <set>
#include <istream>

using namespace std;

struct dimacs {
  int nbVars;
  cnf_t cnf;
};

void lit_dimacs(istream& input, dimacs& data);
set<lit_t> lit_resultat_dimacs(istream& input);

void ecrit_clause_dimacs(ostream& output, const cls_t& clause);

#endif
