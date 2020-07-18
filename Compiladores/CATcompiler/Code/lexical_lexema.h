#ifndef LEXICAL_LEXEMA_H
#define LEXICAL_LEXEMA_H

#include<iostream>
#include<string>
using namespace std;

class lexical_lexema{
public:
  string patron;
  string descripcion;
  int line;
  string type;

  lexical_lexema(string);
  lexical_lexema(string, string);
  lexical_lexema(string, string, int);
  string first();
  string second();
  int third();
  ~lexical_lexema();

  friend ostream& operator << (ostream& os, const lexical_lexema& dt);
};


lexical_lexema::lexical_lexema(string _patron){
  this->patron = _patron;
  this->descripcion = "";
  this->line = -1;
  this->type = "";
}


lexical_lexema::lexical_lexema(string _patron, string _descripcion){
  this->patron = _patron;
  this->descripcion = _descripcion;
  this->line = -1;
  this->type = "";

}


lexical_lexema::lexical_lexema(string _patron, string _descripcion, int _line){
  this->patron = _patron;
  this->descripcion = _descripcion;
  this->line = _line;
  this->type = "";
}

lexical_lexema::~lexical_lexema(){

}

string lexical_lexema::first(){
  return this->patron;
}

string lexical_lexema::second(){
  return this->descripcion;
}

int lexical_lexema::third(){
  return this->line;
}

ostream& operator << (ostream& os, const lexical_lexema& dt){
  os<<"<"<<dt.patron<<"; "<<dt.descripcion<<">";
  return os;
}


#endif
