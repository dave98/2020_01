"""
Created on SAT MAY 09 07:02:23 2020
GRAMMAR READER
@author: DAVE
"""

"""   --> Entrada <-- Diseñar código capaz de procesar una gramática (Procesarla, no entenderla)
E  := T Ep
Ep := + T Ep
Ep := - T Ep
Ep := lambda
T  := F Tp
Tp := * F Tp  |  /  F Tp  | lambda
F  := ( E ) | num | id
"""



class CATproduction:
    def __init__(self):
        self.grammar_dictionary = {}

class CATgrammar:
    def __init__(self):
        self.raw_grammar = []

        self.productions = CATproduction()
        self.terminals = []
        self.non_terminals = []

        self.component_separator = ""
        self.right_component_separator = ""

    def reader(self):
        print("CAT:/ Escriba o pegue la gramatica(ctrl+v). Para finalizar presione ctrl+(z/d) (+ enter si es necesario)")
        while True:
            try:
                line = input()
            except EOFError:
                break
            self.raw_grammar.append(line)

    def _get_non_terminals(self): # Intern class function, don't use it.
        for dictionary_key in self.productions.grammar_dictionary:
            self.non_terminals.append(dictionary_key)


    def _get_terminals(self): # Intern class function, don't use it.
        for dictionary_key in self.productions.grammar_dictionary:
            for dictionary_value in self.productions.grammar_dictionary[dictionary_key]:
                disgregated = dictionary_value.split()
                for i in disgregated:
                    if not self.productions.grammar_dictionary.get(i):
                        self.terminals.append(i)

    def process_grammar(self, component_separator = ":=", right_component_separator = "|" ): # Use only if we put something in raw data
        self.component_separator = component_separator
        self.right_component_separator = right_component_separator
        print("CAT:/ Procesando gramática...")
        for line in self.raw_grammar:  # Separator is used to split left elements from right elements, by default is ":=" but could be anything
            line_tuple = line.split(component_separator) # Left member = line_tuple[0], Right members = line_tuple[1:]
            # SPLITTING
            line_left_member = line_tuple[0].replace(" ", "")
            if not self.productions.grammar_dictionary.get(line_left_member): # WARNING: Need a interface. Now is using direct modification
                self.productions.grammar_dictionary[line_left_member] = []


            line_rigth_member = line_tuple[1].split(right_component_separator)
            for component_in_right_member in line_rigth_member: # WARNING: Should apply a review to see if left member is in dictionary
                self.productions.grammar_dictionary[line_left_member].append(component_in_right_member.strip())

        self._get_terminals()
        self._get_non_terminals()

    def print_raw_grammar(self):
        print("Gramatica Bruta: ")
        for gram in self.raw_grammar:
            print(gram)

    def __str__(self):
        print("CAT:/ Mostrando...")

        print("CAT:/ No terminales: ")
        print("\t" ,self.non_terminals)

        print("CAT:/ Terminales: ")
        print("\t", self.terminals)

        print("CAT:/ Construyendo gramatica a partir de diccionario...")
        for dictionary_key in self.productions.grammar_dictionary:
            sentence = "\t" + str(dictionary_key) + " " + self.component_separator + " "
            for dictionary_value in self.productions.grammar_dictionary[dictionary_key]:
                sentence = sentence + str(dictionary_value) + " " + self.right_component_separator + " "

            print(sentence)
        return "\n"

# ---------------------------  START HERE ----------------------------------------
my_grammar = CATgrammar()
my_grammar.reader() # Just type or paste the grammar
my_grammar.process_grammar(); #  IN DEFAULT: process_grammar(component_separator=":=", right_component_separator="|")
                              #  Set according grammar separators
print(my_grammar)
