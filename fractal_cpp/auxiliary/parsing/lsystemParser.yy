%{
#include <string>
%}

%union {
  float fval;
  int ival;
  std::string sval;
}

%token <fval> FLOAT
%token <ival> INT
%token <ival> NEG_INT
%token <sval> NT
%token <sval> DEFINE

%token SPACE
%token CONTENT_END
%token CONTENT_START
%token SECTION_START
%token INIT_SECTION
%token INIT_START
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
code:
    init_sec code_1

code_1:
      define_sec rule_sec code_2
      | rule_sec code_2

code_2:
      %empty | final_sec

init_sec:
  INIT_SECTION SECTION_START init_start
  | init_start

init_start:
  INIT_START CONTENT_START NT CONTENT_END

define_sec:
  DEFINE_SECTION SECTION_START define_entity define_entities

define_entities:
  %empty | define_entity define_entities

define_entity:
  DEFINE CONTENT_START define_expansion define_expansions CONTENT_END

define_expansions:
  %empty | spaces define_expansion define_expansions

define_expansion:
  NT | term | DEFINE

rule_sec:
  RULES_SECTION SECTION_START rule_entity rule_entities

rule_entities:
  %empty | rule_entity rule_entities

rule_entity:
  NT rule_entity_2
  | NT spaces FLOAT rule_entity_2

rule_entity_2:
  CONTENT_START rule_expansion rule_expansions CONTENT_END

rule_expansions:
  %empty | spaces rule_expansion rule_expansions

rule_expansion:
  NT | term | DEFINE

final_sec:
  FINAL_SECTION SECTION_START final_rule_entity final_rule_entities

final_rule_entities:
  %empty | final_rule_entity final_rule_entities

final_rule_entity:
  NT CONTENT_START final_rule_expansion final_rule_expansions CONTENT_END

final_rule_expansions:
  %empty | spaces final_rule_expansion final_rule_expansions

final_rule_expansion:
  term | DEFINE

spaces:
  SPACE maybe_spaces

maybe_spaces:
  %empty | SPACE maybe_spaces

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
