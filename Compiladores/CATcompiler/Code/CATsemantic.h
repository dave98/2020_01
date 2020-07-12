#ifndef CATSEMANTIC_H
#define CATSEMANTIC_H

#include <iostream>
#include <vector>
#include <string>

#include "sintatic_tree.h"
#include "lexical_lexema.h"

using namespace std;

class CATsemantic{
public:
  sintatic_tree* inner_tree;
  string translated_code_file;

  ofstream writer;

  CATsemantic(sintatic_tree*);
  ~CATsemantic();

  void print_tree();
  void generate_code();

};

// At this we got something in tree -> Tree is not empty
CATsemantic::CATsemantic(sintatic_tree* _tree){
  this->inner_tree = _tree;
  this->translated_code_file = "generated_code.cpp";
}


CATsemantic::~CATsemantic(){}

void CATsemantic::print_tree(){
  this->inner_tree->print_tree();
}

void CATsemantic::generate_code(){
  this->writer = ofstream(this->translated_code_file);

  // Adding basic librarias to work in c++
  this->writer << "// This program was first processed in CAT compiler <-- Greetings from Dave " << endl;
  this->writer << "#include <iostream>" <<endl;
  this->writer << "#include <vector>" <<endl;
  this->writer << "#include <string>" <<endl<<endl;
  this->writer << "using namespace std;"<<endl;

}


#endif
