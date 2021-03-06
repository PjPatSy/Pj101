#include "sat.hpp"

val_t valeur_lit(const vector<val_t> & valeurs, lit_t l) {
	if(positif(l)){
		return valeurs[lit2var(l)];
	}else{
		if(valeurs[lit2var(l)] == INDETERMINEE){
			return INDETERMINEE;
		}else{
			return ((valeurs[lit2var(l)] == FAUX)? VRAI : FAUX);
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

bool cherche_naive(vector<val_t> & valeurs, var_t suiv, const cnf_t & cnf) {
	if(suiv > valeurs.size()){
		if(valeur_cnf(valeurs, cnf) == VRAI){
			return true;
		}else{
			return false;
		}
	}
	else{
		// Si la cnf avec les valeurs actuelles est fausse ça ne sert à rien d'aller plus loin
		// On fait donc un retour en arrière dans l'arbre de recherche
		if(valeur_cnf(valeurs, cnf) == FAUX){
			valeurs[suiv] = INDETERMINEE;
			return false;
		}
		valeurs[suiv] = VRAI;
		if(cherche_naive(valeurs, suiv + 1, cnf)){
			return true;
		}else{
			valeurs[suiv] = FAUX;
		}
		if(cherche_naive(valeurs, suiv + 1, cnf)){
			return true;
		}else{
			valeurs[suiv] = INDETERMINEE;
			return false;
		}
	}
}

// Recherche avec contient_insatisfaite
bool cherche1(vector<val_t> & valeurs, var_t suiv, const vector<vector<cls_t> > & index) {
	if(suiv == valeurs.size()-1){
		valeurs[suiv] = VRAI;
		if(contient_insatisfaite(suiv, valeurs, index)){
			valeurs[suiv] = FAUX;
			if(contient_insatisfaite(suiv, valeurs, index)){
				valeurs[suiv] = INDETERMINEE;
				return false;
			}
			return true;
		}
		return true;
	}
	else{
		valeurs[suiv] = VRAI;
		if(!contient_insatisfaite(suiv, valeurs, index)){
			if(cherche1(valeurs, suiv + 1, index)){
				return true;
			}
		}
		valeurs[suiv] = FAUX;
		if(!contient_insatisfaite(suiv, valeurs, index)){
			if(cherche1(valeurs, suiv + 1, index)){
				return true;
			}
		}
		valeurs[suiv] = INDETERMINEE;
		return false;
	}
}

// Recherche avec propage
bool cherche2(vector<val_t> & valeurs, var_t suiv, const vector<vector<cls_t> > & index) {

	if(suiv == valeurs.size() - 1){
		valeurs[suiv] = VRAI;
		if(contient_insatisfaite(suiv, valeurs, index)){
			valeurs[suiv] = FAUX;
			if(contient_insatisfaite(suiv, valeurs, index)){
				valeurs[suiv] = INDETERMINEE;
				return false;
			}
			return true;
		}
		return true;
	}
	else{
		 vector <var_t> varPropa = propage(var2lit(suiv), valeurs, index);
    
		if(!varPropa.empty() && cherche2(valeurs, suiv + 1, index)){
			 return true;
		}
		for(unsigned int i = 0; i < varPropa.size(); i++){
			valeurs[varPropa[i]] = INDETERMINEE;
		}
		
		
		varPropa = propage(var2lit(suiv, false), valeurs, index);
		
		if(!varPropa.empty() && cherche2(valeurs, suiv + 1, index)){
			return true;
		}
		for(unsigned int i = 0; i < varPropa.size(); i++){
			valeurs[varPropa[i]] = INDETERMINEE;
		}
		
		valeurs[suiv] = INDETERMINEE;
		
		return false;
	}
}


vector<vector<cls_t>> indexe_clauses(const cnf_t& cnf) {
	vector<vector<cls_t> > v;
	for(cnf_t::const_iterator cls = cnf.begin(); cls != cnf.end(); cls++){
		for(cls_t::iterator it = cls->begin(); it != cls->end(); it++){
			if(v.size() <= (unsigned int)*it){
				v.resize(*it+1);
			}
			v[*it].push_back(*cls);
		}
	}
	
	return v;
}

bool contient_insatisfaite(var_t variable, const vector<val_t>& valeurs, const vector<vector<cls_t> >& index_clauses) {
	lit_t lit;
	
	if(valeurs[variable] == FAUX){
		lit = var2lit(variable, true);
	}
	else if(valeurs[variable] == VRAI){
		lit = var2lit(variable, false);
	}
	else{ // Ne doit normalement jamais être indéterminé
		return false;
	}
	if(lit < (int)index_clauses.size()){
		for(unsigned int i=0; i < index_clauses[lit].size(); i++){
			if(valeur_clause(valeurs, index_clauses[lit][i]) == FAUX){
				return true;
			}
		}
	}
	return false;
}

vector<var_t> propage(lit_t lit, vector<val_t> & valeurs, const vector<vector<cls_t> > & index) {
	vector<var_t> v_var;
	vector<lit_t> v_lit(1,lit);
	
	// Tant qu'il reste des littéraux à traiter
	while(!v_lit.empty()){
		// On retire un littérale
		lit_t l = v_lit.back();
		v_lit.pop_back();
		
		var_t v = lit2var(l);
		// Si le littérale n'a pas de valeur
		if(valeurs[v] == INDETERMINEE){
			// On ajoute la variable
			v_var.push_back(v);
			// On affecte la bonne valeur à la variable
			if(positif(l)){
				valeurs[v] = FAUX;
			}else{
				valeurs[v] = VRAI;
			}
			
			// On utilise l'index pour accéder aux clauses à vérifier
			for(size_t i = 0; i < index[l].size(); ++i){
				
				// Si la clause s'évalue à FAUX
				if(valeur_clause(valeurs, index[l][i]) == FAUX){
					// On remet à INDETERMINEE les valeurs des variables
					for(size_t j = 0; j < v_var.size(); ++j){
						valeurs[v_var[j]] = INDETERMINEE;
					}
					// On renvoie le vecteur vide
					v_var.clear();
					return v_var;
				}
				
				// Test des clauses unitaires
				lit_t Lj = -1;
				bool tropIndetermine = false; // Egale à true quand il y a plus d'un litéral indéterminié
				for(cls_t::iterator it = index[l][i].begin(); it != index[l][i].end(); it++){
					if(*it != VRAI){
						if(*it == INDETERMINEE){
							if(Lj == -1){
								Lj = *it;
							}
							else{
								tropIndetermine = true;
								break;
							}
						}
						if(!tropIndetermine && Lj != -1){
							v_lit.push_back(neg(Lj));
						}
					}
				}
			}
		}
	}
	return v_var;
}
