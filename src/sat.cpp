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

bool cherche(vector<val_t> & valeurs, var_t suiv, const vector<vector<cls_t> > & index) {
	//valeurs[suiv] = FAUX;
	if(suiv > valeurs.size()){
		if(!contient_insatisfaite(suiv, valeurs, index)){
			return true;
		}else{
			return false;
		}
	}
	else{
		/* Si la cnf avec les valeurs actuelles est fausse ça ne sert à rin d'aller plus loin
		 * On fait donc un retour en arrière dans l'arbre de recherche*/
		if(contient_insatisfaite(suiv, valeurs, index)){
			valeurs[suiv] = INDETERMINEE;
			return false;
		}
		valeurs[suiv] = VRAI;
		if(cherche(valeurs, suiv + 1, index)){
			return true;
		}else{
			valeurs[suiv] = FAUX;
		}
		if(cherche(valeurs, suiv + 1, index)){
			return true;
		}else{
			valeurs[suiv] = INDETERMINEE;
			return false;
		}
	}
}

//~ bool cherche(vector<val_t> & valeurs, var_t suiv, const cnf_t & cnf, const vector<vector<cls_t> > & index) {
	//~ while(valeurs[suiv] != INDETERMINEE){
		//~ suiv++;
	//~ }
	//~ if(suiv >= valeurs.size()){
		//~ return valeur_cnf(valeurs, cnf) == VRAI;
	//~ }else{
		//~ vector<var_t> p1 = propage(var2lit(suiv, true), valeurs, index);
		//~ if(p1.size() > 0){
			//~ if(cherche(valeurs, suiv, cnf, index)){
				//~ return true;
			//~ }
		//~ }
		//~ for(size_t i = 0; i < p1.size(); i++){
			//~ valeurs[p1[i]] = INDETERMINEE;
		//~ }
		//~ vector<var_t> p2 = propage(var2lit(suiv, false), valeurs, index);	
		//~ if(p2.size() > 0){
			//~ if(cherche(valeurs, suiv, cnf, index)){
				//~ return true;
			//~ }
		//~ }
		//~ for(size_t i = 0; i < p2.size(); i++){
			//~ valeurs[p2[i]] = INDETERMINEE;
		//~ }
	//~ }	
//~ }

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
	
	//~ for(unsigned int i=0; i < v.size(); i++){
		//~ cout << " " << i << " : " << endl;
		//~ for(unsigned int j=0; j < v[i].size(); j++){
			//~ cout << "\t" << v[i][j] << endl;
		//~ }
	//~ }
	
	return v;
}

bool contient_insatisfaite(var_t variable, const vector<val_t>& valeurs, const vector<vector<cls_t> >& index_clauses) {
	//lit_t litF = var2lit(variable, false);
	lit_t lit;
	if(valeurs[variable] == FAUX){
		lit = var2lit(variable, true);
	}
	else if(valeurs[variable] == VRAI){
		lit = var2lit(variable, false);
	}
	else{
		//~ lit = var2lit(variable, true);
		//~ lit_t litF = var2lit(variable, false);
		//~ if(litF < (int)index_clauses.size()){
			//~ for(unsigned int i=0; i < index_clauses[litF].size(); i++){
				//~ if(valeur_clause(valeurs, index_clauses[litF][i]) == FAUX){
					//~ return true;
				//~ }
			//~ }
		//~ }
		//~ if(litV < (int)index_clauses.size()){
			//~ for(unsigned int i=0; i < index_clauses[litV].size(); i++){
				//~ if(valeur_clause(valeurs, index_clauses[litV][i]) == FAUX){
					//~ return true;
				//~ }
			//~ }
		//~ }
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
	var_t v;
	lit_t l;
	
	// Temps qu'il reste des littéraux à traiter
	while(!v_lit.empty()){
		// On retire un littérale
		l = v_lit.back();
		v_lit.pop_back();
		
		v = lit2var(l);
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
			for(size_t i = 0; i < index[l].size(); i++){
				// Pour chaque clause unitaire trouvée,
				// on ajoute le littéral qui n'a pas de valeur dans les littéraux à traiter
				//~ rien bité je regarderai plus tard
				//~ v_lit.push_back(le litteral);

				
				// Si la clause s'évalue à FAUX
				if(valeur_clause(valeurs, index[l][i]) == FAUX){
					// On remet à INDETERMINEE les valeurs des variables
					for(size_t j = 0; j < v_var.size(); j++){
						valeurs[v_var[j]] = INDETERMINEE;
					}
					// On renvoie le vecteur vide
					v_var.clear();
					return v_var;
				}
			}
		}
	}
	return v_var;
}
