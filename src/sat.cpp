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

bool cherche(vector<val_t> & valeurs, var_t suiv, const cnf_t & cnf) {
	if(suiv > valeurs.size()){
		if(valeur_cnf(valeurs, cnf) == VRAI){
			return true;
		}else{
			return false;
		}
	}
	else{
		if(valeur_cnf(valeurs, cnf) == FAUX){
			valeurs[suiv] = INDETERMINEE;
			return false;
		}
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

// Fonction propage d'un autre gars
//~ vector<var_t> propage(lit_t lit, vector<val_t> & valeurs, const vector<vector<cls_t> > & index) {
	//~ vector<var_t> resultat;
	//~ vector<lit_t> liste (1,lit);      // --> Cette structure contiendras la liste courante                                                  
	//~ //     des littéraux que l'on veut affecter à vrai                                                    
	//~ lit_t lit_temp;                   // --> Littéral temporaire de travail                                                                 
	//~ var_t var_temp;                   // --> Variable associé au littéral temp                                                              
	//~ while(!liste.empty()) {           // --> Tant qu'il reste des littéraux à traiter                                                       
		//~ lit_temp = liste.back();
		//~ liste.pop_back();            // --> On retire un littéral des littéraux à traiter                                                  
		//~ var_temp = lit2var(lit_temp);
		//~ if(valeurs[var_temp] == INDETERMINEE) {    // --> Si aucune valeur ne lui ait affecté                                              
			//~ resultat.push_back(var_temp);         // --> On ajoute la variable correspondant à temp dans le vector résultat               
			//~ positif(lit_temp) ? valeurs[var_temp] = FAUX : valeurs[var_temp] = VRAI;
			//~ // --> Pour rendre unitaire une clause, il faut que l'un de ses littéraux soit affecté à FAUX                                 
			//~ // --> Pour chaque clause                                                                                                     
			//~ for(size_t i=0; i<index[lit_temp].size(); i++) {
				//~ // --> Si une clause s'évalue à FAUX alors la CNF aussi                                                                  
				//~ if(valeur_clause(valeurs, index[lit_temp][i]) == FAUX) {
					//~ for(size_t j=0; j<resultat.size(); j++)
						//~ valeurs[resultat[j]] = INDETERMINEE;
					//~ resultat.clear();
					//~ return resultat;
				//~ }
//~ 
				//~ lit_t t = estUnitaire(index[lit_temp][i],valeurs);
				//~ // --> Pour chaque clause unitaire trouvée                                                                               
				//~ if(t != -1) {
					//~ liste.push_back(t);
				//~ }
			//~ }
		//~ }
	//~ }
	//~ return resultat;
//~ }
