#include "formule.hpp"
#include "parser.hpp"
#include "sat.hpp"
#include "dimacs.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
 
using namespace std;
 
int main(int argc, char** argv) {
	if (argc < 3) {
		cerr << "Usage: ./sat cnf.dimacs modele.dimacs" << endl;
		return EXIT_FAILURE;
	}
	ifstream fichier_cnf(argv[1]);
	dimacs dimacs_data;
	lit_dimacs(fichier_cnf, dimacs_data);
	vector<val_t> valeurs; 	// tableau dont les indices sont des (numéros
							// de) variables et le contenu est la valeur
							// affectée à la variable.
							// A FAIRE: initialiser correctement valeurs;
	ofstream fichier_modele(argv[2]);
	// attention effet de bord: valeurs est modifié par cherche
	if (cherche(valeurs, 0, dimacs_data.cnf)) {
		set<lit_t> modele;
		// remplir modele en fonction des valeurs données à chaque variable
		fichier_modele << "SAT" << endl;
		ecrit_clause_dimacs(fichier_modele, modele);
	} else {
		fichier_modele << "UNSAT" << endl;
	}
	fichier_modele.close();
}
