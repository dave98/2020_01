from AbstractExpression import *
from d_non_terminal import *

class suma_c(TerminalExpression):
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

class menos_c(TerminalExpression):
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

class lambda_c(TerminalExpression):
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

class multiplicacion_c(TerminalExpression):
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

class division_c(TerminalExpression):
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

class parentesis_derecho_c(TerminalExpression):
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

class parentesis_izquierdo_c(TerminalExpression):
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

class num_c(TerminalExpression):
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

class id_c(TerminalExpression):
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

