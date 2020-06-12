#ifndef CATLEXICAL_H
#define CATLEXICAL_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <regex>
#include <functional>

#include "lexical_buffer.h"
#include "lexical_lexema.h"

using namespace std;
typedef void (*pfunc)();

void sisi();

class CATlexical{
public:
  string route_actual_doc;      // Ruta hacia el documento actual siendo leido
  ifstream file_reader;         // ifstream de lectura
  lexical_buffer* in_buffer;     // Contenedor in_pair de statements
  regex re_word;
  regex re_number;

  vector<lexical_lexema*> lexema_for_sintactic;
  unordered_map<string, function<void()> > reserved_words;

  CATlexical();
      void initialize_dictionary();
  ~CATlexical();

  void set_doc_to_read(string);  // Setea el documento a leer actualmente
  void reader();                 // Leer documento linea por linea y setear por buffer
    string reader_helper();      // Obtiene una linea del documento
    void process_line(int = 0);         // Procesa la línea de codigo en el buffer_actual
      void process_words();
      void process_numbers();
      bool words(string);
      bool numbers(string);
        void si(); // Tratamiento para if
        void sino();
        void mientras();
        void para();
        void entonces();
        void yy();
        void oo();
        void principal();
        void funcion();
        void retorna();
        void variable();
  void print();                  // Información del objeto

};

CATlexical::CATlexical(){
  this->route_actual_doc = "";
  this->in_buffer = new lexical_buffer();
  this->lexema_for_sintactic = vector<lexical_lexema*>(0, NULL);
  this->re_word = regex("[a-zA-Z]+");
  this->re_number = regex("[0-9]*.[0-9]+");
  this->initialize_dictionary();
}

void CATlexical::initialize_dictionary(){
  this->reserved_words["si"] =        bind(&CATlexical::si, this);
  this->reserved_words["sino"] =      bind(&CATlexical::sino, this);
  this->reserved_words["mientras"] =  bind(&CATlexical::mientras, this);
  this->reserved_words["para"] =      bind(&CATlexical::para, this);
  this->reserved_words["entonces"] =  bind(&CATlexical::entonces, this);
  this->reserved_words["yy"] =        bind(&CATlexical::yy, this);
  this->reserved_words["oo"] =        bind(&CATlexical::oo, this);
  this->reserved_words["principal"] = bind(&CATlexical::principal, this);
  this->reserved_words["funcion"] =   bind(&CATlexical::funcion, this);
  this->reserved_words["retorna"] =   bind(&CATlexical::retorna, this);
  this->reserved_words["variable"] =  bind(&CATlexical::variable, this);
}


CATlexical::~CATlexical(){
}

void CATlexical::set_doc_to_read(string new_route){
  this->route_actual_doc = new_route;
}


void CATlexical::reader(){
  this->file_reader = ifstream(this->route_actual_doc);
  if(!file_reader.is_open()){this->route_actual_doc = "";}

  if(this->route_actual_doc == ""){
    cout<<"Ruta no especifica o inexistente"<<endl;
    return;
  }
  else{
    string current_statement = "";
    int actual_line = 0;
    while(true){
      current_statement = this->reader_helper();
      if (current_statement != "eof"){
        this->in_buffer->fill_buffer(current_statement);
        this->process_line(actual_line);
        //cout<<i<<": "<<this->in_buffer->get_actual_buffer_size()<<" ";
        //cout<<i<<": "<<this->in_buffer->get_scope()<<" ";
        //this->in_buffer->print_actual_buffer();
        actual_line++;
      }
      else{
        break;
      }
    }
  }
}

// Funciona en base al apuntador ifstream: this->file_reader
// Conforme va leendo el apuntador alamacena su posición actual
string CATlexical::reader_helper(){
  string answer = "";
  if( !getline(this->file_reader, answer).eof()){
    return answer;
  }
  else{
    return "eof";
  }
}

// Procesamiento será realizado línea por linea
void CATlexical::process_line(int line_id){
  int scope_in_line = this->in_buffer->get_scope();

  cout<<line_id<<": ";

  if(scope_in_line == -1){ // Linea vacía
    cout<<"EMPTY"<<endl;
    return;
  }
  // At this point we know there is something in the line
  this->process_words();

}

void CATlexical::process_words(){
  string in_word = "";
  in_word += this->in_buffer->get_next();
  while(this->words(in_word)){
    in_word += this->in_buffer->get_next();
  }
  this->in_buffer->go_back();
  in_word.pop_back();

  cout<<"Palabra captada: "<<in_word<<"|"<<endl;
  cout<<"Next in: "<<this->in_buffer->get_next()<<endl;
  unordered_map<string, function<void()>>::iterator it = this->reserved_words.find(in_word);
  if(it != this->reserved_words.end()){
    this->reserved_words[in_word]();
  }
  else if(this->words(in_word)){
    cout<<"Creando identificador: "<<in_word<<endl;
  }
  else{
    cout<<"Verificando nuevos tipos"<<endl;
  }
}

void CATlexical::si(){
  cout<<"Creando token si"<<endl;
}

void CATlexical::sino(){
  cout<<"Creando token sino"<<endl;
}

void CATlexical::mientras(){
  cout<<"Creando token mientras"<<endl;
}

void CATlexical::para(){
  cout<<"Creando token para"<<endl;
}

void CATlexical::entonces(){
  cout<<"Creando token entonces"<<endl;
}

void CATlexical::yy(){
  cout<<"Creando token yy"<<endl;
}

void CATlexical::oo(){
  cout<<"Creando token oo"<<endl;
}

void CATlexical::principal(){
  cout<<"Creando token principal"<<endl;
}

void CATlexical::funcion(){
  cout<<"Creando token funcion"<<endl;
}

void CATlexical::retorna(){
  cout<<"Creando token retorna"<<endl;
}

void CATlexical::variable(){
  cout<<"Creando token variable"<<endl;
}

void CATlexical::process_numbers(){
}



bool CATlexical::words(string in_word){
  if(regex_match(in_word, this->re_word)){
    return true;
  }
  else{
    return false;
  }
}


bool CATlexical::numbers(string in_word){
  regex re("[0-9]*.[0-9]+");
  if(regex_match(in_word, re)){
    return true;
  }
  else{
    return false;
  }

}

void CATlexical::print(){
  cout<<"Codigo en: "<<this->route_actual_doc<<endl;
}

#endif
