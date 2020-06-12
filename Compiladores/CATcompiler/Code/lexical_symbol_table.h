#ifndef LEXICAL_SYMBOL_TABLE_H
#define LEXICAL_SYMBOL_TABLE_H

#include <iostream>
#include <vector>
#include <unordered_map>

#include "lexical_lexema.h"
using namespace std;

class lexical_symbol_table{
public:
  lexical_symbol_table* parent;
  lexical_symbol_table* son;

  string table_type;
  string enviroment_name;

  unordered_map<string, lexical_lexema*> enviroment_tokens;

  lexical_symbol_table(string);
  lexical_symbol_table(string, lexical_symbol_table*);
  ~lexical_symbol_table();
};

lexical_symbol_table::lexical_symbol_table(string _enviroment_name){
  this->enviroment_name = _enviroment_name;
  if(this->enviroment_name == "principal"){
    this->table_type = "principal";
  }
  else if(this->enviroment_name == "funcion"){
    this->table_type = "funcion";
  }
  else{
    this->table_type = "standard";
  }
}

#endif
