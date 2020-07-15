import time
import sys

class CATerror_manager(object):
    """docstring for error_manager."""

    def __init__(self):
        self.panic_mode = False
        self.keeper_of_the_warnings = []
        self.the_error_master = []

        self.error_dict = { 101 : "BuildGrammar  -> La gramática carece de una extructura adecuada para el predictor",
                            102 : "BuildGrammar  -> Diccionario no ubica la producción solicitada",
                            103 : "BuildGrammar  -> GetPrimero, petición no existe",
                            104 : "BuildGrammar  -> GetPrimero, el conjunto de producciones no esta listo para ser usado",
                            105 : "BuildGrammar  -> GetSiguiente, petición no existe",
                            106 : "BuildGrammar  -> GetSiguiente, el conjunto de producciones no esta listo para ser usado",
                            301 : "BuildSemantic -> Error en la depuracion semantica",
                            302 : "BuildSemantic -> Error durante calculo",
                            303 : "BuildSemantic -> No se acepta la division entre cero",
                            304 : "BuildSemantic -> Operador desconocido",
                            305 : "BuildSemantic -> No existe los elementos necesarios para realizar esta operacion."
                          }

        self.warning_dict = { 501 : "Lexical  -> Variable con formato incongruente.",
                              502 : "Lexical  -> Numero con formato incongruente.",
                              601 : "Sintatic -> Cadena invalida.",
                              801 : "Semantic -> El numero es demasiado grande",
                              802 : "Semantic -> El numero es negativo"

                            }

    def add_warning(self, _line, _code):
        self.keeper_of_the_warnings.append([_line, _code])

    def add_error(self, _line, _code):
        self.the_error_master.append(_line)
        self.the_error_master.append(_code)
        self.active_panic_mode()

    def status_report(self):
        print("------------------------------------------------------------------------------------------------------")
        print("---------------------------------------  LOGS  -------------------------------------------------------")
        for _warning in self.keeper_of_the_warnings: #warning[0] : ln, warning[1] : code
            print("Warning en ln ", _warning[0], " - ", self.warning_dict[_warning[1]])
        if  self.panic_mode:
            print("Error   en ln ", self.the_error_master[0], " - ", self.error_dict[self.the_error_master[1]])
        print("------------------------------------------------------------------------------------------------------")
        print("------------------------------------------------------------------------------------------------------")


    def active_panic_mode(self):
        self.panic_mode = True
        self.status_report()
        print("Saliendo")
        time.sleep(3)
        sys.exit()



if __name__ == "__main__":
    error_manager = CATerror_manager()

    error_manager.add_warning(453, 501)
    error_manager.add_warning(452, 501)
    error_manager.add_warning(438, 801)
    error_manager.add_error(324, 102)

    error_manager.status_report()
