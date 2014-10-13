#include "parser.hpp"
#include "edt.hpp"
#include "dimacs.hpp"
#include <fstream>

using namespace std;

void usage() {
    cerr << " edt fichier_probleme.txt -o fichier_cnf.dimacs" << endl;
    cerr << "ou"<< endl;
    cerr << " edt --solution fichier_probleme.txt -i resultat_sat.dimacs -o resultat_emploi_du_temps.html";
}

int main(int argc, char ** argv) {
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
            solution sol = construit_solution(modele,pb);
            ofstream out(output);
            affiche_solution_html(out,sol,pb);
            out.close();
        }
    }
    return 0;
}
