%{
#include "parser_defs.hpp"
#include "parser.tab.hpp"
#include <iostream>
YY_DECL;
#define yyterminate() return yy::parser::token::END
 istream * lex_input;
#define YY_INPUT(buf,result,max_size) \
 { \
   int c = lex_input->get(); \
   result = (c == -1) ? YY_NULL : (buf[0] = c, 1); \
 } 
%}

ENTIER       -?[0-9]+
NL           [\n\r \t]*[\n][\n\r \t]*
%%
[ \t\r]
{NL} {return yy::parser::token::NL; }
"enseignants"  {return yy::parser::token::ENSEIGNANTS; }
"salles" {return yy::parser::token::SALLES;}
"creneaux" {return yy::parser::token::CRENEAUX;}
"cours" {return yy::parser::token::COURS;}
"enseigne" {return yy::parser::token::ENSEIGNE;}
"salle" {return yy::parser::token::SALLE;}
"pour" {return yy::parser::token::POUR;}
"indisponible" {return yy::parser::token::INDISPONIBLE;}
":" {return yy::parser::token::COLON;}
"," {return yy::parser::token::COMMA;}
{ENTIER} {pyylval->i=atoi(yytext);return yy::parser::token::ENTIER;}
%%
int yywrap(){return 1;}

YY_BUFFER_STATE current_state;

void set_yy_buffer(istream & input) {
  lex_input = &input;
}

