#ifndef SUPERVISOR_SYMBOL_TABLE
#define SUPERVISOR_SYMBOL_TABLE

#include <iostream>
#include <vector>
#include <unordered_map>

#include "symbol_table.h"
#include "lexical_lexema.h"
#include "CATerror_manager.h"

class supervisor_symbol_table{
public:
  int current_scope;
  symbol_table* root;
  symbol_table* actual;
  CATerror_manager* global_error_manager;

  supervisor_symbol_table(CATerror_manager*);
  ~supervisor_symbol_table();

  void add_new_identifier(lexical_lexema*);
  bool is_new_identifier_in_table(lexical_lexema*);
  void create_new_symbol_table();
  int evaluate_scope(int);
  void go_back();
  void update_supervisor(int);

  void print();
  void associate_with_type(string, string); //Link a identifier with its type
  string get_type(string); //Link a identifier with its type
};

supervisor_symbol_table::supervisor_symbol_table(CATerror_manager* error_incoming){
  this->current_scope = 0;
  this->root = new symbol_table(current_scope, NULL);
  this->actual = root;
  this->global_error_manager = error_incoming;
}

supervisor_symbol_table::~supervisor_symbol_table(){}

void supervisor_symbol_table::add_new_identifier(lexical_lexema* new_lexema){
  this->actual->add_new_identifier(new_lexema);
}

bool supervisor_symbol_table::is_new_identifier_in_table(lexical_lexema* new_lexema){
  if(new_lexema->second() == ""){
    this->global_error_manager->add_error(new_lexema->third(), 303);
    //cout<<"Supervisor table got nothing to compair in symbol table"<<endl;
  }
  if(this->actual->is_identifier_in(new_lexema->second())){return true;}
  else{return false;}
}

void supervisor_symbol_table::create_new_symbol_table(){
  this->current_scope++;
  symbol_table* new_scope = new symbol_table(current_scope, this->actual);
  this->actual->add_child_table(new_scope);

  unordered_map<string, lexical_lexema*>::iterator it;
  for(it = this->actual->tokens_in_enviroment.begin(); it != this->actual->tokens_in_enviroment.end(); it++){
    new_scope->add_new_identifier(it->second);
  }
  this->actual = new_scope;
}

int supervisor_symbol_table::evaluate_scope(int in_scope){
  int temp_scope = in_scope - this->current_scope;
  return temp_scope;
}

void supervisor_symbol_table::go_back(){
  if(!this->actual->parent){
    this->global_error_manager->add_error(-1, 104);
    return;
  }
  else{
    this->current_scope--;
    this->actual = this->actual->parent;
  }
}

void supervisor_symbol_table::update_supervisor(int scope){
  int new_scope = this->evaluate_scope(scope);
  if(new_scope == 1){
    //cout<<"New table is being created."<<endl;
    this->create_new_symbol_table();
  }
  else if(new_scope == 0){
    //cout<<"Keeping the same table."<<endl;
    // Everything fine
  }
  else if(new_scope == -1){
    //cout<<"Go to previousn table."<<endl;
    this->go_back();
  }
  else{
    this->global_error_manager->add_error(-1, 105);
  }
}

void supervisor_symbol_table::print(){
  this->root->print();
}

void supervisor_symbol_table::associate_with_type(string _identifier, string _types){
  if(!this->actual->associate_with_type(_identifier, _types)){
    this->global_error_manager->add_error(-1, 306);
  }
}


string supervisor_symbol_table::get_type(string _identifier){
  return this->actual->get_type(_identifier);
}


















#endif
