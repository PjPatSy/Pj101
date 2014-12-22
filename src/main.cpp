#include <fstream>
#include <cstdlib>
#include <iostream>

#include "formule.hpp"
#include "parser.hpp"
#include "sat.hpp"
#include "dimacs.hpp"

using namespace std;
 
int main(int argc, char** argv){
	if(argc < 3){
		cerr << "Usage: ./sat cnf.dimacs modele.dimacs" << endl;
		return EXIT_FAILURE;
	}
	
	ifstream fichier_cnf(argv[1]);
	//~ string list[6] = {"pb-simple1-unsat.cnf", "pb-simple2-unsat.cnf", "pb-simple3-sat.cnf", "pb-simple4-unsat.cnf", "pb-simple5-sat.cnf", "pb-simple6-sat.cnf"};
	//~ for(int i=0; i < 6; i++){
	dimacs dimacs_data;
	lit_dimacs(fichier_cnf, dimacs_data);
	// tableau dont les indices sont des variables et
	// le contenu est la valeur affectée à la variable.
	vector<val_t> valeurs(dimacs_data.nbVars, INDETERMINEE);
	
	ofstream fichier_modele(argv[2]);
	// attention effet de bord: valeurs est modifié par cherche
	if(cherche(valeurs, 0, dimacs_data.cnf)){
		set<lit_t> modele;
		for(size_t i = 0; i < valeurs.size(); i++){
			if(valeurs[i] == VRAI){
				modele.insert(var2lit(valeurs[i], true));
			}else{
				modele.insert(var2lit(valeurs[i], false));
			}
		}
		
		// remplir modele en fonction des valeurs données à chaque variable
		fichier_modele << "SAT" << endl;
		cout << "SAT" << endl;
		ecrit_clause_dimacs(fichier_modele, modele);
	}else{
		fichier_modele << "UNSAT" << endl;
		cout << "UNSAT" << endl;
	}
	fichier_modele.close();

}
