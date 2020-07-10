from AbstractExpression import *
from d_terminal import * 

class E(NonTerminalExpression):
	def __init__(self):
		pass

		self.T_in = T()
		self.Ep_in = Ep()

	def interprets(self, base, childs, context):
		if context.GetActualContext() == base:
			context.TakeActualContext()
			if len(childs) > 0:
				childs.reverse()
				for child in childs:
					context.SetMoreContext(child)
		else:
			print("Interpreter fail")
		return context

class Ep(NonTerminalExpression):
	def __init__(self):
		pass

		self.suma_in = suma_c()
		self.T_in = T()
		self.Ep_in = Ep()
		self.menos_in = menos_c()
		self.lambda_in = lambda_c()

	def interprets(self, base, childs, context):
		if context.GetActualContext() == base:
			context.TakeActualContext()
			if len(childs) > 0:
				childs.reverse()
				for child in childs:
					context.SetMoreContext(child)
		else:
			print("Interpreter fail")
		return context

class T(NonTerminalExpression):
	def __init__(self):
		pass

		self.F_in = F()
		self.Tp_in = Tp()

	def interprets(self, base, childs, context):
		if context.GetActualContext() == base:
			context.TakeActualContext()
			if len(childs) > 0:
				childs.reverse()
				for child in childs:
					context.SetMoreContext(child)
		else:
			print("Interpreter fail")
		return context

class Tp(NonTerminalExpression):
	def __init__(self):
		pass

		self.multiplicacion_in = multiplicacion_c()
		self.F_in = F()
		self.Tp_in = Tp()
		self.division_in = division_c()
		self.lambda_in = lambda_c()

	def interprets(self, base, childs, context):
		if context.GetActualContext() == base:
			context.TakeActualContext()
			if len(childs) > 0:
				childs.reverse()
				for child in childs:
					context.SetMoreContext(child)
		else:
			print("Interpreter fail")
		return context

class F(NonTerminalExpression):
	def __init__(self):
		pass

		self.parentesis_derecho_in = parentesis_derecho_c()
		self.E_in = E()
		self.parentesis_izquierdo_in = parentesis_izquierdo_c()
		self.num_in = num_c()
		self.id_in = id_c()

	def interprets(self, base, childs, context):
		if context.GetActualContext() == base:
			context.TakeActualContext()
			if len(childs) > 0:
				childs.reverse()
				for child in childs:
					context.SetMoreContext(child)
		else:
			print("Interpreter fail")
		return context

