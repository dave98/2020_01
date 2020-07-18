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
    void type_eval_get_type_tpdef(sintatic_node*, string*);
    void type_eval_get_type_defdef(sintatic_node*, string*);
    void type_eval_set_type_tpdef(sintatic_node* in_node, string* inherited_type);
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
  cout<<"CAT: Generacion completa de codigo"<<endl;
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
        this->semantic_symbol_table->add_new_identifier(in_node->lexema_to_semantic);
        in_node->lexema_table_location = this->semantic_symbol_table->actual;
      }
    }
    else if(in_node->parent->etiqueta == "TPDEF_SUB"){
      if(this->semantic_symbol_table->is_new_identifier_in_table(in_node->lexema_to_semantic)){
        this->global_error_manager->add_error(in_node->lexema_to_semantic->third(), 301);
      }else{
        this->semantic_symbol_table->add_new_identifier(in_node->lexema_to_semantic);
        in_node->lexema_table_location = this->semantic_symbol_table->actual;
      }
    }
    else if(in_node->parent->parent->etiqueta == "PRINCIPAL"){
    }
    else{
      if( ! this->semantic_symbol_table->is_new_identifier_in_table(in_node->lexema_to_semantic)){
        this->global_error_manager->add_error(in_node->lexema_to_semantic->third(), 302);
      }
      else{
        in_node->lexema_table_location = this->semantic_symbol_table->actual;
      }
    }
  }
  else if(in_node->etiqueta == "COMPOUND_STMT"){
    this->semantic_symbol_table->create_new_symbol_table();
  }
  else if(in_node->etiqueta == "fin"){
    this->semantic_symbol_table->go_back();
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
    string* type_for_branch = new string("none");
    this->type_eval_get_type_tpdef(in_node->pointing_childs.back(), type_for_branch);

    if(*type_for_branch == "str"){ in_node->pointing_childs.front()->lexema_to_semantic->descripcion = "string";}
    else{ in_node->pointing_childs.front()->lexema_to_semantic->descripcion = *type_for_branch;}

    this->type_eval_set_type_tpdef(in_node->pointing_childs[1], type_for_branch);
    this->type_eval_set_type_tpdef(in_node->pointing_childs[2], type_for_branch);
    delete type_for_branch;
    return;
  }

  else if(in_node->etiqueta == "DEFDEF"){
    string* type_for_branch_2 = new string("none");
    for(unsigned int i = 0; i < in_node->pointing_childs.size(); i++){
      this->type_eval_get_type_defdef(in_node->pointing_childs[i], type_for_branch_2);
    }
    delete type_for_branch_2;
    return;
  }
  else{
    for(unsigned int i = 0; i < in_node->pointing_childs.size(); i++){
      this->type_eval_navigator(in_node->pointing_childs[i]);
    }
  }
}

//TPDEF_SUB evaluator
void CATsemantic::type_eval_get_type_tpdef(sintatic_node* in_node, string* inherited_type){ // Type evaluator
  if(in_node->etiqueta == "num"){
    if(*inherited_type == "str"){
      this->global_error_manager->add_error(-1,304);
    }
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
  else if(in_node->etiqueta == "str"){
    if(*inherited_type == "int" || *inherited_type == "float"){
      this->global_error_manager->add_error(-1,304);
    }
    else{
      *inherited_type = "str";
    }
  }
  else if(in_node->etiqueta == "id"){
    //cout<<"TO: "<<in_node->etiqueta<<" - "<<in_node->lexema_to_semantic->second()<<" - "<<in_node->lexema_to_semantic->type<<endl;
    string temp_type = "";
    temp_type = in_node->lexema_table_location->get_type(in_node->lexema_to_semantic->second());
    if(temp_type == "int" || temp_type == "float" ){
      if(*inherited_type == "str"){
        this->global_error_manager->add_error(-1,304);
      }
      else{*inherited_type = temp_type;}
      return;
    }
    else if(temp_type == "str"){
      if(*inherited_type == "int" || *inherited_type == "float"){
        this->global_error_manager->add_error(-1,304);
      }
      else{
        *inherited_type = "str";
      }
    }
  }

  for(unsigned int i = 0; i < in_node->pointing_childs.size(); i++){
    this->type_eval_get_type_tpdef(in_node->pointing_childs[i], inherited_type);
  }
  return;
}

void CATsemantic::type_eval_set_type_tpdef(sintatic_node* in_node, string* inherited_type){
  if(in_node->etiqueta == "id" && (in_node->parent->etiqueta == "TPDEF" || in_node->parent->etiqueta == "TPDEF_SUB" )   ){
    in_node->lexema_table_location->associate_with_type(in_node->lexema_to_semantic->second(), *inherited_type);
    in_node->lexema_to_semantic->type = *inherited_type;
  return;
  }
  for(unsigned int i = 0; i < in_node->pointing_childs.size(); i++){
    this->type_eval_set_type_tpdef(in_node->pointing_childs[i], inherited_type);
  }
  return;
}

void CATsemantic::type_eval_get_type_defdef(sintatic_node* in_node, string* inherited_type){ // Type evaluator
  //cout<<"INNODE->E: "<<in_node->etiqueta<<endl;
  if(in_node->etiqueta == "num"){
    if(*inherited_type == "str"){
      this->global_error_manager->add_error(-1,304);
    }
    else{ *inherited_type = "num"; }
  }
  else if(in_node->etiqueta == "str"){
    if(*inherited_type == "num"){
      this->global_error_manager->add_error(-1,304);
    }
    else{ *inherited_type = "str"; }
  }
  else if(in_node->etiqueta == "id"){
    string temp_type = "";
    temp_type = in_node->lexema_table_location->get_type(in_node->lexema_to_semantic->second());
    if(temp_type == ""){this->global_error_manager->add_error(-1, 305);}
    else{
      if(temp_type == "int" || temp_type == "float" ){
        if(*inherited_type == "str"){
          this->global_error_manager->add_error(-1,304);
        }
        else if(*inherited_type == "num"){}
        else{*inherited_type = temp_type;}
        return;
      }

      else if(temp_type == "str"){
        if(*inherited_type == "int" || *inherited_type == "float" || * inherited_type == "num"){
          this->global_error_manager->add_error(-1,304);
        }
        else{
          *inherited_type = "str";
        }
      }
    }
  }

  for(unsigned int i = 0; i < in_node->pointing_childs.size(); i++){
    this->type_eval_get_type_defdef(in_node->pointing_childs[i], inherited_type);
  }

}



#endif
