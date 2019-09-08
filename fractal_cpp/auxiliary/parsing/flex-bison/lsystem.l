%{
//#include "lsystem.tab.hh"
//#include <iostream>

namespace my_parser{
  static void make_SPACE(){
  std::cout << "space\n";
  }
  static void make_ENDFACE(){
  std::cout << "endface!\n";
  }
}

%}
%option noyywrap nounput noinput batch debug


%%
[ \t\n] { my_parser::make_SPACE(); return 7;}
endf { my_parser::make_ENDFACE(); }
%%
//push { my_parser::make_PUSH(); }
//pop { my_parser::make_POP(); }
//start { my_parser::make_INIT_SECTION(); }
//define { my_parser::make_DEFINE_SECTION(); }
//rules { my_parser::make_RULES_SECTION(); }
//final { my_parser::make_FINAL_SECTION(); }
//r { my_parser::make_ROTATE(); }
//d { my_parser::make_DRAW(); }
//m { my_parser::make_MOVE(); }
//f {my_parser::make_FACE(); }
//_[A-Z]([a-zA-Z0-9])* { my_parser::make_DEFINE(std::string(yytext)); }
//[A-Z]([a-zA-Z0-9])* { my_parser::make_NT(std::string(yytext)); }
//(\-?[0-9]+)(\.[0-9]+)? { my_parser::make_FLOAT(std::stod(yytext)); }
//[\,\(\)\{\}] { yytext[0]; }
//%%

int main( int /* argc */, char** /* argv */ )
    {
    FlexLexer* lexer = new yyFlexLexer;
    while(lexer->yylex() != 0)
        ;
    return 0;
    }
