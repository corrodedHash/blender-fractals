grammar lsystem;

INT : [1-9][0-9]* | '0';
FLOAT : '0' '.' [0-9]+ | INT ('.' [0-9])? ; 
NT : [A-Z]([a-z] | [A-Z] | [0-9])*;
ROTATION : 'r' FLOAT ?;
FORWARD : 'f' FLOAT ? ;
PUSH : 'push' ;
POP : 'pop' ;
TERMINAL : (ROTATION | FORWARD | PUSH | POP) ;



init_sec : init_start ;
init_start : 'start' ':' ' ' NT ';' '\n' ;

rule_sec : 'rules:\n' rule_entity + ;
rule_entity : NT ':' ' ' rule_res ';' '\n' ;
rule_res : ( (NT | TERMINAL) ' ' ) * (NT | TERMINAL) ;

final_sec : 'final:\n' final_rule_entity + ;
final_rule_entity : NT ':' final_rule_res  ';' ;
final_rule_res : ( TERMINAL ' ' ) * TERMINAL ;


//code : init_sec rule_sec final_sec ? ;
code: (ROTATION | FORWARD | PUSH | POP) *;
