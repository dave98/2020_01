#ifndef CATERROR_MANAGER_H
#define CATERROR_MANAGER_H

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <windows.h>

using namespace std;

class CATerror_manager{
public:
  bool panic_mode;
  vector<vector<int>> keeper_of_the_warnings;
  vector<vector<int>> error_master;

  unordered_map<int, string> warning_dict;
  unordered_map<int, string> error_dict;

  CATerror_manager();
  ~CATerror_manager();

  void initialize_warnings();
  void initialize_errors();
  void add_warning(int, int);
  void add_error(int, int);
  void status_report();
  void activate_panic_mode();
};

CATerror_manager::CATerror_manager(){
  this->panic_mode = false;
  this->keeper_of_the_warnings = vector<vector<int>>(0, vector<int>(0, 0));
  this->error_master = vector<vector<int>>(0, vector<int>(0, 0));
  this->initialize_warnings();
  this->initialize_errors();
}

CATerror_manager::~CATerror_manager(){}

void CATerror_manager::initialize_warnings(){
this->warning_dict[501] = "Lexical: Variable con formato incongruente.";
}

void CATerror_manager::initialize_errors(){
  this->error_dict[101] = "Lexical: No existe el archivo de lectura solicitado.";
  this->error_dict[102] = "Lexical: Un comentario no ha sido concluido.";
  this->error_dict[103] = "Lexical: No hay lexemas que retornar.";
  this->error_dict[104] = "Lexical: La tabla de simbolos ha sobrepasado la raiz.";
  this->error_dict[105] = "Lexical: Error de ambito.";
  this->error_dict[201] = "Sintatic: No existe el archivo descrito para la gramatica.";
  this->error_dict[202] = "Sintatic: Se ha realizado una peticion de GetPrimero inadecuada.";
  this->error_dict[203] = "Sintatic: Se ha descubierto una recursion por la izquierda en la gramatica.";
  this->error_dict[204] = "Sintatic: Se ha realizado una peticion de GetSiguiente inadecuada.";
  this->error_dict[205] = "Sintatic: Sin lexemas que procesar.";
  this->error_dict[206] = "Sintatic: El programa ha fallado su proceso de validacion.";
  this->error_dict[207] = "Sintatic: El arbol no esta listo para su analisis sintactico.";
  this->error_dict[301] = "Semantic: La variable ha sido declarada dos veces.";
  this->error_dict[302] = "Semantic: Un identicador no ha sido declarado.";
  this->error_dict[303] = "Semantic: El supervisor de simbolos ha encontrado una excepcion.";

}

void CATerror_manager::add_warning(int _line, int _code){
  this->keeper_of_the_warnings.push_back(vector<int>{_line, _code});
}

void CATerror_manager::add_error(int _line, int _code){
  this->error_master.push_back(vector<int>{_line, _code});
  this->panic_mode = true;
  this->activate_panic_mode();
}

void CATerror_manager::status_report(){
  cout<<"+++++++++++++++++++++++++++++++++++ LOGS +++++++++++++++++++++++++++++++++++++"<<endl;
  for(unsigned int i = 0; i < this->keeper_of_the_warnings.size(); i++){
  cout<<"ADVERTENCIA: En linea "<<this->keeper_of_the_warnings[i][0]<<" -> "<<this->warning_dict.at( (int)this->keeper_of_the_warnings[i][1]) <<endl;
  }
  if(this->panic_mode){
    cout<<"ERROR: En linea "<<this->error_master[0][0]<<" -> "<<this->error_dict.at(this->error_master[0][1])<<endl;
  }
  cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
  return;
}

void CATerror_manager::activate_panic_mode(){
  this->panic_mode = true;
  this->status_report();
  cout<<"CAT ha ubicado un error y dejado de responder... Saliendo"<<endl;
  Sleep(5000);
  exit(EXIT_SUCCESS);
}

#endif
