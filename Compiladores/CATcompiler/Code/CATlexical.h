#ifndef CATLEXICAL_H
#define CATLEXICAL_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "lexical_buffer.h"

using namespace std;

class CATlexical{
public:
  string route_actual_doc;      // Ruta hacia el documento actual siendo leido
  ifstream file_reader;         // ifstream de lectura
  lexical_buffer* in_buffer;     // Contenedor in_pair de statements

  CATlexical();
  ~CATlexical();

  void set_doc_to_read(string);  // Setea el documento a leer actualmente
  void reader();                 // Leer documento linea por linea y setear por buffer
    string reader_helper();      // Obtiene una linea del cdocumento
  void print();                  // Información del objeto

};

CATlexical::CATlexical(){
  this->route_actual_doc = "";
  this->in_buffer = new lexical_buffer();
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
    int i = 0;
    while(true){
      current_statement = this->reader_helper();
      //cout<<"->"<<current_statement<<"<-->\t"<<current_statement.size()<<endl;
      for(unsigned int j = 0; j < current_statement.size(); j++){
        if(current_statement[j] == ' '){
          cout<<"->"<<"SPC"<<"<-";
        }
        else{
          cout<<"->"<<current_statement[j]<<"<-";
        }
      }
      cout<<endl;
      cout<<"----------"<<endl;
      cout<<"----------"<<endl;

      if (current_statement != "eof"){
        this->in_buffer->fill_buffer(current_statement);
        //cout<<i<<": ";
        //this->in_buffer->print_actual_buffer();
        i++;
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



void CATlexical::print(){
  cout<<"Codigo en: "<<this->route_actual_doc<<endl;
}





#endif
