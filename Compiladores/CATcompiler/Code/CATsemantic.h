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

  CATsemantic(sintatic_tree*);
  ~CATsemantic();

  void print_tree();

};

CATsemantic::CATsemantic(sintatic_tree* _tree){
  this->inner_tree = _tree;
}

CATsemantic::~CATsemantic(){}

void CATsemantic::print_tree(){
  this->inner_tree->print_tree();
}
#endif
