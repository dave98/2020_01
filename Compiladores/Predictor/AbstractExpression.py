

class AbstractExpression():
    def interprets(self, context):
        raise NotImplementedError("Interpret must be defined en subclass")

class TerminalExpression(AbstractExpression):
    def interprets(self, context):
        print("Inside TerminalExpression - Interpret")

class NonTerminalExpression(AbstractExpression):
    def interprets(self, context):
        print("Inside NonTerminalExpression - Interpret con", self.data)

class Context:
    def __init__(self, value, start_on):
        self.value = value.split()  #[]
        self.start_on = [start_on]

        self.operations_pool = []
        self.nex_operations = ""

    def update_operations_pool(self, extra_val):
        self.operations_pool.append(extra_val)
        self.perform_operations_pool()

    def perform_operations_pool(self):
        if op != "" and len(self.operations_pool) >= 2:
            acc = 0
            for i in self.operations_pool:
                if self.nex_operations == "+":
                    acc += i
                elif self.nex_operations == "-":
                    acc -= i
                else:
                    acc *= i

            self.operations_pool.clear()
            self.operations_pool.append(acc)

            self.nex_operations = "";

    def GetActualContext(self):
        if self.start_on[0] == "lambda":
            self.TakeActualContext()
            return self.GetActualContext()
        else:
            return self.start_on[0]

    def SetMoreContext(self, more_to_start):
        self.start_on.insert(0, more_to_start)

    def TakeActualContext(self):
        self.start_on.pop(0)
