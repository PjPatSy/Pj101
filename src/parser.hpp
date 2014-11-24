#ifndef Parser
#define Parser
#include "formule.hpp"
#include "edt.hpp"
#include <iostream>
/** Remplit une structure probleme avec le problème lu sur un flux
    d'entrée */
probleme lit_probleme(istream & input);

/** Remplit une structure probleme avec le problème lu dans la chaîne
    de caractères passée en argument */
probleme lit_probleme(const string & s);

#endif
