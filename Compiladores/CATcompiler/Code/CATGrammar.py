S -> PRINCIPAL STMT

PRINCIPAL -> Prin PARAMETERS Arrow Return Atom DPoint

PARAMETERS -> LPar RPar
PARAMETERS -> LPar ARGLIST RPar

ARGLIST -> ARGEXPR
ARGLIST -> ARGEXPR Comma ARGLIST

ARGEXPR -> TPDEF
ARGEXPR -> TPDEF Equal TEST
ARGEXPR ->

TPDEF -> Vari Iden
TEST -> Atom
TEST -> OP_STMT

TPDEF_SUB -> Comma Iden
TPDEF_SUB -> Comma Iden TPDEF_SUB

DEFDEF -> Iden Equal TEST
DEFDEF -> Iden SEqual Atom
DEFDEF -> Iden AAsig

STMT -> SIMPLE_STMT SComma STMT
STMT -> SIMPLE_STMT SComma
STMT -> COMPOUND_STMT SComma STMT
STMT -> COMPOUND_STMT SComma

SIMPLE_STMT ->  STMTLIST
STMTLIST -> DEFDEF
STMTLIST -> TPDEF
STMTLIST -> TPDEF TPDEF_SUB
STMTLIST -> TPDEF Equal TEST

COMPOUND_STMT -> IF_STMT
COMPOUND_STMT -> WHILE_STMT
COMPOUND_STMT -> FOR_STMT

IF_STMT -> IF_COMPLETE
IF_STMT -> IF_INCOMPLETE

IF_COMPLETE -> SI NAMED_EXPR ENTONCES DPoint IF_COMPLETE SINO ENTONCES DPoint IF_COMPLETE
IF_COMPLETE -> SIMPLE_STMT
IF_IMCOMPLETE -> SI NAMED_EXPR ENTONCES DPoint IF_STMT
IF_INCOMPLETE -> SI NAMED_EXPR ENTONCES DPoint IF_COMPLETE SINO ENTONCES DPoint IF_INCOMPLETE

NAMED_EXPR -> OR_TEST
OR_TEST -> AND_TEST
OR_TEST -> AND_TEST OO OR_TEST
AND_TEST -> NOT_TEST
AND_TEST -> NOT_TEST YY AND_TEST
NOT_TEST -> NO NOT_TEST
NOT_TEST -> COMPARISON
COMPARISON ->  EXPR
COMPARISON ->  EXPR ComOp EXPR


if_stmt: 'if' namedexpr_test ':' suite ('elif' namedexpr_test ':' suite)* ['else' ':' suite]
while_stmt: 'while' namedexpr_test ':' suite ['else' ':' suite]
for_stmt: 'for' exprlist 'in' testlist ':' [TYPE_COMMENT] suite ['else' ':' suite]

OP_STMT -> E
E -> T Ep
Ep -> BOp T Ep
Ep ->
T -> F Tp
Tp -> SOp F Tp
Tp ->
F -> LPar E RPar
F -> Atom

Prin -> 'principal'
Arrow -> '>'
Return -> 'retorna'
Atom -> 'numero'
Atom -> 'identificador'
DPoint -> ':'
LPar -> '('
RPar -> ')'
Equal -> '='
SEqual -> '+='
SEqual -> '-='
SEqual -> '*='
SEqual -> '/='
AAsig -> '++'
AAsig -> '--'
Comma -> ','
SComma -> ';'
BOp -> '+'
BOp -> '-'
SOp -> '*'
SOp -> '/'
Vari -> 'variable'
Iden -> 'identificador'

SI -> 'si'
SINO -> 'sino'
MIENTRAS -> 'mientras'
PARA -> 'para'
ENTONCES -> 'entonces'
YY -> 'yy'
OO -> 'oo'
NO -> 'no'

ComOp -> '=='
ComOp -> '>='
ComOp -> '<='
ComOp -> '<>'
ComOp -> '!='
