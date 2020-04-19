importar CAT_mat_basico

u_variable a = 10
u_variable b = 12
variable c[] = [1, 2, 3, 4]                   ~~ Vector
variable d[][] = [[1, 2],  [3, 4]]            ~~ Matriz
variable e{} = {1: "Agua", 2: "Luz", 3:"Red"} ~~ Red

~~ Funciones Secundarias

funcion multiplicar(variable x, variable y) -> retorna a_1:
  variable a_1 = x * y

funcion sumar(variable x, variable y) -> retorna m_suma:
  variable j = x + y ~~ ERROR, se necesita que exista la variable de respuesta


~~ Funcion principal

principal() -> retorna 0:
  variable x_1 = 12.4  ~~ Definicion automática de tipos básicos
  variable x_2 = 10
  variable x_3 = x_1 + x_2
  imprimir( x_3 )

  variable x_4 = multiplicar(x_1, x_2)

  mientras (x_4 < a) o (x_3 > b) entonces: ~~ While
    si x_4 < a entonces:                   ~~ If
      x_4++
    sino si x_3 < b entonces:
      x_3--
    sino entonces:
      x_2++

  para x_1 y x_2 mientras x_3 < a entonces:
    x_1+=2
    x_2+=2
