from AbstractExpression import *
from d_terminal import * 

class E(NonTerminalExpression):
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

