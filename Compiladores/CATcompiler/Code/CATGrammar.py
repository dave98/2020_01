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

STMT ->
STMT -> SIMPLE_STMT SComma STMT
STMT -> SIMPLE_STMT SComma
STMT -> COMPOUND_STMT STMT
STMT -> COMPOUND_STMT

SIMPLE_STMT ->  STMTLIST
STMTLIST -> DEFDEF
STMTLIST -> TPDEF
STMTLIST -> TPDEF TPDEF_SUB
STMTLIST -> TPDEF Equal TEST

COMPOUND_STMT -> IF_STMT
COMPOUND_STMT -> WHILE_STMT
COMPOUND_STMT -> FOR_STMT

IF_STMT -> SI NAMED_EXPR ENTONCES DPoint STMT IF_STMT_2 IF_STMT_3

IF_STMT_2 ->
IF_STMT_2 -> SINO SI NAMED_EXPR ENTONCES DPoint STMT IF_STMT_2

IF_STMT_3 ->
IF_STMT_3 -> SINO ENTONCES DPoint STMT


NAMED_EXPR -> OR_TEST
OR_TEST -> AND_TEST
OR_TEST -> AND_TEST OO OR_TEST
AND_TEST -> NOT_TEST
AND_TEST -> NOT_TEST YY AND_TEST
NOT_TEST -> NO NOT_TEST
NOT_TEST -> COMPARISON
COMPARISON ->  EXPR
COMPARISON ->  EXPR ComOp EXPR
EXPR -> Atom
EXPR -> BoolVal

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
BoolVal -> 'True'
BoolVal -> 'False'
