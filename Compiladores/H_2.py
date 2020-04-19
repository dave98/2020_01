# -*- coding: utf-8 -*-
"""
Created on Sun Apr  5 19:08:57 2020

@author: Dave
"""

used_vocals = ['a', 'e', 'i', 'o', 'u']

i_grammar = ['ar', 'er', 'ir']
f_grammar = ['ando', 'iendo', 'iendo']
e_grammar = ['-', 'yendo', 'yendo']

def contains_any(set, str):
    return True in [x in str for x in set]

def fixer(verb, gerund):
    get_fverb = verb[-2:]
    get_fgerund = verb[:-2]
    
    '''General cases'''
    if contains_any(get_fgerund[-1], used_vocals):
        get_fgerund = get_fgerund + e_grammar[i_grammar.index(get_fverb)]
    else:
        get_fgerund = get_fgerund + f_grammar[i_grammar.index(get_fverb)]
    
    
    '''Some especial cases'''
    if i_grammar.index(get_fverb) == 2: #Special case ir
        pos = verb.rfind('e') 
        if pos != -1: 
            get_fgerund = get_fgerund[0:pos] + 'i' + get_fgerund[pos+1:] 
    
    
    if gerund == get_fgerund: return 'SI'
    else: return 'NO'
    
    
verb = 'caer'
gerund = 'cayendo'
print(fixer(verb, gerund))


