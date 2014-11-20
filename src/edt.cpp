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
	int cpt = 0;
	vars.Cr_En.resize(pb.nb_cours);
	vars.Cr_Sal.resize(pb.nb_cours);
	vars.Cr_Cx.resize(pb.nb_cours);
	
	
	for(int i=0; i < pb.nb_cours; i++){
		for(int j=0; j < pb.nb_enseignants; j++){
			vars.Cr_En[i].push_back(var2lit(cpt++));
		}
	}
	for(int i=0; i < pb.nb_cours; i++){
		for(int j=0; j < pb.nb_salles; j++){
			vars.Cr_Sal[i].push_back(var2lit(cpt++));
		}
	}
	for(int i=0; i < pb.nb_cours; i++){
		for(int j=0; j < pb.nb_creneaux; j++){
			vars.Cr_Cx[i].push_back(var2lit(cpt++));
		}
	}
	
	cout << "Cr_En : " << endl;
	for(int i=0; i < pb.nb_cours; i++){
		cout << "\t";
		for(int j=0; j < pb.nb_enseignants; j++){
			cout << vars.Cr_En[i][j] << " ";
		}
		cout << endl;
	}
	
	cout << "Cr_Sal : " << endl;
	for(int i=0; i < pb.nb_cours; i++){
		cout << "\t";
		for(int j=0; j < pb.nb_salles; j++){
			cout << vars.Cr_Sal[i][j] << " ";
		}
		cout << endl;
	}
	
	
	cout << "Cr_Cx : " << endl;
	for(int i=0; i < pb.nb_cours; i++){
		cout << "\t";
		for(int j=0; j < pb.nb_creneaux; j++){
			cout << vars.Cr_Cx[i][j] << " ";
		}
		cout << endl;
	}
}

void cours_salle_creneau(ostream& out, const probleme& pb, const lit_edt& vars){
	for(int i=0; i < pb.nb_cours-1; i++){
		for(int j=i+1; j < pb.nb_cours; j++){
			for(int k=0; k < pb.nb_salles; k++){
				for(int l=0; l < pb.nb_creneaux; l++){
					cours_salle_creneau(out, vars, i, j, k, l);
				}
			}
		}
	}
}


void cours_salle_creneau(ostream& out, const lit_edt& vars, int cours1, int cours2, int salle, int creneau){
	cls_t clause = {neg(vars.Cr_Sal[cours1][salle]),
					neg(vars.Cr_Sal[cours2][salle]),
					neg(vars.Cr_Cx[cours1][creneau]),
					neg(vars.Cr_Cx[cours2][creneau])
					};
	ecrit_clause_dimacs(out, clause);
}

void cours_enseignant_creneau(ostream& out, const lit_edt& vars, int cours1, int cours2, int enseignant, int creneau){
	
	cls_t clause = {neg(vars.Cr_En[cours1][enseignant]),
					neg(vars.Cr_En[cours2][enseignant]),
					neg(vars.Cr_Cx[cours1][creneau]),
					neg(vars.Cr_Cx[cours2][creneau])
					};
	
	ecrit_clause_dimacs(out, clause);
}

void cours_enseignant_creneau(ostream& out, const probleme& pb, const lit_edt& vars){
	for(int i=0; i < pb.nb_cours-1; i++){
		for(int j=i+1; j < pb.nb_cours; j++){
			for(int k=0; k < pb.nb_enseignants; k++){
				for(int l=0; l < pb.nb_creneaux; l++){
					cours_enseignant_creneau(out, vars, i, j, k, l);
				}
			}
		}
	}
}

void cours_au_plus_une_fois(ostream& out, const probleme& pb, const lit_edt& vars, int cours){
	for(int i=0; i < pb.nb_creneaux-1; i++){
		for(int j=i+1; j < pb.nb_creneaux; j++){
			cls_t cl = {neg(vars.Cr_Cx[cours][i]), neg(vars.Cr_Cx[cours][j])};
			ecrit_clause_dimacs(out, cl);
		}
	}
}

void cours_au_plus_une_salle(ostream& out, const probleme& pb, const lit_edt& vars, int cours){
	for(int i=0; i < pb.nb_salles-1; i++){
		for(int j=i+1; j < pb.nb_salles; j++){
			cls_t cl = {neg(vars.Cr_Sal[cours][i]), neg(vars.Cr_Sal[cours][j])};
			ecrit_clause_dimacs(out, cl);
		}
	}
}

void cours_au_plus_un_enseignant(ostream& out, const probleme& pb, const lit_edt& vars, int cours){
	for(int i=0; i < pb.nb_enseignants-1; i++){
		for(int j=i+1; j < pb.nb_enseignants; j++){
			cls_t cl = {neg(vars.Cr_En[cours][i]), neg(vars.Cr_En[cours][j])};
			ecrit_clause_dimacs(out, cl);
		}
	}
}

// C'est à dire un parmi tous (a V b V c V...)
void cours_au_moins_une_fois(ostream& out, const probleme& pb, const lit_edt& vars, int cours){
	cls_t cl;
	for(int i=0; i < pb.nb_creneaux; i++){
		cl.insert(vars.Cr_Cx[cours][i]);
	}
	if(!cl.empty()){
		ecrit_clause_dimacs(out, cl);
	}
}


void cours_au_moins_une_salle(ostream& out, const probleme& pb, const lit_edt& vars, int cours){
	cls_t cl;
	for(int i=0; i < pb.nb_salles; i++){
		cl.insert(vars.Cr_Sal[cours][i]);
	}
	if(!cl.empty()){
		ecrit_clause_dimacs(out, cl);
	}
}

void cours_au_moins_un_enseignant(ostream& out, const probleme& pb, const lit_edt& vars, int cours){
	cls_t cl;
	for(int i=0; i < pb.nb_enseignants; i++){
		cl.insert(vars.Cr_En[cours][i]);
	}
	if(!cl.empty()){
		ecrit_clause_dimacs(out, cl);
		/*cout << "Cl -> ";
		for(cls_t::iterator it = cl.begin(); it != cl.end(); it++){
			cout << *it << " ";
		}
		cout << endl;*/
	}
}

void cours_exactement_une_fois(ostream& out, const probleme& pb, const lit_edt& vars){
	for(int i=0; i < pb.nb_cours; i++){ // Ces contraintes sont pour chaque cours
		cours_au_plus_une_fois(out, pb, vars, i);
		cours_au_moins_une_fois(out, pb, vars, i);
	}
}

void cours_exactement_une_salle(ostream& out, const probleme& pb, const lit_edt& vars){
	for(int i=0; i < pb.nb_cours; i++){ // Ces contraintes sont pour chaque cours
		cours_au_plus_une_salle(out, pb, vars, i);
		cours_au_moins_une_salle(out, pb, vars, i);
	}
}

void cours_exactement_un_enseignant(ostream& out, const probleme& pb, const lit_edt& vars){
	for(int i=0; i < pb.nb_cours; i++){ // Ces contraintes sont pour chaque cours
		cours_au_plus_un_enseignant(out, pb, vars, i);
		cours_au_moins_un_enseignant(out, pb, vars, i);
	}
}


void peut_enseigner_seulement(ostream& out, const probleme& pb, const lit_edt& vars, int enseignant, set<int> cours){
	for(int i=0; i < pb.nb_cours; i++){
		if(cours.find(i) == cours.end()){ // Si on ne trouve pas i, l'enseignant n'enseigne pas ce cours
			cls_t cl = {neg(vars.Cr_En[i][enseignant])};
			ecrit_clause_dimacs(out, cl);
		}
	}
}

void contrainte_enseigne(ostream& out, const probleme& pb, const lit_edt& vars){
	for(int i=0; i < pb.nb_enseignants; i++){
		peut_enseigner_seulement(out, pb, vars, i, pb.enseigne[i]);
	}
}

void peut_seulement_avoir_lieu_dans(ostream& out, const probleme& pb, const lit_edt& vars, int cours, set<int> salles){
	for(int i=0; i < pb.nb_salles; i++){
		if(salles.find(i) == salles.end()){ // Si on ne trouve pas i, le cours n'a pas lieu dans cette salle
			cls_t cl = {neg(vars.Cr_Sal[cours][i])};
			ecrit_clause_dimacs(out, cl);
		}
	}
}

void contraintes_salles_cours(ostream& out, const probleme& pb, const lit_edt& vars){
	for(int i=0; i < pb.nb_cours; i++){
		peut_seulement_avoir_lieu_dans(out, pb, vars, i, pb.salles[i]);
	}
}


// Retourne NonCr_En ou NonCr_Cx pour les cours les cours, créneaux où l'enseignant est indisponible
void indisponibilites_enseignant(ostream& out, const probleme& pb, const lit_edt& vars, int enseignant, set<int> creneaux_indisponibles){
	for(set<int>::iterator it = creneaux_indisponibles.begin(); it != creneaux_indisponibles.end(); it++){
		for(int i=0; i < pb.nb_cours; i++){
			// Si l'enseignant enseigne cours i et que le cours i est donné sur le créneau it
			if(pb.enseigne[enseignant].find(i) != pb.enseigne[enseignant].end()){ 
				cls_t cl = {neg(vars.Cr_En[i][enseignant]), neg(vars.Cr_Cx[i][*it])};
				ecrit_clause_dimacs(out, cl);
			}
		}
	}
}

void contrainte_indisponibilites(ostream& out, const probleme& pb, const lit_edt& vars){
	for(int i=0; i < pb.nb_enseignants; i++){
		indisponibilites_enseignant(out, pb, vars, i, pb.indisponibilites[i]);
	}
}


void ecrit_cnf_probleme(ostream& out, probleme& pb) {
    lit_edt vars;
	init_lits(pb, vars); // Initialisation de vars
    
    // Contraintes implicites
    cours_salle_creneau(out, pb, vars);
    cours_enseignant_creneau(out, pb, vars);
    cours_exactement_une_fois(out, pb, vars);
	cours_exactement_une_salle(out, pb, vars);
	cours_exactement_un_enseignant(out, pb, vars);
	
	// Contrainte explicites
	contrainte_enseigne(out, pb, vars);
	contraintes_salles_cours(out, pb, vars);
	contrainte_indisponibilites(out, pb, vars);
}

solution construit_solution(set<lit_t>& modele, probleme& pb) {
	solution sol;
	
	lit_edt vars;
	init_lits(pb, vars);
	
	sol.resize(pb.nb_cours); // Initialisation solution vide
	
	
	for(int i=0; i < pb.nb_cours; i++){
		int j; // Enseignant
		int k; // Salle
		int l; // Creneau
		
		for(j=0; modele.find(vars.Cr_En[i][j]) != modele.end() && j < pb.nb_enseignants; j++);
		for(k=0; modele.find(vars.Cr_Sal[i][k]) != modele.end() && k < pb.nb_salles; k++);
		for(l=0; modele.find(vars.Cr_Cx[i][l]) != modele.end() && l < pb.nb_creneaux; l++);
		affectation af = {j, i, k, l};
		sol[i] = af;
	}

	/*for(unsigned int i=0; i < sol.size(); i++){
		cout << "Enseignant : " << sol[i].enseignant <<" Cours : " << sol[i].cours << " Salle : " << sol[i].salle << " Creneau : " << sol[i].creneau << endl;   
	}*/
	
    return sol;
}

