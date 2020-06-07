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
  string route_actual_doc;
  ifstream reader_file;
  lexical_buffer in_buffer;

  CATlexical();
  ~CATlexical();

  void set_doc_to_read(string);
  void reader();
  void print();

};

CATlexical::CATlexical(){
  this->route_actual_doc = "";
}

CATlexical::~CATlexical(){
}

void CATlexical::set_doc_to_read(string new_route){
  this->route_actual_doc = new_route;
}


void CATlexical::reader(){

}

void CATlexical::print(){
  cout<<"Codigo en: "<<this->route_actual_doc<<endl;
}





#endif
