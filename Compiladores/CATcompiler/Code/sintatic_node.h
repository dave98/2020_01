#ifndef SINTATIC_NODE_H
#define SINTATIC_NODE_H

#include <iostream>
#include <vector>
#include <string>

#include "lexical_lexema.h"
#include "symbol_table.h"

using namespace std;

class sintatic_node{
public:
  string etiqueta;
  vector<string> explicit_childs;

  int next_to_choose;
  sintatic_node* parent;
  vector<sintatic_node*> pointing_childs;
  lexical_lexema* lexema_to_semantic;
  symbol_table* lexema_table_location;

  sintatic_node(string, vector<string>, sintatic_node*, lexical_lexema*);
  ~sintatic_node();

  void add_pointing_child(sintatic_node*);
  void set_parent(sintatic_node*);
  sintatic_node* get_parent();
};


sintatic_node::sintatic_node(string _etiqueta, vector<string> _explicit_childs, sintatic_node* _parent, lexical_lexema* _lexema){
  this->etiqueta = _etiqueta;
  this->explicit_childs = _explicit_childs;

  this->next_to_choose = 0;
  this->parent = _parent;
  this->pointing_childs = vector<sintatic_node*>(0, NULL);

  this->lexema_to_semantic = _lexema;
  this->lexema_table_location = NULL;
}

sintatic_node::~sintatic_node(){}

void sintatic_node::add_pointing_child(sintatic_node* new_child){
  this->pointing_childs.push_back(new_child);
  this->next_to_choose += 1;
}

void sintatic_node::set_parent(sintatic_node* new_parent){
  this->parent = new_parent;
}

sintatic_node* sintatic_node::get_parent(){
  return this->parent;
}


#endif
