from lexema import *

# Parser only for grammars
# This parser is explicited designed for this grammar:
#E  := T Ep
#Ep := + T Ep
#Ep := - T Ep
#Ep := lambda
#T  := F Tp
#Tp := * F Tp  |  /  F Tp  | lambda
#F  := ( E ) | num | id

class CATlexical_parser:
    def __init__(self):
        self.route_to_grammar = "";
        self.route_to_chain = "";

        self.standard_symbols = ["+", "-", "*", "/", "(", ")"]
        self.chain_container = []
        self.chain_lexema_container = []

    def set_chain(self, _route_to_chain):
        self.route_to_chain = _route_to_chain

    def read_chain(self):
        print("CAT (lexical):/ Escriba o pegue la cadena a validar(ctrl+v). Para finalizar presione ctrl+(z/d) (+ enter si es necesario)")
        return self.reader("")

    def reader(self, x_route):
        if x_route != "":
            print("Still no implemented")
        else:
            while True:
                try:
                    line = input()
                except EOFError:
                    break

                self.chain_container.append(line)


    def parser_symbols(self):
        if(len(self.chain_container) == 0):
            print("Nada para parsear")
        else:
            for individual_chain in self.chain_container:
                temp_member = ""
                processed_chain = []
                index = 0

                while(True):
                    temp_member = temp_member + individual_chain[index]

                    if temp_member in self.standard_symbols:
                        processed_chain.append(temp_member)
                        temp_member = ""

                    elif temp_member.isalpha():
                        while temp_member.isalpha():
                            index += 1
                            if (index >= len(individual_chain)):
                                temp_member += " "
                                break
                            temp_member = temp_member + individual_chain[index]
                        index = index - 1
                        temp_member = temp_member[:-1]
                        processed_chain.append(temp_member)
                        temp_member = ""

                    elif temp_member.isnumeric():
                        while temp_member.isnumeric():
                            index += 1
                            if index >= len(individual_chain):
                                temp_member += " "
                                break
                            temp_member = temp_member + individual_chain[index]
                        index = index - 1
                        temp_member = temp_member[:-1]
                        processed_chain.append(temp_member)
                        temp_member = ""

                    else:
                        temp_member = ""
                    index+=1
                    if(index >= len(individual_chain)):
                        break

                lexema_container = []
                for member in processed_chain:
                    if member.isalpha():
                        temp_lexema = lexema("id", member)
                        lexema_container.append(temp_lexema)
                    elif member.isnumeric():
                        temp_lexema = lexema("num", member)
                        lexema_container.append(temp_lexema)
                    else:
                        temp_lexema = lexema(member)
                        lexema_container.append(temp_lexema)

                self.chain_lexema_container.append(lexema_container)

    def get_parser_symbols(self):
        if len(self.chain_lexema_container) == 0:
            print("Sin lexema alguno")
        else:
            return self.chain_lexema_container


""" Ejemplos de cadena
num + num + num + num
( num    +num ) + ( num + num )
( num*) num
num *( num * num )
num +( num * num )
2 + (5 * 6) + 4
"""
if __name__ == "__main__":
    lexical_analyzer = CATlexical_parser()
    lexical_analyzer.read_chain()
    lexical_analyzer.parser_symbols()

    temp_con = lexical_analyzer.get_parser_symbols()
    for chain in temp_con:
        for eye in chain:
            print(eye.first(), " ", end="")
        print()
