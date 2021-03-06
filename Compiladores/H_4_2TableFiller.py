"""
Created on SAT MAY 09 10:45:21 2020
TABLE FILLER
@author: DAVE
"""
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

        else:
            self.table[key1][key2] = inter_val
            print("Valor actualizado")

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
        
# ---------------------------  START HERE ----------------------------------------
my_table = CATsintatic_table()
# FILLING UP
my_table.insert("E", "(", "T Ep")       # For E
my_table.insert("E", "num", "T Ep")
my_table.insert("E", "id", "T Ep")

my_table.insert("Ep", "+", "+ T Ep")    # For Ep
my_table.insert("Ep", "-", "- T Ep")
my_table.insert("Ep", ")", "lambda")
my_table.insert("Ep", "$", "lambda")

my_table.insert("T", "(", "F Tp")       # For T
my_table.insert("T", "num", "F Tp")
my_table.insert("T", "id", "F Tp")

my_table.insert("Tp", "+", "lambda")    # For Tp
my_table.insert("Tp", "-", "lambda")
my_table.insert("Tp", "*", "* F Tp")
my_table.insert("Tp", "/", "/ F Tp")
my_table.insert("Tp", ")", "lambda")
my_table.insert("Tp", "$", "lambda")

my_table.insert("F", "(", "( E )")    # For Tp
my_table.insert("F", "num", "num")
my_table.insert("F", "id", "id")

# CONSULTING
my_table.get("E", "(")  # Valid
my_table.get("Ep", "-")
my_table.get("Tp", "$")

my_table.get("E", "+")  # Not defined
my_table.get("Ep", "/")  # Not defined

my_table.get("Ea", "+")  # Not Valid

print(my_table)
