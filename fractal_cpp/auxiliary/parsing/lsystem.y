%{
#include <string>
#include <iostream>
#include <cstdio>
%}
%require "3.2"
%language "c++"

%define api.token.constructor
%define api.value.type variant
%define parse.assert

%token <double> FLOAT
%token <std::string> NT
%token <std::string> DEFINE

%token SPACE
%token INIT_SECTION
%token DEFINE_SECTION
%token RULES_SECTION
%token FINAL_SECTION

%token PUSH
%token POP
%token ENDFACE
%token MOVE
%token DRAW
%token FACE
%token ROTATE

%%
%start code;
code:
    init_sec code_1 { std::cout << "Parsed correct\n"; }

code_1:
      define_sec rule_sec code_2
      | rule_sec code_2

code_2:
      %empty | final_sec

init_sec:
  INIT_SECTION content_start NT content_end

define_sec:
  DEFINE_SECTION content_start define_entities

define_entities:
  define_entity | define_entity define_entities

define_entity:
  DEFINE content_start define_expansions content_end

define_expansions:
  define_expansion maybe_spaces
  | define_expansion spaces define_expansions

define_expansion:
  NT | term | DEFINE

rule_sec:
  RULES_SECTION content_start rule_entities

rule_entities:
  rule_entity | rule_entity rule_entities

rule_entity:
  NT rule_entity_2
  | NT spaces FLOAT rule_entity_2

rule_entity_2:
  content_start rule_expansions content_end

rule_expansions:
  rule_expansion maybe_spaces
  | rule_expansion spaces rule_expansions

rule_expansion:
  NT | term | DEFINE

final_sec:
  FINAL_SECTION content_start final_rule_entities

final_rule_entities:
  final_rule_entity | final_rule_entity final_rule_entities

final_rule_entity:
  NT content_start final_rule_expansions content_end

final_rule_expansions:
  final_rule_expansion maybe_spaces 
  | final_rule_expansion spaces final_rule_expansions

final_rule_expansion:
  term | DEFINE

content_start:
  maybe_spaces ':' maybe_spaces

content_end:
  ';' maybe_spaces

spaces:
  maybe_spaces SPACE 

maybe_spaces:
  %empty | maybe_spaces SPACE 

term:
  rotation | move | draw | face | ENDFACE | PUSH | POP

move:
  MOVE | MOVE rand_entry

draw:
  DRAW | DRAW rand_entry

face:
  FACE | FACE rand_entry

rotation:
  ROTATE rand_entry

rand_entry:
  FLOAT


{};
%%

int main(int, char**) {
  yy::parser parse;
  return parse();
}
