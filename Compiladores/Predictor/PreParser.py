from d_non_terminal import*
from d_terminal import *

class PreParser():
    def __init__(self):
        self.E_in = E()
        self.Ep_in = Ep()
        self.T_in = T()
        self.Tp_in = Tp()
        self.F_in = F()

        self.suma_in = suma_c()
        self.menos_in = menos_c()
        self.lambda_in = lambda_c()
        self.multiplicacion_in = multiplicacion_c()
        self.division_in = division_c()
        self.parentesis_izquierdo_in = parentesis_izquierdo_c()
        self.parentesis_derecho_in = parentesis_derecho_c()
        self.num_in = num_c()

    def interprets(self, base, childs, context):
        if base == "E":
            return self.E_in.interprets(base, childs, context)
        elif base == "Ep":
            return self.Ep_in.interprets(base, childs, context)
        elif base == "T":
            return self.T_in.interprets(base, childs, context)
        elif base == "Tp":
            return self.Tp_in.interprets(base, childs, context)
        elif base == "F":
            return self.F_in.interprets(base, childs, context)
        elif base == "+":
            return self.suma_in.interprets(base, childs, context)
        elif base == "-":
            return self.menos_in.interprets(base, childs, context)
        elif base == "lambda":
            return self.lambda_in.interprets(base, childs, context)
        elif base == "*":
            return self.multiplicacion_in.interprets(base, childs, context)
        elif base == "/":
            return self.division_in.interprets(base, childs, context)
        elif base == "(":
            return self.parentesis_derecho_in.interprets(base, childs, context)
        elif base == ")":
            return self.parentesis_derecho_in.interprets(base, childs, context)
        elif base == "num":
            return self.num_in.interprets(base, childs, context)
        else:
            pass
