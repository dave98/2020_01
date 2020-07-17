#ifndef CATSEMANTIC_H
#define CATSEMANTIC_H

#include <iostream>
#include <vector>
#include <string>

#include "CATerror_manager.h"
#include "sintatic_tree.h"
#include "sintatic_node.h"
#include "lexical_lexema.h"
#include "semantic_interpreter.h"
#include "semantic_context.h"
#include "supervisor_symbol_table.h"
#include "m_functions.h"

using namespace std;

class CATsemantic{
public:
  sintatic_tree* inner_tree;
  string translated_code_file;
  S* interpreter_root;
  semantic_context* context;

  CATerror_manager* global_error_manager;
  supervisor_symbol_table* semantic_symbol_table;

  ofstream* writer;

  CATsemantic(sintatic_tree*, CATerror_manager*);
  ~CATsemantic();

  void print_tree();
  void interpreter_evaluation();
  void generate_code();


  void symbol_verification(); // Interface
    void symbol_verification_navigator(sintatic_node*);

  void type_eval();
    void type_eval_navigator(sintatic_node*);
    void type_eval_get_type(sintatic_node*, string*);
};

// At this we got something in tree -> Tree is not empty
CATsemantic::CATsemantic(sintatic_tree* _tree, CATerror_manager* _error_handler){
  this->inner_tree = _tree;
  this->translated_code_file = "generated_code.cpp";
  this->writer = new ofstream(this->translated_code_file);
  this->context = new semantic_context(this->writer);

  this->global_error_manager = _error_handler;
  this->semantic_symbol_table = new supervisor_symbol_table(_error_handler);

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

  this->interpreter_evaluation();
}

// Symbol verification
void CATsemantic::symbol_verification(){
  this->symbol_verification_navigator(this->inner_tree->root);
}

void CATsemantic::symbol_verification_navigator(sintatic_node* in_node){
  if(in_node->etiqueta == "id"){
    if(in_node->parent->etiqueta == "TPDEF"){
      if(this->semantic_symbol_table->is_new_identifier_in_table(in_node->lexema_to_semantic)){
        this->global_error_manager->add_error(in_node->lexema_to_semantic->third(), 301);
      }else{
        //cout<<"Adding variable: "<<in_node->lexema_to_semantic->second()<<endl;
        this->semantic_symbol_table->add_new_identifier(in_node->lexema_to_semantic);
      }
    }
    else if(in_node->parent->etiqueta == "TPDEF_SUB"){
      if(this->semantic_symbol_table->is_new_identifier_in_table(in_node->lexema_to_semantic)){
        this->global_error_manager->add_error(in_node->lexema_to_semantic->third(), 301);
      }else{
        //cout<<"Adding variable multiples: "<<in_node->lexema_to_semantic->second()<<endl;
        this->semantic_symbol_table->add_new_identifier(in_node->lexema_to_semantic);
      }
    }
    else if(in_node->parent->parent->etiqueta == "PRINCIPAL"){
      //cout<<"RETURN VALUE FOUNDED"<<endl;
    }
    else{
      if( ! this->semantic_symbol_table->is_new_identifier_in_table(in_node->lexema_to_semantic)){
        this->global_error_manager->add_error(in_node->lexema_to_semantic->third(), 302);
        //cout<<"Identicador en tabla: "<<in_node->lexema_to_semantic->second()<<endl;
      }
    }
  }
  else if(in_node->etiqueta == "COMPOUND_STMT"){
    this->semantic_symbol_table->create_new_symbol_table();
    //cout<<in_node->pointing_childs[0]->etiqueta<<endl;
    //cout<<"New table created"<<endl;
  }
  else if(in_node->etiqueta == "fin"){
    this->semantic_symbol_table->go_back();
    //cout<<"New table closed"<<endl;
  }



  for(unsigned int i = 0; i < in_node->pointing_childs.size(); i++){
    this->symbol_verification_navigator(in_node->pointing_childs[i]);
  }

}

// Eval type
void CATsemantic::type_eval(){ // Interface
  this->type_eval_navigator(this->inner_tree->root);
}

void CATsemantic::type_eval_navigator(sintatic_node* in_node){ // Tree navigator
  if(in_node->etiqueta == "TPDEF"){
    string* type_for_branch = new string("string");
    // Back shall be TPDEF_SUB
    this->type_eval_get_type(in_node->pointing_childs.back(), type_for_branch);
    //cout<<"Type gone from string to "<<*type_for_branch<<endl;
    // Front shall be variable;
    in_node->pointing_childs.front()->lexema_to_semantic->descripcion = *type_for_branch;
    return;
  }
  else{
    for(unsigned int i = 0; i < in_node->pointing_childs.size(); i++){
      this->type_eval_navigator(in_node->pointing_childs[i]);
    }
  }
}

//TPDEF_SUB evaluator
void CATsemantic::type_eval_get_type(sintatic_node* in_node, string* inherited_type){ // Type evaluator
  if(in_node->etiqueta == "num"){
    if( is_float( in_node->lexema_to_semantic->second() )   ){
      *inherited_type = "float";
    }
    else{
      if(*inherited_type != "float"){
        *inherited_type = "int";
      }
    }
    return;
  }
  for(unsigned int i = 0; i < in_node->pointing_childs.size(); i++){
    this->type_eval_get_type(in_node->pointing_childs[i], inherited_type);
  }
  return;
}



#endif
