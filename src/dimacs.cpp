#include "dimacs.hpp"
#include <string>
#include <sstream>

lit_t fromDimacs(int d) {
  return var2lit( abs(d) - 1,  d > 0 );
}

int toDimacs(lit_t l) {
  return (l/2 +1) * ((l%2 == 0) ? 1 : -1);
}

void lit_ligne_dimacs(istream& input, dimacs & data) {
  cls_t values;
  int n;
  do {
    input >> n;
    if (n != 0) {
      values.insert(fromDimacs(n));
      data.nbVars = max(data.nbVars, abs(n));
    }
  } while(n != 0 && !input.eof());
  data.cnf.push_back(values);
}

void lit_dimacs(istream& input, dimacs & data) {
  string line;
  while (!input.eof()) {
    getline(input,line);
    if (line.length() > 0 && line[0] != 'p' && line[0] != 'c') {
      istringstream buffer(line);
      lit_ligne_dimacs(buffer,data);
      getline(input,line);
    }
  }
}

set<lit_t> lit_resultat_dimacs(istream& input) {
  string line;
  set<lit_t> result;
  input >> line;
  if (line == "SAT") {
    int n;
    do {
      input >> n;
      if (n != 0) {
        result.insert(fromDimacs(n));
      }
    } while(n != 0 && !input.eof());
  }
  return result;
}

void ecrit_clause_dimacs(ostream& output, const cls_t& clause) {
  for(auto it = clause.cbegin(); it != clause.cend(); ++it) {
    output << toDimacs(*it) << " ";
  }
  output << 0 << endl;
}
