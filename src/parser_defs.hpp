#ifndef ParserDefs 
#define ParserDefs
#include <stdio.h>
#include "formule.hpp"
#include "edt.hpp"
#define YY_DECL yy::parser::token_type yylex (yy::parser::semantic_type* pyylval)

void from_to(int from, int to, vector<int>& lus);

#endif
