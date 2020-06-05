#ifndef CATLEXICAL_H
#define CATLEXICAL_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class CATlexical{
public:
  string inner_message;
  CATlexical();
  ~CATlexical();
};

CATlexical::CATlexical(){
  this->inner_message = "Analizador";
  cout<<this->inner_message<<endl;
}

CATlexical::~CATlexical(){
}


#endif
