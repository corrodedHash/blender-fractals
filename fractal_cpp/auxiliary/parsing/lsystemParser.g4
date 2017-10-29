parser grammar lsystemParser;

options {
	tokenVocab = lsystemLexer;
}

probability : FLOAT ;

rand_entry : FLOAT | BR_OPEN SPACE * FLOAT SPACE * SEP SPACE * FLOAT SPACE *  BR_CLOSE ;

rotation : ROT ( PAR_OPEN ( ( SPACE * rand_entry SPACE * SEP ) ?  SPACE * rand_entry SPACE * SEP ) ? SPACE * rand_entry SPACE * PAR_CLOSE | rand_entry );
move: MOVE rand_entry ?;
draw: DRAW rand_entry ?;
face: FACE rand_entry ?;
endface: ENDFACE ;
push: PUSH ;
pop: POP ;

term : rotation | move | draw | face | endface | push | pop;
non_term : NT ;
define_term: DEFINE ;

init_sec : ( INIT_SECTION SECTION_START ) ? init_start ;
init_start : INIT_START CONTENT_START non_term CONTENT_END ;

define_sec : DEFINE_SECTION SECTION_START define_entity + ;
define_entity : define_term CONTENT_START define_res CONTENT_END ;
define_res : ( (non_term | term | define_term) SPACE + ) * (non_term | term | define_term) SPACE * ;

rule_sec : RULES_SECTION SECTION_START rule_entity + ;
rule_entity : non_term (SPACE +  probability)? CONTENT_START rule_res CONTENT_END ;
rule_res : ( (non_term | term | define_term ) SPACE + ) * (non_term | term | define_term) SPACE * ;

final_sec : FINAL_SECTION SECTION_START final_rule_entity + ;
final_rule_entity : non_term CONTENT_START final_rule_res  CONTENT_END ;
final_rule_res : ( ( term | define_term ) SPACE + ) * ( term | define_term ) SPACE *;

code : init_sec define_sec ? rule_sec final_sec ? EOF;
