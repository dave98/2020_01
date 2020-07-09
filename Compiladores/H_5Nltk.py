import nltk
nltk.app.rdparser()
print("Hola mundo")

"""
principal ( ) > retorna identificador : variable identificador , identificador , identificador , identificador = numero ;
principal ( ) > retorna identificador : variable identificador = numero ;
principal ( ) > retorna identificador : identificador /= numero ;
principal ( ) > retorna identificador : identificador ++ ;
principal ( variable identificador , variable identificador = numero ) > retorna identificador : variable identificador ; variable identificador = numero ; identificador ++ ; identificador += numero ;
principal ( ) > retorna identificador : identificador ++ ; variable identificador = numero ;
principal ( ) > retorna identificador : identificador = ( numero + numero ) * identificador ; identificador = ( numero - identificador + numero) * identificador ;

principal ( ) > retorna identificador : si identificador entonces : variable identificador ; identificador ++ ;

//
if_stmt: 'if' namedexpr_test ':' suite ('elif' namedexpr_test ':' suite)* ['else' ':' suite]
while_stmt: 'while' namedexpr_test ':' suite ['else' ':' suite]
for_stmt: 'for' exprlist 'in' testlist ':' [TYPE_COMMENT] suite ['else' ':' suite]


STMT ->
STMT -> SIMPLE_STMT SComma STMT
STMT -> COMPOUND_STMT SComma STMT


IF_STMT -> IF_COMPLETE
IF_STMT -> IF_INCOMPLETE

IF_COMPLETE -> SI NAMED_EXPR ENTONCES DPoint IF_COMPLETE SINO ENTONCES DPoint IF_COMPLETE
IF_COMPLETE -> SIMPLE_STMT
IF_IMCOMPLETE -> SI NAMED_EXPR ENTONCES DPoint IF_STMT
IF_INCOMPLETE -> SI NAMED_EXPR ENTONCES DPoint IF_COMPLETE SINO ENTONCES DPoint IF_INCOMPLETE


"""
