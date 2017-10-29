lexer grammar lsystemLexer;

FLOAT : ( INT | NEG_INT ) ( '.' [0-9]+ )? ;

INT : [1-9][0-9]* | '0';
NEG_INT: '-' [1-9][0-9]*;

SPACE : ' ' | '\t';
SEP : ',';
PAR_OPEN : '(';
PAR_CLOSE : ')';
BR_OPEN : '{';
BR_CLOSE : '}';

NT : [A-Z]([a-z] | [A-Z] | [0-9])*;
DEFINE : '_' NT ;

CONTENT_END : ';' '\n' ? ;
CONTENT_START : SPACE * ':' SPACE * ;
SECTION_START : ':' '\n' ;
ROT : 'r' ;
DRAW : 'd' ;
MOVE : 'm' ;
FACE: 'f' ;
ENDFACE: 'endf' ;
PUSH : 'push' ;
POP : 'pop' ;

INIT_SECTION : 'init' ;
INIT_START : 'start' ;
DEFINE_SECTION : 'define' ;
RULES_SECTION : 'rules' ;
FINAL_SECTION : 'final' ;
