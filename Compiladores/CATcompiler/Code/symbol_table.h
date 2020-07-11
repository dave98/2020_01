#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <iostream>
#include <vector>
#include <unordered_map>

#include "lexical_lexema.h"

using namespace std;

class symbol_table{
public:
  int scope_id; // Scope que puede definir esta tabla
  symbol_table* parent;
  vector<symbol_table*> childs;
  unordered_map<string, lexical_lexema*> tokens_in_enviroment;

  symbol_table(int, symbol_table*);
  ~symbol_table();

  void add_child_table(symbol_table*);
  bool is_identifier_in(string);
  void add_new_identifier(lexical_lexema*); // Be added only if its the first time in THIS table

  void print(int = 0);
};

symbol_table::symbol_table(int _scope_id, symbol_table* _parent){
  this->scope_id = _scope_id;
  this->parent = _parent;
  this->childs = vector<symbol_table*>(0, NULL);
}

symbol_table::~symbol_table(){}

void symbol_table::add_child_table(symbol_table* new_child){
  this->childs.push_back(new_child);
}

bool symbol_table::is_identifier_in(string identifier){
  if(this->tokens_in_enviroment.find(identifier) != this->tokens_in_enviroment.end()){ return true; }
  else{ return false; }
}

// Identifier lexemas has the following structure -> lexemas<id, description>
void symbol_table::add_new_identifier(lexical_lexema* new_lexema){
  if(!this->is_identifier_in(new_lexema->second())){
    this->tokens_in_enviroment.insert(make_pair(new_lexema->second(), new_lexema));
  }
  return;
}

void symbol_table::print(int deep){
  unordered_map<string, lexical_lexema*>::iterator it;
  cout<<"Deep: "<<deep<<endl;
  for(it = this->tokens_in_enviroment.begin(); it != this->tokens_in_enviroment.end(); it++){
    cout<<"("<<it->second->second()<<" "<<it->second->third()<<")";
  }
  cout<<endl<<endl;
  for(unsigned int i = 0; i < this->childs.size(); i++){
    this->childs[i]->print(deep+1);
  }

}

#endif
