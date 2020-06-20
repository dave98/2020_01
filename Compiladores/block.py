
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

    def insert(self, _etiqueta, _hijos):
        if not self.root:
            print("Creando Raiz")

            temp_node = CATNode(_etiqueta, _hijos, None)
            self.root = temp_node
            self.actual_node = temp_node

        else:
            if self.down_to_first_child() == _etiqueta :                        # Evaluando primer hijo es equivalente a la etiqueta ingresante
                temp_node = CATNode(_etiqueta, _hijos, self.actual_node)        # Por lo general siempre es verdadero
                self.actual_node.add_child(temp_node)
                self.actual_node = temp_node
                print("Insercción normal")

            else:                                                               # De no serlo es por que : No hay concordancia o no existe hijo a donde bajar
                self.actual_node = self.go_next(self.actual_node)
                if self.actual_node != None:
                    #print("-->", self.actual_node.hijos, "-->", self.actual_node.siguiente)
                    if self.actual_node.hijos[self.actual_node.siguiente] == _etiqueta:
                        temp_node = CATNode(_etiqueta, _hijos, self.actual_node)
                        self.actual_node.add_child(temp_node)
                        self.actual_node = temp_node
                        print("Insercción siguiente")
                    else:
                        print("Incongruencia de insercción")
                else:
                    print("Root reached!!")

    def down_to_first_child(self):
        if len(self.actual_node.hijos) == 0:
            return ""
        else:
            return self.actual_node.hijos[0]

    def go_next(self, current_node):                                            # First interaction is actual node. In recursivity it takes several temp nodes values until it reaches root node
        if current_node.get_parent() != None:
            temp_parent = current_node.get_parent()
            if( temp_parent.siguiente < len(temp_parent.hijos) ):
                return temp_parent
            else:
                return self.go_next(temp_parent)
        else:
            return None                                                         # Indica que hemos llegado a la raiz (por ende no tiene padre)


my_tree = CATree()
my_tree.insert("E", ["T", "Ep"])
my_tree.insert("T", ["F", "Tp"])
my_tree.insert("F", ["num"])
my_tree.insert("num", [])
my_tree.insert("Tp", ["lambda"])
my_tree.insert("Ep", ["+", "T", "Ep"])
my_tree.insert("+", [])
my_tree.insert("T", ["F", "Tp"])
my_tree.insert("F", ["(", "E", ")"])
my_tree.insert("(", [])
my_tree.insert("E", ["T", "Ep"])
my_tree.insert("T", ["F", "Tp"])
my_tree.insert("F", ["num"])
my_tree.insert("num", [])
my_tree.insert("Tp", ["*", "F", "Tp"])
my_tree.insert("*", [])
my_tree.insert("F", ["num"])
my_tree.insert("num", [])
my_tree.insert("Tp", ["lambda"])
my_tree.insert("Ep", ["lambda"])
my_tree.insert(")", [])
my_tree.insert("Tp", ["lambda"])
my_tree.insert("Ep", ["lambda"])
my_tree.insert("$", [])
my_tree.insert("$", [])
#print(my_tree.down_to_first_child())
#print(my_tree.actual_node.get_parent().hijos)
