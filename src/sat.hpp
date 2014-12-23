#ifndef Sat
#define Sat
#include "formule.hpp"


////////////////////////////////////////////////////////////////////////////////
//              ICI LES FONCTIONS SONT SIMPLEMENT DÉCLARÉES ET                //
//                   DOIVENT ÊTRE IMPLÉMENTÉES DANS SAT.CPP                   //
////////////////////////////////////////////////////////////////////////////////

// Solveur simple //////////////////////////////////////////////////////////////
val_t valeur_lit(const vector<val_t> & valeurs, lit_t l);
val_t valeur_clause(const vector<val_t> & valeurs, cls_t clause);
val_t valeur_cnf(const vector<val_t> & valeurs, cnf_t cnf);
bool cherche_naive(vector<val_t> & valeurs, var_t suiv, const cnf_t & cnf); 
bool cherche1(vector<val_t> & valeurs, var_t suiv, const vector<vector<cls_t> > & index); 
bool cherche2(vector<val_t> & valeurs, var_t suiv, const cnf_t & cnf, const vector<vector<cls_t> > & index); 
// Optimisations ///////////////////////////////////////////////////////////////
vector<vector<cls_t> > indexe_clauses(const cnf_t& cnf);
bool contient_insatisfaite(var_t variable, 
                           const vector<val_t>& valeurs,
                           const vector<vector<cls_t> >& index_clauses);
vector<var_t> propage(lit_t lit, vector<val_t> & valeurs, cnf_t & cnf, vector<vector<cls_t> > & index);
#endif
