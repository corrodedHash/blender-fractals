grammar lsystem;

FLOAT : ( INT | NEG_INT ) ( '.' [0-9]+ )? ;

INT : [1-9][0-9]* | '0';
NEG_INT: '-' [1-9][0-9]*;

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

rotation : ROT SPACE * ( '(' ( ( SPACE * FLOAT SPACE * ',' ) ?  SPACE * FLOAT SPACE * ',' ) ? SPACE * FLOAT SPACE * ')' | FLOAT | );
move: MOVE FLOAT ?;
push: PUSH;
pop: POP;

term : rotation | move | push | pop;

init_sec : ( INIT_SECTION SECTION_START ) ? init_start ;
init_start : INIT_START CONTENT_START NT CONTENT_END ;

rule_sec : RULES_SECTION SECTION_START rule_entity + ;
rule_entity : NT CONTENT_START rule_res CONTENT_END ;
rule_res : ( (NT | term) SPACE + ) * (NT | term) SPACE * ;

final_sec : FINAL_SECTION SECTION_START final_rule_entity + ;
final_rule_entity : NT CONTENT_START final_rule_res  CONTENT_END ;
final_rule_res : ( term SPACE + ) * term SPACE *;

code : init_sec rule_sec final_sec ? ;
