#ifndef LEXICAL_LEXEMA_H
#define LEXICAL_LEXEMA_H

#include<iostream>
#include<string>
using namespace std;

class lexical_lexema{
public:
  string patron;
  string descripcion;

  lexical_lexema(string);
  lexical_lexema(string, string);
  ~lexical_lexema();

  friend ostream& operator << (ostream& os, const lexical_lexema& dt);
};


lexical_lexema::lexical_lexema(string _patron){
  this->patron = _patron;
  this->descripcion = "";
}


lexical_lexema::lexical_lexema(string _patron, string _descripcion){
  this->patron = _patron;
  this->descripcion = _descripcion;
}

lexical_lexema::~lexical_lexema(){

}


ostream& operator << (ostream& os, const lexical_lexema& dt){
  os<<"<"<<dt.patron<<"; "<<dt.descripcion<<">";
  return os;
}


#endif
