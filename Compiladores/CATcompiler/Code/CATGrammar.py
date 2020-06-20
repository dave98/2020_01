S -> PRINCIPAL STMT

PRINCIPAL -> Prin PARAMETERS Arrow Return Atom DPoint

PARAMETERS -> LPar RPar
PARAMETERS -> LPar ARGLIST RPar

"""
ARGLIST -> TPDEF Equal TEST
ARGLIST -> TPDEF
ARGLIST ->
ARGLIST -> ARGLIST Comma ARGLIST
"""

ARGLIST -> TPDEF Equal TEST _ARGLIST
ARGLIST -> TPDEF _ARGLIST
ARGLIST -> _ARGLIST

_ARGLIST ->


TPDEF -> Vari Iden
TEST -> Atom

STMT ->
STMT -> SIMPLE_STMT STMT
STMT -> COMPOUND_STMT STMT

SIMPLE_STMT ->  STMTLIST

STMTLIST -> TPDEF Equal TEST
STMTLIST -> TPDEF
STMTLIST -> STMTLIST Comma STMTLIST

Prin -> 'principal'
Arrow -> '>'
Return -> 'retorna'
Atom -> 'numero'
Atom -> 'identificador'
DPoint -> ':'
LPar -> '('
RPar -> ')'
Equal -> '='
Comma -> ','
Vari -> 'variable'
Iden -> 'identificador'
