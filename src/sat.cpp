#include "sat.hpp"

val_t valeur_lit(const vector<val_t> & valeurs, lit_t l) {
	if(positif(l)){
		return valeurs[lit2var(l)];
	}else{
		if(valeurs[lit2var(l)] == INDETERMINEE){
			return INDETERMINEE;
		}else{
			return -1 * valeurs[lit2var(l)];
		}
	}
}

val_t valeur_clause(const vector<val_t> & valeurs, cls_t clause) {
	val_t result = FAUX;
	for(cls_t::iterator it = clause.begin(); it != clause.end(); it++) {
		if(valeur_lit(valeurs, *it) == VRAI){
			return VRAI;
		}
		if(valeur_lit(valeurs, *it) == INDETERMINEE) {
			result = INDETERMINEE;
		}
	}
	return result;
}

val_t valeur_cnf(const vector<val_t> & valeurs, cnf_t cnf) {
	val_t result = VRAI;
	for(cnf_t::iterator it = cnf.begin(); it != cnf.end(); it++) {
		if(valeur_clause(valeurs, *it) == FAUX){
			return FAUX;
		}
		if(valeur_clause(valeurs, *it) == INDETERMINEE) {
			result = INDETERMINEE;
		}
	}
	return result;
}

// Pas compris.. à vérifier !
bool cherche(vector<val_t> & valeurs, var_t suiv, const cnf_t & cnf) {
	if(suiv > valeurs.size()){
		if(valeur_cnf(valeurs, cnf)){
			return true;
		}else{
			return false;
		}
	}
	else{
		valeurs[suiv] = VRAI;
		if(cherche(valeurs, suiv + 1, cnf)){
			return true;
		}else{
			valeurs[suiv] = FAUX;
		}
		if(cherche(valeurs, suiv + 1, cnf)){
			return true;
		}else{
			valeurs[suiv] = INDETERMINEE;
			return false;
		}
	}
} 

//~ vector<vector<cls_t>> indexe_clauses(const cnf_t& cnf) {
	//~ // A FAIRE
	//~ vector<vector<cls_t> > v;
	//~ return v;
//~ }

//~ bool contient_insatisfaite(var_t variable, const vector<val_t>& valeurs, const vector<vector<cls_t> >& index_clauses) {
	//~ // A FAIRE
	//~ return false;
//~ }

//~ vector<var_t> propage(lit_t lit, vector<val_t> & valeurs, cnf_t & cnf, vector<vector<cls_t> > & index) {
	//~ // A FAIRE
	//~ vector<var_t> v;
	//~ return v;
//~ }

