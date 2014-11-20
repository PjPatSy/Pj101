#include "parser.hpp"
#include "edt.hpp"
#include "dimacs.hpp"
#include <fstream>

using namespace std;

void usage() {
    cerr << " edt fichier_probleme.txt -o fichier_cnf.dimacs" << endl;
    cerr << "ou"<< endl;
    cerr << " edt --solution fichier_probleme.txt -i resultat_sat.dimacs -o resultat_emploi_du_temps.html" << endl;
}

int main(int argc, char ** argv) {
	//~ string srcPb = "test-data/pb-simple5b.txt";
	//~ ifstream pbFile(srcPb);
	
	//~ probleme pb = lit_probleme(pbFile);
	
	//~ lit_edt vars;
	//~ init_lits(pb, vars);
	//~ set<lit_t> modele;
	//~ construit_solution(modele, pb);

	//~ cours_salle_creneau(cout, vars, 0, 2, 0, 1);
	//~ cours_enseignant_creneau(cout, vars, 0, 2, 1, 1);
	//~ cours_salle_creneau(cout, pb, vars);
	//~ cours_enseignant_creneau(cout, pb, vars);
	//~ cours_au_plus_une_fois(cout, pb, vars, 1);
	//~ cours_au_plus_une_salle(cout, pb, vars, 1); // (Na V Nb) et (Na V Nc) et (Nb V Nc)
	//~ cours_au_plus_un_enseignant(cout, pb, vars, 1);
	//~ cours_au_moins_une_fois(cout, pb, vars, 1);
	//~ cours_au_moins_un_enseignant(cout, pb, vars, 2);
	//~ cours_au_moins_une_salle(cout, pb, vars, 2);
	//~ cours_exactement_une_fois(cout, pb, vars);
	//~ cours_exactement_une_salle(cout, pb, vars);
	//~ cours_exactement_un_enseignant(cout, pb, vars);
	//~ 
	//~ set<int> lsCours = {0};
	//~ peut_enseigner_seulement(cout, pb, vars, 1, lsCours);
	//~ contrainte_enseigne(cout, pb, vars);
	//~ set<int> lsSalles = {0};
	//~ peut_seulement_avoir_lieu_dans(cout, pb, vars, 0, lsSalles);
	//~ contraintes_salles_cours(cout, pb, vars);
	//~ set<int> lsIndisp = {1};
	//~ indisponibilites_enseignant(cout, pb, vars, 1, lsIndisp);
	//~ contrainte_indisponibilites(cout, pb, vars);
	


    probleme pb;
    pb.nb_salles = 0;
    bool probleme_vers_formule = true;
    string input = "";
    string output = "";
    for(int i = 1; i < argc; ++i) {
        if ("--solution" == string(argv[i])) {
            probleme_vers_formule = false;
        } else if ("-i" == string(argv[i])) {
            ++i;
            if (i >= argc) {
                usage();
                return -1;
            } else {
                input = string(argv[i]);
            }
        } else if ("-o" == string(argv[i])) {
            ++i;
            if (i >= argc) {
                usage();
                return -1;
            } else {
                output = string(argv[i]);
            }
        } else {
            ifstream pb_file(argv[i]);
            pb = lit_probleme(pb_file);
            pb_file.close();
        }
    }
    if (pb.nb_salles == 0) {
        usage();
        return -1;
    }
    if ("" == output) {
        usage();
        return -1;
    }
    if (probleme_vers_formule) {
        ofstream out(output);
        ecrit_cnf_probleme(out, pb);
        out.close();
    } else {
        if ("" == input) {
            usage();
            return -1;
        } else {
            ifstream in(input);
            set<lit_t> modele = lit_resultat_dimacs(in);
            in.close();
            if (modele.size() > 0) {
              solution sol = construit_solution(modele,pb);
              ofstream out(output);
              affiche_solution_html(out,sol,pb);
              out.close();
            } else {
              cout << "modele vide, pas de solution" << endl;
              return 1;
            }
        }
    }
    
    return 0;
}
