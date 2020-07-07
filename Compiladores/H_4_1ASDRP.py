"""
Created on SAT MAY 09 07:02:23 2020
GRAMMAR READER
@author: DAVE
"""

import os

class CATsintatic_table:
    def __init__(self):
        self.table = {} # dictionary of dictionary

    def insert(self, key1, key2, inter_val):
        key1 = key1.strip()
        key2 = key2.strip()
        inter_val = inter_val.strip()
        if not self.table.get(key1):
            self.table[key1] = {}
            self.table[key1][key2] = inter_val

        elif not self.table[key1].get(key2):
            self.table[key1][key2] = inter_val

        else: # No actualizamos la tabla
            pass

    def get_from_keys(self, key1, key2):
        if not self.table.get(key1) or not self.table[key1].get(key2):
            return "ERROR"
        else:
            return self.table[key1][key2]

    def get(self, key1, key2):
        try:
            print("[" + str(key1) + "][" + str(key2) + "] = [" + str(self.table[key1][key2]) + "]")
        except:
            if not self.table.get(key1):
                print("[" + str(key1) + "]", "no esta definido en la tabla")
            else:
                print("No se ha definido un valor para " + "[" + str(key1) + "][" + str(key2) + "]")


    def format_matrix(self, header, matrix, top_format, left_format, cell_format, row_delim, col_delim):
        table = [[''] + header] + [row for name, row in zip(header, matrix)]
        table_format = [['{:^{}}'] + len(header) * [top_format]] + len(matrix) * [[left_format] + len(header) * [cell_format]]
        col_widths = [max( len(format.format(cell, 0)) for format, cell in zip(col_format, col)) for col_format, col in zip(zip(*table_format), zip(*table))]
        return row_delim.join( col_delim.join( format.format(cell, width) for format, cell, width in zip(row_format, row, col_widths)) for row_format, row in zip(table_format, table))

    def __str__(self):
        print("TABLE")

        total_terminals = []
        total_terminals.append(" ")
        m_matrix = []
        for x in self.table:
            total_terminals = total_terminals + list(self.table[x].keys())
        total_terminals = [i for n, i in enumerate(total_terminals) if i not in total_terminals[:n]]


        for x in self.table:
            t_matrix = []
            t_matrix.append(x)
            for i in total_terminals:
                if not self.table[x].get(i):
                    t_matrix.append(" ")
                else:
                    t_matrix.append(self.table[x][i])
            m_matrix.append(t_matrix)

        print(self.format_matrix(total_terminals, m_matrix, '{:^{}}', '{:<{}}', '{:>{}}', '\n', ' | '))
        return ""


class CATproduction:
    def __init__(self):
        self.grammar_dictionary = {}

    def is_usable(self):
        if not self.grammar_dictionary.keys():
            return False
        else:
            return True

    # key representan los nodos no terminales
    def is_key_on_dictionary(self, key):
        if not self.grammar_dictionary.get(key):
            return False
        else:
            return True

    def get_key_values(self, key):
        if not self.is_key_on_dictionary(key):
            print("No existe el no-terminal solicitado")
            return []
        else:
            return self.grammar_dictionary.get(key)

    # Returns all values from all keys
    def get_all_values(self):
        return list(self.grammar_dictionary.values())

#Using in built pointer implementation (Diferente variables points to the same inmutable objetc)
class CATNode:
    def __init__(self, _etiqueta, _hijos, _padre):
        self.etiqueta = _etiqueta
        self.hijos = _hijos
        self.padre = _padre
        self.siguiente = 0
        self.n_hijos = []

    def add_child(self, new_child):
        self.n_hijos.append(new_child)
        self.siguiente+=1

    def set_parent(self, new_parent):
        self.padre = new_parent

    def get_parent(self):
        return self.padre

class CATree:
    def __init__(self):
        self.root = None
        self.actual_node = None
        self.is_usable = True

        self.dictio_visualizer = {}

    def insert(self, _etiqueta, _hijos, debug = False):
        if self.is_usable:
            if debug: print(_etiqueta, ": ", end="")
            if not self.root:
                temp_node = CATNode(_etiqueta, _hijos, None)
                self.root = temp_node
                self.actual_node = temp_node
                if debug: print("\t Creando Raiz")

            else:
                if self.down_to_first_child() == _etiqueta :                        # Evaluando primer hijo es equivalente a la etiqueta ingresante
                    temp_node = CATNode(_etiqueta, _hijos, self.actual_node)        # Por lo general siempre es verdadero
                    self.actual_node.add_child(temp_node)
                    self.actual_node = temp_node
                    if debug: print("\t Insercción normal -> Op 1")

                else:                                                               # De no serlo es por que : No hay concordancia o no existe hijo a donde bajar
                    self.actual_node = self.go_next(self.actual_node)
                    if self.actual_node != None:
                        #print("-->", self.actual_node.hijos, "-->", self.actual_node.siguiente)
                        if self.actual_node.hijos[self.actual_node.siguiente] == _etiqueta:
                            temp_node = CATNode(_etiqueta, _hijos, self.actual_node)
                            self.actual_node.add_child(temp_node)
                            self.actual_node = temp_node
                            if debug: print("\t Insercción siguiente -> Op 2")
                        else:
                            self.is_usable = False
                            if debug: print("\t Incongruencia de insercción")
                    else:
                        self.is_usable = False
                        if debug: print("\t Root reached!!")

                if self.is_usable and self.down_to_first_child() == "lambda":
                    if debug: print("Lambda: \t Lambda in -> Op 3")
                    self.insert_lambda()

    ######### OPERACION 1 ACORDE A LA PROPUESTA DE LABORATARIO ############################
    def down_to_first_child(self):
        if len(self.actual_node.hijos) == 0:
            return ""
        else:
            return self.actual_node.hijos[0]

    ######### OPERACION 2 ACORDE A LA PROPUESTA DE LABORATARIO ############################
    def go_next(self, current_node):                                            # First interaction is actual node. In recursivity it takes several temp nodes values until it reaches root node
        if current_node.get_parent() != None:
            temp_parent = current_node.get_parent()
            if( temp_parent.siguiente < len(temp_parent.hijos) ):
                return temp_parent
            else:
                return self.go_next(temp_parent)
        else:
            return None                                                         # Indica que hemos llegado a la raiz (por ende no tiene padre)

    ######### OPERACION 3 ACORDE A LA PROPUESTA DE LABORATARIO ############################
    def insert_lambda(self):
        temp_node = CATNode("lambda", [], self.actual_node)
        self.actual_node.add_child(temp_node)


    #############  Tree tools (Ignore) #################
    def draw_tree(self):
        if not self.root:
            print("\tERROR: Null root")
            return

        self.set_tree_tranversal(self.root, 0, debug = False)
        for key in self.dictio_visualizer:
            print(key, self.dictio_visualizer.get(key))

    def add_to_dictio(self, _level, _etiqueta):
        if not self.dictio_visualizer.get(_level):
            self.dictio_visualizer[_level] = []
        self.dictio_visualizer[_level].append(_etiqueta)

    def set_tree_tranversal(self, start_from, order, debug = False):
        if debug:
            print(order, start_from.etiqueta, start_from.hijos)

        self.add_to_dictio(order, "ROOT" + "->" + start_from.etiqueta if not start_from.padre else start_from.padre.etiqueta + "->" + start_from.etiqueta)
        for node in start_from.n_hijos:
            self.set_tree_tranversal(node, order+1, debug)
        return

class CATgrammar:
    def __init__(self):
        self.raw_grammar = []

        self.productions = CATproduction()
        self.my_table = CATsintatic_table()
        self.terminals = []
        self.non_terminals = []

        self.component_separator = ""
        self.right_component_separator = ""
        self.empty_component = ""

    def reader(self, for_root = True):
        temporal_container = [] # En caso procesamos la lectura de otra manera
        if for_root:
            print("CAT:/ Escriba o pegue la gramatica(ctrl+v). Para finalizar presione ctrl+(z/d) (+ enter si es necesario)")
        else:
            print("CAT:/ Escriba o pegue la cadena a validar(ctrl+v). Para finalizar presione ctrl+(z/d) (+ enter si es necesario)")
        while True:
            try:
                line = input()
            except EOFError:
                break

            if for_root:
                self.raw_grammar.append(line)
            else:
                temporal_container.append(line)

        if not for_root:
            return temporal_container


    def _get_non_terminals(self): # Intern class function, don't use it.
        for dictionary_key in self.productions.grammar_dictionary:
            self.non_terminals.append(dictionary_key)

    def _get_terminals(self): # Intern class function, don't use it.
        for dictionary_key in self.productions.grammar_dictionary:
            for dictionary_value in self.productions.grammar_dictionary[dictionary_key]:
                disgregated = dictionary_value.split()
                for i in disgregated:
                    if not self.productions.grammar_dictionary.get(i) and not i in self.terminals:
                        self.terminals.append(i)

    def process_grammar(self, component_separator = ":=", right_component_separator = "|", empty_component = "lambda" ): # Use only if we put something in raw data
        self.component_separator = component_separator
        self.right_component_separator = right_component_separator
        self.empty_component = empty_component
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

    # Primer nodo terminal a la derecha de la produccion
    def get_primero(self, not_terminal):
        if not self.productions.is_usable():
            print("No se puede utilizar esta funcion sin construir la gramatica")
            return
        if not_terminal in self.terminals:
            return [not_terminal]
        elif not self.productions.is_key_on_dictionary(not_terminal):
            print(not_terminal, "no existe")
            return ""
        else:
            terminal_founded = False
            t_production = self.productions.get_key_values(not_terminal)[0] #WARNING Assuming each non terminal has at least one production. Check later
            t_production = t_production.split()[0] # WARNING Assuming each composition is separated by " "
            while not terminal_founded:
                #print("Looking for:", t_production)
                if t_production in self.terminals:
                    terminal_founded = True # Just to be sure
                    return t_production
                elif not self.productions.is_key_on_dictionary(t_production):
                    print("ERROR: Gramatica mal estructurada - Imposible encontrar primero para", not_terminal)
                    terminal_founded = True
                    return ""
                else:
                    t_production = self.productions.get_key_values(t_production)[0].split()[0]

    def get_primeros(self, not_terminal, verified = True, n_recursive = 0, update_table=False):
        if verified:
            print("-->", not_terminal, ": ", end = '')
            if not self.productions.is_usable():
                print("No se puede utilizar esta funcion sin construir la gramatica")
                return ""

        if not_terminal in self.terminals:
            return [not_terminal]
        elif not self.productions.is_key_on_dictionary(not_terminal):
            print(not_terminal, "no existe")
            return ""
        else:
            g_primeros = []
            t_productions = self.productions.get_key_values(not_terminal)
            for t_production in t_productions:
                o_t_production = t_production
                t_production = t_production.split()[0]
                g_primeros = g_primeros + self.get_primeros(t_production, False, n_recursive+1) # Can't use append. It creates a list of lists

                # Algoritmo imbuido para actualizar tabla
                if n_recursive == 0 and update_table:
                    for g in g_primeros:
                        if g != self.empty_component:
                            self.my_table.insert(not_terminal, g, o_t_production) #No termina, Terminal, Cruce
                        else:
                            lambda_adding = self.get_siguientes(not_terminal, verified=False)
                            for lam in lambda_adding:
                                self.my_table.insert(not_terminal, lam, self.empty_component)

            return g_primeros

    def get_siguientes(self, i_terminal, verified = True, n_recursive = 0):
        if verified:
            print("--> Siguientes de ", i_terminal, ": ", end = '')
            if not self.productions.is_usable():
                print("No se puede utilizar esta funcion sin construir la gramatica")
                return ""

        if i_terminal in self.terminals:
            return [i_terminal]
        elif not self.productions.is_key_on_dictionary(i_terminal):
            print(i_terminal, "no existe")
            return ""
        else:
            a_siguiente = []

            if (self.non_terminals.index(i_terminal) == 0):
                a_siguiente.append("$")

            all_productions = self.productions.get_all_values() # Contains a list with all rigth productions organized in a list of lists
                                                                # Each list in this list comes from a specific non terminal in its postion is according to the same non terminal in self.non_terminals

            for nonterminal_production in all_productions:
                prepare_for_circular_references = False
                if all_productions.index(nonterminal_production) == self.non_terminals.index(i_terminal):
                    prepare_for_circular_references = True

                for in_production in nonterminal_production:
                    in_production = in_production.split()
                    if i_terminal in in_production: # Verificamos si el no terminal con el que trabajamos esta en una produccion para extraer el siguiente

                        p_index = in_production.index(i_terminal)
                        if p_index + 1 >= len(in_production): # Verificando si no existe un componente derecho. En caso no lo hay, extraemos los siguientes de la raiz de la produccion
                            if not prepare_for_circular_references: #WARNING Teacher didn't mention anything about this situation
                                a_siguiente = a_siguiente + self.get_siguientes(self.non_terminals[all_productions.index(nonterminal_production)], verified=False,n_recursive=2)
                        else: # En caso si hay un miembro al lado derecho, extraemos sus primeros
                            next_member =  in_production[p_index +1]
                            next_primeros = self.get_primeros(next_member, False, n_recursive=1)

                            if self.empty_component in next_primeros:
                                next_primeros =  next_primeros + self.get_siguientes(next_member, verified=False, n_recursive=2)
                                next_primeros = [elem for elem in next_primeros if elem != self.empty_component] # Deleting empty_component

                            a_siguiente = a_siguiente + next_primeros

            return [i for n, i in enumerate(a_siguiente) if i not in a_siguiente[:n]] # Avoiding duplicates


    def fill_dictionary(self):
        for _no_terminal in self.non_terminals:
            self.get_primeros(_no_terminal, verified=False, update_table=True) # El codigo de get primeros, mientras recorre puede actualizar la tabla semantica
        print(self.my_table)

    def chain_validation(self, debug = False, with_tree_at_end = False, with_tree_debug = False):
        raw_chain = self.reader(for_root = False)

        for chain in raw_chain: # Validando linea por linea
            print("Validando: ", chain)
            entry = chain.split()
            stack = ["$"]
            internal_tree = CATree()

            stack.append(self.non_terminals[0]) # Push estadoInicial
            entry.append("$")

            while(entry and stack):
                if debug:
                    print("Cadena: ", entry)
                    print("Entrada: ", stack)

                if (stack[len(stack)-1] == entry[0]):
                    internal_tree.insert(stack[len(stack)-1], [], with_tree_debug)
                    stack.pop()                                                         # Deleting last element
                    entry.pop(0)
                else:
                    temp1 = stack.pop()                                                 # Getting and deleting last element
                    temp2 = entry[0]
                    x_val = self.my_table.get_from_keys(temp1, temp2).split()
                    internal_tree.insert(temp1, x_val.copy(), with_tree_debug)          # Copy() to avoid inmutable objetcs
                    x_val.reverse()

                    if x_val[0] == "ERROR":
                        break

                    else:
                        for x in x_val:
                            if x != self.empty_component:
                                stack.append(x)

            if(not stack and not entry):
                print("\t Cadena aceptada")
                if with_tree_at_end:
                    print("\t Mostrando arbol")
                    print()
                    internal_tree.draw_tree()
                    print()
                    print()
            else:
                print("\t Cadena invalida")
                if with_tree_at_end:
                    print("\t No hay arbol que mostrar")
                    print()
                    print()



    def print_dictionary(self):
        print("DICTIONARY")
        print(self.productions.grammar_dictionary)

    def print_raw_grammar(self):
        print("Gramatica Bruta: ")
        for gram in self.raw_grammar:
            print(gram)

    def create_class_nonal_interpreter(self, sign_to_interpret):
        switcher = {
            "*": "multiplicacion",
            "/": "division",
            "+": "suma",
            "-": "menos",
            "(": "parentesis_derecho",
            ")": "parentesis_izquierdo"
        }
        return switcher.get(sign_to_interpret, "unknow_alpha")

    def create_classes_carpet(self):
        print("CAT:/Creando directorio de carpetas.")
        path = "classes"
        try:
            os.mkdir(path)
        except:
            pass
        else:
            print("\tCreación de directorio completo")


        for non_terminal in self.non_terminals:
            if not non_terminal.isalnum():
                non_terminal = self.create_class_nonal_interpreter(non_terminal)

            print("\tRedactando: " + non_terminal)
            file = open(path + "/" + non_terminal + ".py", "w+")
            file.write("# Non terminal class\n")
            file.write("class " + non_terminal + "(AbstractExpressionNT):\n")
            file.write("\t#diccionario<" + non_terminal + ", Objeto>\n")
            file.write("\tdef interprets(val1, val2, val3):\n")
            file.write("\t\treturn (0, 0, 0)\n")
            file.close()

        for terminal in self.terminals:
            if not terminal.isalnum():
                terminal = self.create_class_nonal_interpreter(terminal)
            print("\tRedactando: " + terminal)
            file = open(path + "/" + terminal + ".py", "w+")
            file.write("# Terminal class\n")
            file.write("class " + terminal + "(AbstractExpressionT):\n")
            file.write("\t#valor\n")
            file.write("\tdef interprets():\n")
            file.write("\t\treturn valor\n")
            file.close()

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

# --------------------------------------------------------------------------------
# ---------------------------  START HERE ----------------------------------------
# --------------------------------------------------------------------------------
"""   --> CUIDADO <-- Insertar gramáticas acorde a este modelo.
E  := T Ep
Ep := + T Ep
Ep := - T Ep
Ep := lambda
T  := F Tp
Tp := * F Tp  |  /  F Tp  | lambda
F  := ( E ) | num | id
"""
my_grammar = CATgrammar()
my_grammar.reader()           # Just type or paste the grammar
my_grammar.process_grammar()  #  IN DEFAULT: process_grammar(component_separator=":=", right_component_separator="|")
                              #  Set according grammar separators
print(my_grammar)
#print(my_grammar.get_siguientes("F")) # +++++ NUEVO GET_SIGUIENTE +++++++
my_grammar.fill_dictionary()  # Funcion para llenar diccionario
#my_grammar.create_classes_carpet();


""" Cadenas a validar
num + num + num + num
( num + num ) + ( num + num )
( num * ) num
num * ( num * num )
num + ( num * num )
"""
# Just type or paste the chain for validation
#my_grammar.chain_validation()                                              # Proceso de validacion
my_grammar.chain_validation(with_tree_at_end=True)                          # Proceso de validacion mostrando arbol al final (ln 395, 406, 413) -> Proceso de insercion en ln 129 (Incluye tres tipos de operaciones descritas en laboratiorio)
#my_grammar.chain_validation(with_tree_at_end=True, with_tree_debug = True) # Proceso de validacion con arbol e operaciones solicitadas en laboratorio
