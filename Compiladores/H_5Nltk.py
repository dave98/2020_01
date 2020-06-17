import nltk
nltk.app.rdparser()
print("Hola mundo")

"""
S -> PRIN PARAMETERS DPoint STMT

PARAMETERS -> LPar RPar
PARAMETERS -> LPar ARGLIST RPar

ARGLIST -> TFDEF
ARGLIST -> TFDEF Equal TEST
ARGLIST -> ARGLIST Comma ARGLIST
ARGLIST ->

TFDEF -> VARI IDEN

STMT -> SIMPLE_STMT
STMT -> COMPOUND_STMT

SIMPLE_STMT -> EXPR_STMT

EXPR_STMT -> LIST_EXPR

LIST_EXPR -> TEST
LIST_EXPR -> TEST Comma TEST
LIST_EXPR ->

TEST -> Atom

VARI -> 'variable'
IDEN -> 'identificador'
Atom -> 'number'
PRIN -> 'principal'
LPar -> '('
RPar -> ')'
Comma -> ','
DPoint -> ':'
Equal -> '='
"""

"""
    principal ( variable identificador = number , variable identificador = number , variable identificador ) :
"""


"""
In the beginning:
    Introduction                                         1
    Who I am                                             2
    Who I think you are                                  3          OBVIAR
    The problem                                          3

Go big or go home                                          ---------------------------
    Introduciendo Kubernets                              5 ---------------------------
    Aplications VS Services                              6           Parte 1
    The master and its minions                           7
    Pods                                                 10 --------------------------
    Volumes                                              12 --------------------------
    From brick to house                                  14

Organize, grow, go                                                   Parte 2
    Better lives through labels annotations and selector 15
    Replication controllers                              18
        The gestalt of a Replication Controller          19 --------------------------
        Scheduling != Scaling                            20 --------------------------
    Services                                             21          Parte 3
    Health checking                                      27 --------------------------
    Moving on                                            30

Here, there and everywhere                                           Parte 4
    Starting small with your local machine               32
    Bare metal                                           33
    Virtual metal (IaaS on a Public Cloud)               33 ---------------------------
    Other configurations                                 34 ---------------------------
    Fully managed                                        35          OBVIAR
"""
