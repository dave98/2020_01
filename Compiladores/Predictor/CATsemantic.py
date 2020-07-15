class SemanticContext():
    def __init__(self, _error_tracker):
        self.error_tracker = _error_tracker
        self.stack_content = []
        self.is_viable = True

    def add_val(self, n_values):
        #print("Setting values: ", n_values)

        if isinstance(n_values, int):
            self.stack_content.append(n_values)
        else:
            self.is_viable = False

    def perform_operation(self, op_type):
        #print("Performing operation: ", op_type)
        if not self.is_viable:
            return


        if (len(self.stack_content) == 0) :
            self.error_tracker.add_error(-1, 302)
            return

        if op_type == '+':
            if len(self.stack_content) < 2:
                self.error_tracker.add_error(-1, 305)
            temp_s1 = self.stack_content.pop()
            temp_s2 = self.stack_content.pop()
            temp_s = temp_s2 + temp_s1
            self.stack_content.append(temp_s)

        elif op_type == '-':
            if len(self.stack_content) < 2:
                self.error_tracker.add_error(-1, 305)
            temp_s1 = self.stack_content.pop()
            temp_s2 = self.stack_content.pop()
            temp_s = temp_s2 - temp_s1
            self.stack_content.append(temp_s)

        elif op_type == '*':
            if len(self.stack_content) < 2:
                self.error_tracker.add_error(-1, 305)
            temp_s1 = self.stack_content.pop()
            temp_s2 = self.stack_content.pop()
            temp_s = temp_s2 * temp_s1
            self.stack_content.append(temp_s)
        elif op_type == '/':
            if len(self.stack_content) < 2:
                self.error_tracker.add_error(-1, 305)
            temp_s1 = self.stack_content.pop()
            temp_s2 = self.stack_content.pop()
            if temp_s1 == 0:
                self.error_tracker.add_error(-1, 303)
            print("--> ", temp_s1, " - ", temp_s2)
            temp_s = temp_s2 / temp_s1
            self.stack_content.append(temp_s)
        else:
            self.error_tracker.add_error(-1, 304)


class AbstractBase():
    def interprets(self):
        pass

class NonTerminalNode(AbstractBase):
    def __init__(self, _NTnode, _semantic_context, _error_tracker): # childs_n equal to child_pointing
        self.inNTnode = _NTnode
        self.error_tracker = _error_tracker
        self.semantic_context = _semantic_context

    def interprets(self):
        if ( len(self.inNTnode.n_hijos)  == 0):
            return TerminalNode(self.inNTnode, self.semantic_context, self.error_tracker).interprets()
        else:
            for child in self.inNTnode.n_hijos:
                NonTerminalNode(child, self.semantic_context, self.error_tracker).interprets()

class TerminalNode(AbstractBase):
    def __init__(self, _NTnode, _semantic_context, _error_tracker):
        self.inNTnode = _NTnode
        self.error_tracker = _error_tracker
        self.semantic_context = _semantic_context

    def interprets(self):
        print("DefaultTerminalNode: ", self.inNTnode.etiqueta)


# -----------------------------NON Terminal----------------------------------
class E(NonTerminalNode):
    def interprets(self):
        if ( len(self.inNTnode.n_hijos)  == 0):
            self.error_tracker.add_error(-1, 301)
        else:
            T(self.inNTnode.n_hijos[0], self.semantic_context, self.error_tracker).interprets()
            Ep(self.inNTnode.n_hijos[1], self.semantic_context, self.error_tracker).interprets()

class Ep(NonTerminalNode):
    def interprets(self):
        if ( len(self.inNTnode.n_hijos)  == 0):
            self.error_tracker.add_error(-1, 301)
        else:
            if(self.inNTnode.n_hijos[0].etiqueta == '+'):
                T(self.inNTnode.n_hijos[1], self.semantic_context, self.error_tracker).interprets()
                suma(self.inNTnode.n_hijos[0], self.semantic_context, self.error_tracker).interprets()
                Ep(self.inNTnode.n_hijos[2], self.semantic_context, self.error_tracker).interprets()
                return

            elif(self.inNTnode.n_hijos[0].etiqueta == '-'):
                T(self.inNTnode.n_hijos[1], self.semantic_context, self.error_tracker).interprets()
                resta(self.inNTnode.n_hijos[0], self.semantic_context, self.error_tracker).interprets()
                Ep(self.inNTnode.n_hijos[2], self.semantic_context, self.error_tracker).interprets()
                return
            else:
                return empty(self.inNTnode.n_hijos[0], self.semantic_context, self.error_tracker).interprets()

class T(NonTerminalNode):
    def interprets(self):
        if ( len(self.inNTnode.n_hijos)  == 0):
            self.error_tracker.add_error(-1, 301)
        else:
            F(self.inNTnode.n_hijos[0], self.semantic_context, self.error_tracker).interprets()
            Tp(self.inNTnode.n_hijos[1], self.semantic_context, self.error_tracker).interprets()

class Tp(NonTerminalNode):
    def interprets(self):
        if ( len(self.inNTnode.n_hijos)  == 0):
            self.error_tracker.add_error(-1, 301)
        else:
            if(self.inNTnode.n_hijos[0].etiqueta == '*'):
                F(self.inNTnode.n_hijos[1], self.semantic_context, self.error_tracker).interprets()
                multiplicacion(self.inNTnode.n_hijos[0], self.semantic_context, self.error_tracker).interprets()
                Tp(self.inNTnode.n_hijos[2], self.semantic_context, self.error_tracker).interprets()
                return

            elif(self.inNTnode.n_hijos[0].etiqueta == '/'):
                F(self.inNTnode.n_hijos[1], self.semantic_context, self.error_tracker).interprets()
                division(self.inNTnode.n_hijos[0], self.semantic_context, self.error_tracker).interprets()
                Tp(self.inNTnode.n_hijos[2], self.semantic_context, self.error_tracker).interprets()
                return
            else:
                return empty(self.inNTnode.n_hijos[0], self.semantic_context, self.error_tracker).interprets()

class F(NonTerminalNode):
    def interprets(self):
        if ( len(self.inNTnode.n_hijos)  == 0):
            self.error_tracker.add_error(-1, 301)
        else:
            if(self.inNTnode.n_hijos[0].etiqueta == '('):
                par_iz(self.inNTnode.n_hijos[0], self.semantic_context, self.error_tracker).interprets()
                E(self.inNTnode.n_hijos[1], self.semantic_context, self.error_tracker).interprets()
                par_der(self.inNTnode.n_hijos[2], self.semantic_context, self.error_tracker).interprets()
                return
            elif(self.inNTnode.n_hijos[0].etiqueta == 'num'):
                return num(self.inNTnode.n_hijos[0], self.semantic_context, self.error_tracker).interprets()
            else:
                return iden(self.inNTnode.n_hijos[0], self.semantic_context, self.error_tracker).interprets()

# -----------------------------Terminal----------------------------------
class suma(TerminalNode):
    def interprets(self):
        self.semantic_context.perform_operation('+')
        #print("SumaNode: ", self.inNTnode.etiqueta)

class resta(TerminalNode):
    def interprets(self):
        self.semantic_context.perform_operation('-')
        #print("RestaNode: ", self.inNTnode.etiqueta)

class empty(TerminalNode):
    def interprets(self):
        pass
        #print("EmptyNode: ", self.inNTnode.etiqueta)

class multiplicacion(TerminalNode):
    def interprets(self):
        self.semantic_context.perform_operation('*')
        #print("MultiplicacionNode: ", self.inNTnode.etiqueta)

class division(TerminalNode):
    def interprets(self):
        self.semantic_context.perform_operation('/')
        #print("DivisionNode: ", self.inNTnode.etiqueta)

class par_der(TerminalNode):
    def interprets(self):
        pass

        #print("ParDerNode: ", self.inNTnode.etiqueta)

class par_iz(TerminalNode):
    def interprets(self):
        pass

        #print("ParIz: ", self.inNTnode.etiqueta)

class num(TerminalNode):
    def interprets(self):
        self.semantic_context.add_val(int(self.inNTnode.val))
        #print("NumNode: ", self.inNTnode.val)

class iden(TerminalNode):
    def interprets(self):
        self.semantic_context.is_viable = False
        #print("IdenNode: ", self.inNTnode.val)
