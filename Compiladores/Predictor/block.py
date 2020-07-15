
class NTnode():
    def __init__(self, _name ,_childs = []):
        self.name = _name
        self.childs_n = _childs

class AbstractBase():
    def interprets(self):
        pass

class NonTerminalNode(AbstractBase):
    def __init__(self, _NTnode): # childs_n equal to child_pointing
        self.inNTnode = _NTnode

    def interprets(self):
        if ( len(self.inNTnode.childs_n)  == 0):
            return TerminalNode(self.inNTnode).interprets()
        else:
            for child in self.inNTnode.childs_n:
                NonTerminalNode(child).interprets()

class TerminalNode(AbstractBase):
    def __init__(self, _NTnode):
        self.inNTnode = _NTnode

    def interprets(self):
        print("TerminalNode: ", self.inNTnode.name)


class E(NonTerminalNode):
    def interprets(self):
        if ( len(self.inNTnode.childs_n)  == 0):
            return TerminalNode(self.inNTnode).interprets()
        else:
            for child in self.inNTnode.childs_n:
                print("ENode")
                NonTerminalNode(child).interprets()


if __name__ == "__main__":
    tree_test = NTnode( "2" , [ NTnode("3" , [ NTnode("5") , NTnode("6")]  ), NTnode("4")] )
    abstract_expression = E(tree_test)
    abstract_expression.interprets()

























# This line has not purpose
