#ifndef SEMANTIC_CONTEXT_H
#define SEMANTIC_CONTEXT_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class semantic_context{
public:
  ofstream* writer;

  semantic_context(ofstream*);
  ~semantic_context();
};

semantic_context::semantic_context(ofstream* _writer){
  this->writer = _writer;
}
semantic_context::~semantic_context(){}



#endif
