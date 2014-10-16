#include "formule.hpp"

#include <algorithm>

////////////////////////////////////////////////////////////////////////////////
//            A PARTIR D'ICI LES FONCTIONS SONT A IMPLEMENTER                 //
////////////////////////////////////////////////////////////////////////////////
ostream& operator<<(ostream& out, const cls_t& cl){
	out << "{";
	for(cls_t::const_iterator it = cl.cbegin(); it != cl.cend(); it++) {
		if(it != cl.cbegin()){
			out << ", ";
		}
		out << *it;
	}
	out << "}";
	
	return out;
}

ostream& operator<<(ostream& out, const cnf_t& c){
	out << "{";
	for(cnf_t::const_iterator it = c.cbegin(); it != c.cend(); it++) {
		if(it != c.cbegin()){
			out << ", ";
		}
		out << *it;
	}
	out << "}";
	
	return out;
}
/////////////////////////////////////////////
// A DEMANDER AU PROF POUR LA LIB ALGO !!! //
/////////////////////////////////////////////
bool est_dans(const cls_t& c, const cnf_t& f){
	for(cnf_t::const_iterator it = f.cbegin(); it != f.cend(); it++) {
		if(*it == c){
			return true;
		}
	}
	
	//~ if(find(f.cbegin(), f.cend(), c) == f.cend()){
		//~ return true;
	//~ }
	
	return false;
}

lit_t var2lit(var_t v, bool p){
	if(v == 0){
		return 0;
	}
	return (p ? v * 2 : (v * 2) - 1);
}

lit_t neg(lit_t l){
	// A FAIRE
	return 0;
}


var_t lit2var(lit_t l) {
	if(v == 0){
		return 0;
	}
	return (p ? v * 2 : (v * 2) - 1);
}

bool positif(lit_t l) {
	// A FAIRE
	return true;
}
