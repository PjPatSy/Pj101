#include "sat.hpp"

////////////////////////////////////////////////////////////////////////////////
//               ICI LES FONCTIONS SONT A IMPLEMENTER                         //
////////////////////////////////////////////////////////////////////////////////

val_t valeur_lit(const vector<val_t> & valeurs, lit_t l) {
  // A FAIRE
  return INDETERMINEE;
}

val_t valeur_clause(const vector<val_t> & valeurs, cls_t clause) {
  // A FAIRE
  return INDETERMINEE;
}

val_t valeur_cnf(const vector<val_t> & valeurs, cnf_t cnf) {
  // A FAIRE
  return INDETERMINEE;
}

bool cherche(vector<val_t> & valeurs, var_t suiv, const cnf_t & cnf) {
  // A FAIRE
  return false;
} 

vector<vector<cls_t>> indexe_clauses(const cnf_t& cnf) {
  // A FAIRE
  vector<vector<cls_t> > v;
  return v;
}

bool contient_insatisfaite(var_t variable, 
                           const vector<val_t>& valeurs,
                           const vector<vector<cls_t> >& index_clauses) {
  // A FAIRE
  return false;
}

vector<var_t> propage(lit_t lit, vector<val_t> & valeurs, cnf_t & cnf, vector<vector<cls_t> > & index) {
  // A FAIRE
  vector<var_t> v;
  return v;
}

