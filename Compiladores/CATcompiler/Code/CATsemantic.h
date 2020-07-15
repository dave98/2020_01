#ifndef CATSEMANTIC_H
#define CATSEMANTIC_H

#include <iostream>
#include <vector>
#include <string>

#include "sintatic_tree.h"
#include "lexical_lexema.h"
#include "semantic_interpreter.h"
#include "semantic_context.h"

using namespace std;

class CATsemantic{
public:
  sintatic_tree* inner_tree;
  string translated_code_file;
  S* interpreter_root;
  semantic_context* context;

  ofstream* writer;

  CATsemantic(sintatic_tree*);
  ~CATsemantic();

  void print_tree();
  void interpreter_evaluation();
  void generate_code();
  void type_eval();
  void set_w();

};

// At this we got something in tree -> Tree is not empty
CATsemantic::CATsemantic(sintatic_tree* _tree){
  this->inner_tree = _tree;
  this->translated_code_file = "generated_code.cpp";
  this->writer = new ofstream(this->translated_code_file);
  this->context = new semantic_context(this->writer);
  this->interpreter_root = new S(this->inner_tree->root, this->context);
}


CATsemantic::~CATsemantic(){}

void CATsemantic::print_tree(){
  this->inner_tree->print_tree();
}

void CATsemantic::interpreter_evaluation(){
  this->interpreter_root->interprets();
}

void CATsemantic::generate_code(){
  // Adding basic librarias to work in c++
  *this->writer << "// ------------------------------------------------------------------------- // " << endl;
  *this->writer << "// This program was first processed in CAT compiler <-- Greetings from Dave  //" << endl;
  *this->writer << "// ------------------------------------------------------------------------- // " << endl;
  *this->writer << "#include <iostream>" <<endl;
  *this->writer << "#include <vector>" <<endl;
  *this->writer << "#include <string>" <<endl<<endl;
  *this->writer << "using namespace std;"<<endl<<endl;
  //*this->writer << "void main(){"<<endl;

  this->interpreter_evaluation();
  //*this->writer << "}"<<endl;

}

void CATsemantic::type_eval(){

}




//void random_function(os)

#endif
