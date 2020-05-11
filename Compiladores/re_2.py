"""
Created on Thu Apr 23 18:56:50 2020
REGEX AND FLEX
@author: ASUS
"""
import re

# Los .. sirven para reemplazar lo que falte en un string
# El ^ viene de "empieza por"
# El $ viene de "finaliza por"
# El * implica zero mas ocurrencias 
# El + implica una o más ocurrencias.
# Los {} especifican el número de ocurrencias
# Los () capture and group

pattern = '^[^0-9][a-zA-Z0-9_]+$'
text = '1variable_1'

x = re.findall(pattern, text)
if x:
    print("Si hay match")
else:
    print("No hay match")
