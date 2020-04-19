"""
@author: Jose David Mamani Vilca
"""
# Construir un analizador léxico utilizando funciones.
c_types = ["Entero", "Variable", "Operador", "Undefined"]
c_operators = ["+", "-", "/", "%", "&&", "*", "=    "]


class CatToken:
    def __init__(self, i_value = "zero", i_type = c_types[3], i_pos = -1):
        self.c_value = i_value # Palabra
        self.c_type = i_type # Indice
        self.c_pos = i_pos # Token position

    def __str__(self): # Descripción de impresion
        return "Token[" + self.c_value + "]: pos = " + str(self.c_pos) + ", tipo = " + self.c_type

class CatCompiler:
    """docstring for CatCompiler."""
    def __init__(self):
        self.original_expression = ""
        self.initial_token_list = [] # Both have the same size always, can be erased since the information is in cat_tokens
        self.initial_types_list = []
        self.cat_tokens = [] # Works with class CatToken

    def __str__(self):
        print("ORIGINAL: ", self.original_expression)
        for token in self.cat_tokens:
            print(token)
        return ""a

    def cleaner(self): # Clean class
        self.original_expression = ""
        del self.initial_token_list[:]
        del self.initial_types_list[:]
        del self.cat_tokens[:]

    def universal_recognizer(self, incoming_message, position): # Reconoce entre variables, numeros y operadores
        self.initial_token_list.append(incoming_message)
        if self.number_recognizer(incoming_message):
            self.initial_types_list.append(c_types[0])
            self.cat_tokens.append(CatToken(incoming_message, c_types[0] ,position))
        elif self.variable_recognizer(incoming_message):
            self.initial_types_list.append(c_types[1])
            self.cat_tokens.append(CatToken(incoming_message, c_types[1] ,position))
        elif self.operator_recognizer(incoming_message):
            self.initial_types_list.append(c_types[2])
            self.cat_tokens.append(CatToken(incoming_message, c_types[2] ,position))
        else:
            self.initial_types_list.append(c_types[3])
            self.cat_tokens.append(CatToken(incoming_message, c_types[3] ,position))

    # We can diferentiate just in one function, but for exercises requirementes we are splitting functions in two parts
    def number_recognizer(self, incoming_message): # Reconoce numeros
        if incoming_message.isnumeric(): return True
        else: return False

    def variable_recognizer(self, incoming_message): # Reconoce variables
        if incoming_message[0].isalpha(): return True  # Variables starts with an alphabet letter (Upper or Lower)
        else: return False

    def operator_recognizer(self, incoming_message): # Not really necessary, just to kept clear code
        if not incoming_message.isalnum(): return True
        else:  return False

    def tokens_splitter(self, incoming_message, show_extra_information = False): # Splitting tokens by nonalphanumeric symbols
        self.cleaner() # Delete previous data in each new consult
        self.original_expression = incoming_message
        actual_token = "" # Temp
        incoming_message = incoming_message.replace(" ", "") # Delete blank spaces
        temp_pos = 0 # Just to kept token postion!! (characters in string are not relevant) <----------------

        for token in incoming_message:
            if token.isalnum():
                actual_token = actual_token + token # Alphanumeric pool
            else:                                   # Operator founded
                self.universal_recognizer(actual_token, temp_pos) # Alphanumeric
                self.universal_recognizer(token, temp_pos + 1) # Operators
                actual_token = ""
                temp_pos += 2

        if (actual_token != ""): # Last token if its lphanumeric
            self.universal_recognizer(actual_token, temp_pos)

        if show_extra_information:
            print(self.initial_token_list)
            print(self.initial_types_list)

#++++++++++++++++++++++++++++++ START HERE +++++++++++++++++++++++++++++++++++++
#++++++++++++++++++++++ Descomentar para ejecutar ++++++++++++++++++++++++++++++
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
cookie = CatCompiler() # Universal Class, almacena la linea y todos los tokens en ella
# +++++++++++++++ Exercise 1, 2, 3 +++++++++++++++++++++++++++
"""
# Reconoce una linea y los separa en variables, numeros y operadores (acorde a las reglas descritas)
# Funciones "reconoceNumeros", "reconoceVariable" en 54, 58.
linea = "variable = tmp0 + 20"
#linea = "C = A + variable1"
#linea = "60   /    5 + 3 - 0"
#linea = "4*3-8"
cookie.tokens_splitter(linea, True) # line 66: Entrada, devolver tratamiento de datos
"""
# +++++++++++++++ Exercise 4, 5 +++++++++++++++++++++++++++
# Class Token en ln 9, posee método implementado para imprimir clase
# Metodo para imprimir conjunto de tokens implementado en ln 26
linea = "variable = tmp0 + 20"
#linea = "C = A + variable1"
#linea = "60   /    5 + 3 - 0"
#linea = "4*3-8"
cookie.tokens_splitter(linea)
print(cookie) # ln 26
