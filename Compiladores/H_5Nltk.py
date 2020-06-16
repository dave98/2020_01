import nltk
nltk.app.rdparser()
print("Hola mundo")

"""
S-> PRIN PARAMETERS DPoint
PARAMETERS -> LPar RPar
PARAMETERS -> LPar ARGLIST RPar
ARGLIST -> TFDEF
ARGLIST -> TFDEF Equal TEST
ARGLIST -> ARGLIST Comma ARGLIST
ARGLIST ->
STMT -> SIMPLE_STMT
STMT -> COMPOUND_STMT
SIMPLE_STMT -> EXPR_STMT
EXPR_STMT -> LIST_EXPR
LIST_EXPR -> TEST
LIST_EXPR -> TEST Comma TEST
LIST_EXPR ->

TFDEF -> 'variable'
TEST -> 'number'
PRIN -> 'principal'
LPar -> '('
RPar -> ')'
Comma -> ','
DPoint -> ':'
Equal -> '='
"""

"""
    principal ( variable = number , variable = number , variable ) :
"""
