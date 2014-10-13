%{
#include "parser_defs.hpp"
%}
%skeleton "lalr1.cc"
%{
#include <iostream>
#include <string>
#include <sstream>
#include <set>
using namespace std;
 extern void set_yy_buffer(istream& input);
%}
%union{
  int i;
 };
%{ /* A DECLARER ABSOLUMENT APRES L'UNION */
  YY_DECL;
  vector<int> lus;
  probleme pb;
%}

%token <i> ENTIER 
%token ENSEIGNANTS SALLES CRENEAUX COURS ENSEIGNE SALLE POUR INDISPONIBLE COLON COMMA NL END


%start PROBLEME
%%

PROBLEME:
  HEADERS CONTRAINTES END {YYACCEPT;}
;

HEADERS:
  HEADER NL HEADERS {}
| HEADER NL {init_probleme(pb);}
;

HEADER:
  SALLES COLON ENTIER { pb.nb_salles = $3; } 
| CRENEAUX COLON ENTIER { pb.nb_creneaux = $3; } 
| COURS COLON ENTIER { pb.nb_cours = $3; }
| ENSEIGNANTS COLON ENTIER { pb.nb_enseignants = $3; }
;

CONTRAINTES:
  CONTRAINTE NL CONTRAINTES {}
| CONTRAINTE NL {}
;

CONTRAINTE:
  ENTIER ENSEIGNE COLON LISTE_ENTIERS { 
      pb.enseigne[$1].insert(lus.begin(),lus.end());
      lus.clear();
    }
| SALLES POUR ENTIER COLON LISTE_ENTIERS { 
      pb.salles[$3].insert(lus.begin(),lus.end());
      lus.clear(); 
    }
| ENTIER INDISPONIBLE COLON LISTE_ENTIERS { 
      pb.indisponibilites[$1].insert(lus.begin(),lus.end());
      lus.clear(); 
    }
;

LISTE_ENTIERS:  
  ENTIER COMMA { lus.push_back($1); } LISTE_ENTIERS {}
| ENTIER { lus.push_back($1); }
;
%%
void yy::parser::error(yy::location const& loc, std::string const& s){
    cerr<<endl<<loc<<": "<<s<<endl;
}

probleme lit_probleme() {
    yy::parser* pparser = new yy::parser();
    /* pparser->set_debug_level(1); */ 
    int i = pparser->parse();
    if (i == 0) {
        return pb;
    } else {
        probleme pb2;
        pb2.nb_cours = 0;
        pb2.nb_enseignants = 0;
        pb2.nb_creneaux = 0;
        pb2.nb_salles = 0;
        init_probleme(pb2);
        return pb2;
    }
}

probleme lit_probleme(istream & file) {
    set_yy_buffer(file);
    return lit_probleme();
}

probleme lit_probleme(const string & s) {
    istringstream is (s);
    set_yy_buffer(is);
    return lit_probleme();
}

