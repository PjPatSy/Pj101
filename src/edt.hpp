#ifndef EDT
#define EDT

#include "formule.hpp"
#include <vector>
#include <set>
#include <ostream>

using namespace std;

struct probleme {
  int nb_enseignants;
  int nb_cours;
  int nb_creneaux;
  int nb_salles;
  // pb.enseigne[i]={j1,j2,...}
  // correspond à la contrainte "i enseigne: j1, j2, ..."
  vector< set<int> > enseigne; 
  // pb.salles[i]={j1,j2,...} correspond 
  // à la contrainte "salles pour i: j1, j2, ..."
  vector< set<int> > salles;
  // pb.indisponibilites[i]={j1,j2,...} correspond à la 
  // contrainte "i indisponible: j1, j2, ..."
  vector< set<int> > indisponibilites;
};

void init_probleme(probleme& pb);

// Structure stockant les littéraux qui représentent un emploi du temps.
struct lit_edt {
  // le littéral Cr_En[i][j] est vrai si l'enseignant Ens_j enseigne
  // le cours Crs_i.
  vector< vector<lit_t> > Cr_En; 
  // le littéral Cr_Sal[i][j] est vrai si le cours Crs_i a lieu
  // dans la salle Sl_j.
  vector< vector< vector<lit_t> > > Cr_Sal;
  // le littéral Cr_Cx[i][j] est vrai si le cours Crs_i a lieu
  // au créneau Cx_j.
  vector< vector<lit_t> > Cr_Cx;
};

// A coder /////////////////////////////////////////////////////////////////////
// Initialise la structure contenant les littéraux qui représentent l'emploi du temps.
// On utilisera un compteur pour générer des variables représentées par un numéro.
void init_lits(const probleme& pb, lit_edt& vars);

// A coder /////////////////////////////////////////////////////////////////////
// Génère la clause qui exprime que deux cours ne peuvent avoir lieu
// en même temps au même endroit.
void cours_salle_creneau(ostream& out, const lit_edt& vars, int cours1, int cours2, int salle, int creneau);

// A coder /////////////////////////////////////////////////////////////////////
void cours_salle_creneau(ostream& out, const probleme& pb, const lit_edt& vars);

// A coder /////////////////////////////////////////////////////////////////////
void cours_au_moins_une_fois(ostream& out, const probleme& pb, const lit_edt& vars, int cours);

// A coder /////////////////////////////////////////////////////////////////////
void cours_au_plus_une_fois(ostream& out, const probleme& pb, const lit_edt& vars, int cours);

// A coder /////////////////////////////////////////////////////////////////////
void cours_exactement_une_fois(ostream& out, const probleme& pb, const lit_edt& vars);

// A coder /////////////////////////////////////////////////////////////////////
void cours_au_moins_une_salle(ostream& out, const probleme& pb, const lit_edt& vars, int cours);

// A coder /////////////////////////////////////////////////////////////////////
void cours_au_plus_une_salle(ostream& out, const probleme& pb, const lit_edt& vars, int cours);

// A coder /////////////////////////////////////////////////////////////////////
void cours_exactement_une_salle(ostream& out, const probleme& pb, const lit_edt& vars);

// A coder /////////////////////////////////////////////////////////////////////
void cours_au_moins_un_enseignant(ostream& out, const probleme& pb, const lit_edt& vars, int cours);

// A coder /////////////////////////////////////////////////////////////////////
void cours_au_plus_un_enseignant(ostream& out, const probleme& pb, const lit_edt& vars, int cours);

// A coder /////////////////////////////////////////////////////////////////////
void cours_exactement_un_enseignant(ostream& out, const probleme& pb, const lit_edt& vars);

// A coder /////////////////////////////////////////////////////////////////////
void cours_enseignant_creneau(ostream& out, const lit_edt& vars, int cours1, int cours2, int enseignant, int creneau);

// A coder /////////////////////////////////////////////////////////////////////
void cours_enseignant_creneau(ostream& out, const probleme& pb, const lit_edt& vars);

// A coder /////////////////////////////////////////////////////////////////////
void peut_enseigner_seulement(ostream& out, const probleme& pb, const lit_edt& vars, int enseignant, set<int> cours);

// A coder /////////////////////////////////////////////////////////////////////
void contrainte_enseigne(ostream& out, const probleme& pb, const lit_edt& vars);

// A coder /////////////////////////////////////////////////////////////////////
void peut_seulement_avoir_lieu_dans(ostream& out, const probleme& pb, const lit_edt& vars, int cours, set<int> salles);

// A coder /////////////////////////////////////////////////////////////////////
void contraintes_salles_cours(ostream& out, const probleme& pb, const lit_edt& vars);

// A coder /////////////////////////////////////////////////////////////////////
void indisponibilites_enseignant(ostream& out, const probleme& pb, const lit_edt& vars, int enseignant, set<int> creneaux_indisponibles);

// A coder /////////////////////////////////////////////////////////////////////
void contrainte_indisponibilites(ostream& out, const probleme& pb, const lit_edt& vars);

// A coder /////////////////////////////////////////////////////////////////////
void ecrit_cnf_probleme(ostream& out, probleme& pb);

// Représente un morceau de solution, i.e. l'affectation à un cours
// d'un enseignant, d'une salle et d'un créneau.
struct affectation {
  int enseignant; // numero de l'enseignant faisant cours
  int cours; // numero du cours
  int salle; // le numero de la salle
  int creneau; // le creneau concerné
};

typedef vector<affectation> solution;


// A coder /////////////////////////////////////////////////////////////////////
solution construit_solution(set<lit_t>& modele, probleme& pb);

/** Ecrit la solution sous forme d'un tableau HTML */
// Cette fonction est déjà codée
void affiche_solution_html(ostream& out, solution& sol, probleme& pb);

#endif
