# -*- coding: utf-8 -*-
"""
Created on Sun Apr  5 14:45:35 2020

@author: Dave
"""

allowed_1 = ['[', '{', '(']
allowed_2 = [']', '}', ')']

def contains_any(set, str):
    return True in [x in str for x in set]

def review_process(phrase):
    #print(phrase)
    if contains_any(phrase[0:1], allowed_1): # Ubicamos primer caracter de Entrada
        waited_value = allowed_2[allowed_1.index(phrase[0:1])] # Esperamos un caracter de Salida equivalente
        future_value = review_process(phrase[1:])

        if isinstance(future_value, bool): return False    
    
        if future_value[0] == waited_value:
            if len(future_value[1:]) != 0:
                return future_value[1:]
            else: 
                return True
        else:
            if len(future_value[1:]) != 0:
                return '_'
            else: 
                return False
            
    else:
        return phrase # Si no es entrada retornamos la supuesta salida

def review(phrase):
    if len(phrase) == 0:
        return False
    answer = review_process(phrase)
    #print(answer)
    if isinstance(answer, bool): return answer
    else: 
        if contains_any(answer[0:1], allowed_1):
            return review(answer)
        else:
            return False 

#++++++++++++++++++++++++++++++ Main +++++++++++++++++++++++++++++++++++++
a = review('(()){[)]}[]')
print(a)











