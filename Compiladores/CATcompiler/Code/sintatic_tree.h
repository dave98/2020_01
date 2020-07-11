#ifndef SINTATIC_TREE_H
#define SINTATIC_TREE_H

#include<iostream>
#include<vector>
#include<string>

#include"sintatic_node.h"
#include"m_functions.h"
#include"lexical_lexema.h"

using namespace std;

class sintatic_tree{
public:
  sintatic_node* root;
  sintatic_node* actual;
  bool is_tree_usable;
  bool root_reached;

  sintatic_tree();
  ~sintatic_tree();

  void insert(string, vector<string>, lexical_lexema*, bool=false);

  string down_to_first_child();
  sintatic_node* go_next(sintatic_node*);
  void insert_lambda();


  //---------------- PRINT TREE TOOLS ------------------------
  void print_tree();
  void set_tree_tranversal(sintatic_node*, int, bool = false);
};


sintatic_tree::sintatic_tree(){
  this->root = NULL;
  this->actual = NULL;
  this->is_tree_usable = true;
  this->root_reached = false;
}

sintatic_tree::~sintatic_tree(){}

void sintatic_tree::insert(string _etiqueta, vector<string> _explicit_childs, lexical_lexema* _lexema, bool debug){
  //cout<<"-->"<<*_lexema<<"<--"<<endl;
  if(!this->is_tree_usable){cout<<"Error: Arbol inutilizable"<<endl; return;}
  else{
    if(this->root == NULL){
      sintatic_node* temp_node = new sintatic_node(_etiqueta, _explicit_childs, NULL, _lexema);
      this->root = temp_node;
      this->actual = temp_node;
      if(debug){cout<<"\tRaiz creada"<<endl;}
    }
    else{
      if(this->down_to_first_child() == _etiqueta){
        sintatic_node* temp_node = new sintatic_node(_etiqueta, _explicit_childs, this->actual, _lexema);
        this->actual->add_pointing_child(temp_node);
        this->actual = temp_node;
        if(debug){cout<<"\tInserccion normal -> OP1"<<endl;}
      }
      else{
        this->actual = this->go_next(this->actual);
        if(this->actual != NULL){
          if(this->actual->explicit_childs[this->actual->next_to_choose] == _etiqueta){
            sintatic_node* temp_node = new sintatic_node(_etiqueta, _explicit_childs, this->actual, _lexema);
            this->actual->add_pointing_child(temp_node);
            this->actual = temp_node;
            if(debug){cout<<"\tInserccion siguiente -> OP2"<<endl;}
          }
          else{
            this->is_tree_usable = false;
            cout<<"\tIncongrueencia de inserccion"<<endl;
          }
        }
        else{
          this->is_tree_usable = false;
          this->root_reached = true;
          cout<<"\tArbol sintactico: Raiz alcanzada"<<endl;
        }
      }

      if(this->is_tree_usable && (this->down_to_first_child() == "lambda")){
        if(debug){cout<<"\tInserccion lambda -> OP3"<<endl;}
        this->insert_lambda();
      }
    }
  }
}


string sintatic_tree::down_to_first_child(){
  if(this->actual->explicit_childs.size() == 0){
    return "";
  }
  else{
    return this->actual->explicit_childs[0];
  }
}

sintatic_node* sintatic_tree::go_next(sintatic_node* recursive_current_node){
  if (recursive_current_node->get_parent() != NULL){
    sintatic_node* temp_parent = recursive_current_node->get_parent();
    if((unsigned)temp_parent->next_to_choose < temp_parent->explicit_childs.size()){
      return temp_parent;
    }
    else{
      return this->go_next(temp_parent);
    }
  }
  else{
    return NULL;
  }
}

void sintatic_tree::insert_lambda(){
  lexical_lexema* empty_lexema = new lexical_lexema("");

  sintatic_node* temp_node = new sintatic_node("lambda", vector<string>{}, this->actual, empty_lexema);
  this->actual->add_pointing_child(temp_node);
}

void sintatic_tree::print_tree(){
  if(this->root == NULL){
    cout<<"No hay arbol que mostrar"<<endl;
    return;
  }
  else{
    this->set_tree_tranversal(this->root, 0, false);
    return;
  }
}

void sintatic_tree::set_tree_tranversal(sintatic_node* start_from, int order, bool debug){
  cout<<order<<": "<<start_from->etiqueta<<" --> "; print_vector(start_from->explicit_childs); cout<<endl;
  for(unsigned int i = 0; i < start_from->pointing_childs.size(); i++){
    this->set_tree_tranversal(start_from->pointing_childs[i], order+1, debug);
  }
}



#endif
