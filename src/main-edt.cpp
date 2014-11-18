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
	probleme pb;
	ifstream input("test-data/pb-simple5.txt");
	pb = lit_probleme(input);
	
	cout << "______" << pb.nb_enseignants;
	
	// Problem 8 : exemple cours
	
	//~ lit_edt vars;
	//~ probleme pb;
	//~ pb.nb_enseignants = 2;
	//~ pb.nb_salles = 2;
	//~ pb.nb_creneaux = 2;
	//~ pb.nb_cours = 3;
	//~ 
	//~ 
	//~ pb.enseigne.resize(pb.nb_enseignants);
	//~ pb.enseigne[0] = {0, 1, 2};
	//~ pb.enseigne[1] = {0, 1};
	//~ pb.salles.resize(pb.nb_cours);
	//~ pb.salles[0] = {0};
	//~ pb.salles[1] = {0};
	//~ pb.salles[2] = {0, 1};
	//~ pb.indisponibilites.resize(1);
	//~ pb.indisponibilites[0] = {1};
	//~ 
//~ 
	//~ init_lits(pb, vars);
//~ 
	//~ cout << "Args(" << argc << ") : " << argv[0] << endl;
	
    //~ probleme pb;
    //~ pb.nb_salles = 0;
    //~ bool probleme_vers_formule = true;
    //~ string input = "";
    //~ string output = "";
    //~ for(int i = 1; i < argc; ++i) {
        //~ if ("--solution" == string(argv[i])) {
            //~ probleme_vers_formule = false;
        //~ } else if ("-i" == string(argv[i])) {
            //~ ++i;
            //~ if (i >= argc) {
                //~ usage();
                //~ return -1;
            //~ } else {
                //~ input = string(argv[i]);
            //~ }
        //~ } else if ("-o" == string(argv[i])) {
            //~ ++i;
            //~ if (i >= argc) {
                //~ usage();
                //~ return -1;
            //~ } else {
                //~ output = string(argv[i]);
            //~ }
        //~ } else {
            //~ ifstream pb_file(argv[i]);
            //~ pb = lit_probleme(pb_file);
            //~ pb_file.close();
        //~ }
    //~ }
    //~ if (pb.nb_salles == 0) {
        //~ usage();
        //~ return -1;
    //~ }
    //~ if ("" == output) {
        //~ usage();
        //~ return -1;
    //~ }
    //~ if (probleme_vers_formule) {
        //~ ofstream out(output);
        //~ ecrit_cnf_probleme(out, pb);
        //~ out.close();
    //~ } else {
        //~ if ("" == input) {
            //~ usage();
            //~ return -1;
        //~ } else {
            //~ ifstream in(input);
            //~ set<lit_t> modele = lit_resultat_dimacs(in);
            //~ in.close();
            //~ if (modele.size() > 0) {
              //~ solution sol = construit_solution(modele,pb);
              //~ ofstream out(output);
              //~ affiche_solution_html(out,sol,pb);
              //~ out.close();
            //~ } else {
              //~ cout << "modele vide, pas de solution" << endl;
              //~ return 1;
            //~ }
        //~ }
    //~ }
    
    return 0;
}
