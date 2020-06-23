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

DEFDEF -> Iden Equal Atom
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
STMTLIST -> TPDEF TPDEF_SUB Equal TEST


TPDEF_SUB -> Comma Iden
TPDEF_SUB -> Comma Iden TPDEF_SUB

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
Vari -> 'variable'
Iden -> 'identificador'
