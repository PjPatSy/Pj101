#include "edt.hpp"
#include "dimacs.hpp"

void init_probleme(probleme& pb) {
    pb.enseigne = vector< set<int> >(pb.nb_enseignants);
    pb.salles = vector< set<int> >(pb.nb_cours);
    pb.indisponibilites = vector< set<int> >(pb.nb_enseignants);
}

void affiche_solution_html(ostream& out, solution& sol, probleme& pb) {
    affectation vide;
    vide.enseignant = -1;
    vide.cours = -1;
    vide.salle = -1;
    vide.creneau = -1;
    vector<affectation> salles_vides(pb.nb_salles, vide);
    vector< vector<affectation> > table(pb.nb_creneaux, salles_vides);
    for(auto it = sol.cbegin(); it != sol.cend(); ++it) {
        table[it->creneau][it->salle] = *it;
    }
    out << "<html><head><title>Solution</title></head><body><h1>Solution</h1>" << endl;
    out << "<table><thead><tr>";
    for(int i = 0; i < pb.nb_salles; ++i) {
        out << "<th>Salle " << i << "</th>";
    }
    out << "</thead>" << endl << "<tbody>" << endl;
    for(int i = 0; i < pb.nb_creneaux; ++i) {
        out << "<tr>";
        for(int j = 0; j < pb.nb_salles; ++j) {
            out << "<td>";
            if (table[i][j].enseignant == -1) {
                out << " X ";
            } else {
                out << "Cours: " << table[i][j].cours;
                out << "<br/>Enseignant: " << table[i][j].enseignant;
            }
            out << "</td>";
        }
        out << "</tr>" << endl;
    }
    out << "</tbody></table>" << endl;
    out << "</html>" << endl;
}

void init_lits(const probleme& pb, lit_edt& vars){
	int j;
	cout << "dd" << endl;
	/*for(j = 0; j < pb->enseigne[i][j].size; j++){
		if(pb->enseigne[i][j] == j){
			vars[i]->push(var2lit(pb->enseigne[i][j]));
		}else{
			
			for(int cpt = j; cpt < pb->enseigne[i][j]; cpt++){
				vars[i]->push(var2lit(cpt, false));
			}
		}
	}
	for(int cpt = pb->enseigne[i][j]; cpt < pb->nb_cours; cpt++){
		vars[i]->push(var2lit(cpt, false));
	}*/
}

// A coder
void ecrit_cnf_probleme(ostream& out, probleme& pb) {
    out << "A implementer" << endl;
}

// A coder
solution construit_solution(set<lit_t>& modele, probleme& pb) {
    solution sol;
    return sol;
}

