%{
#include "lsystem.tab.hh"
#include <string>
//%option nodefault
# define YY_DECL \
  yy::parser::symbol_type yylex ()
%}

%option c++
%option noyywrap

%%
[ \t\n] { return yy::parser::make_SPACE(); }
endf { return yy::parser::make_ENDFACE(); }
push { return yy::parser::make_PUSH(); }
pop { return yy::parser::make_POP(); }
start { return yy::parser::make_INIT_SECTION(); }
define { return yy::parser::make_DEFINE_SECTION(); }
rules { return yy::parser::make_RULES_SECTION(); }
final { return yy::parser::make_FINAL_SECTION(); }
r { return yy::parser::make_ROTATE(); }
d { return yy::parser::make_DRAW(); }
m { return yy::parser::make_MOVE(); }
f {return yy::parser::make_FACE(); }
_[A-Z]([a-zA-Z0-9])* { return yy::parser::make_DEFINE(std::string(yytext)); }
[A-Z]([a-zA-Z0-9])* { return yy::parser::make_NT(std::string(yytext)); }
(\-?[0-9]+)(\.[0-9]+)? { return yy::parser::make_FLOAT(std::stod(yytext)); }
[\,\(\)\{\}] { return yytext[0]; }
%%
