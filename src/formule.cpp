#include "formule.hpp"

#include <algorithm>

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

bool est_dans(const cls_t& c, const cnf_t& f){
	for(cnf_t::const_iterator it = f.cbegin(); it != f.cend(); it++) {
		if(*it == c){
			return true;
		}
	}
	
	return false;
}

lit_t var2lit(var_t v, bool p){
	if(p){
		return v * 2;
	}else{
		return v * 2 + 1;
	}
}

var_t lit2var(lit_t l) {
	if(positif(l)){
		return l / 2;
	}else{
		return (l - 1) / 2;
	}
}

lit_t neg(lit_t l){
	if(positif(l)){
		return l + 1;
	}else{
		return l - 1;
	}
}

bool positif(lit_t l) {
	return (l % 2 == 0 ? true : false);
}
