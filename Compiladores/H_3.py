# -*- coding: utf-8 -*-
"""
Created on Sun Apr  5 20:17:49 2020

@author: Dave
"""
constants = ['I', 'P', 'U']
units =     ['A', 'W', 'V']
prefix =    ['M',  'm', 'k']
estorbos =  ['.', ',']


def contains_any(set, str):
    return True in [x in str for x in set]

def get_data(phrase, common_sign):
    data = []
    for i in phrase:
       if i.find(common_sign) != -1:
           if contains_any(estorbos, i[-1:]):
               i = i[:-1]
           data.append(i)
    return data

def get_number(string_number): #['2.5MW']
    string_number = string_number[:-1] #['2.5M']
    extrafactors = 1.0

    if contains_any(string_number[-1:], prefix): # Si existe algún prefijo:
        if string_number[-1:] == 'm':
            extrafactors = 0.001
        elif string_number[-1:] == 'k':
            extrafactors = 1000
        else:
            extrafactors = 1000000
        string_number = string_number[:-1]

    number = float(string_number) * extrafactors
    return number

def format_data(data): # [P=2.5MW]
    I = 0.0
    P = 0.0
    U = 0.0
    for i in data:
        if constants.index(i[0]) == 0: #'I'
            I = get_number(i[2:])
        elif constants.index(i[0]) == 1: #'P'
            P = get_number(i[2:])
        else: #'U'
            U = get_number(i[2:])
    return I, P, U

# P = U*I
def get_result(data, n_problem):
    t_data = format_data(data)

    I = t_data[0]
    P = t_data[1]
    U = t_data[2]
    #Por lo general se dispone de dos de tres datos
    print('Problem #' + str(n_problem))
    if I == 0:
        I = P/U
        return constants[0] + '=' + str(format(I, '.2f')) + units[0] + '\n'
    elif P == 0:
        P = U*I
        return constants[1] + '=' + str(format(P, '.2f')) + units[1] + '\n'
    else:
        U = P/I
        return constants[2] + '=' + str(format(U, '.2f')) + units[2] + '\n'



#+++++++++++++++ Main +++++++++++++++++++++++++++++
problema = input()
problem = problema.splitlines()
problem = problem[1:]

number_of_problems = 1

for i in problem:
    data = i.split()
    crucial_data = get_data(data, '=')

    print(get_result(crucial_data, number_of_problems))
    number_of_problems+=1
