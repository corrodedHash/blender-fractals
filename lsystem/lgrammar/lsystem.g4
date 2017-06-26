grammar lsystem;

INT : [1-9][0-9]* | '0';
NEG_INT: '-' [1-9][0-9]*;

FLOAT : ( INT | NEG_INT ) ( '.' [0-9]+ )? ;

SPACE : ' ' | '\t';

NT : [A-Z]([a-z] | [A-Z] | [0-9])*;

CONTENT_END : ';' '\n' ? ;
CONTENT_START : SPACE * ':' SPACE * ;
SECTION_START : ':' '\n' ;
ROT : 'r' ;
MOVE : 'm' ;
PUSH : 'push' ;
POP : 'pop' ;

INIT_SECTION : 'init' ;
INIT_START : 'start' ;
RULES_SECTION : 'rules' ;
FINAL_SECTION : 'final' ;


terminal : ROT FLOAT ? | MOVE FLOAT ? | PUSH | POP ;

init_sec : INIT_SECTION SECTION_START init_start ;
init_start : INIT_START CONTENT_START NT CONTENT_END ;

rule_sec : RULES_SECTION SECTION_START rule_entity + ;
rule_entity : NT CONTENT_START rule_res CONTENT_END ;
rule_res : ( (NT | terminal) SPACE + ) * (NT | terminal) SPACE * ;

final_sec : FINAL_SECTION SECTION_START final_rule_entity + ;
final_rule_entity : NT CONTENT_START final_rule_res  CONTENT_END ;
final_rule_res : ( terminal SPACE + ) * terminal SPACE *;

code : init_sec rule_sec final_sec ? ;
