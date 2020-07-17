#ifndef SEMANTIC_INTERPRETER_H
#define SEMANTIC_INTERPRETER_H

#include <iostream>
#include <vector>
#include <string>
#include "sintatic_node.h"
#include "sintatic_tree.h"
#include "semantic_context.h"

using namespace std;

//--------------------------------------ABSTRACT BASE -------------------------------------
class AbstractBase{
public:
  AbstractBase();
  ~AbstractBase();
  virtual void interprets() = 0;
};

AbstractBase::AbstractBase(){}
AbstractBase::~AbstractBase(){}

//--------------------------------------TERMINAL NODE -------------------------------------
class TerminalNode : public AbstractBase{
public:
  sintatic_node* NTnode;
  semantic_context* NTcontext;


  TerminalNode(sintatic_node*, semantic_context*);
  ~TerminalNode();
  virtual void interprets();
};

inline TerminalNode::TerminalNode(sintatic_node* _NTnode, semantic_context* _semantic_context){
  this->NTnode = _NTnode;
  this->NTcontext = _semantic_context;
}

inline TerminalNode::~TerminalNode(){}

inline void TerminalNode::interprets(){
  //*this->NTcontext->writer << this->NTnode->etiqueta<<endl;
  //cout<<"Look in: "<<this->NTnode->etiqueta<<endl;

}

//--------------------------------------NON TERMINAL BASE -------------------------------------
class NonTerminalNode : public AbstractBase{
public:
  sintatic_node* NTnode;
  semantic_context* NTcontext;

  NonTerminalNode(sintatic_node*, semantic_context*);
  ~NonTerminalNode();
  virtual void interprets();
};

inline NonTerminalNode::NonTerminalNode(sintatic_node* _NTnode, semantic_context* _semantic_context){
  this->NTnode = _NTnode;
  this->NTcontext = _semantic_context;
}

inline NonTerminalNode::~NonTerminalNode(){}

inline void NonTerminalNode::interprets(){
  //cout <<"Look for: " <<this->NTnode->etiqueta<< " ON: "<<this->NTnode->pointing_childs[0]->etiqueta<<endl;
  if(this->NTnode->pointing_childs.size() == 0){
    TerminalNode(this->NTnode, this->NTcontext).interprets();
  }
  else{
    //cout <<"Look for: " <<this->NTnode->etiqueta<< " :: ";
    for(unsigned int i = 0; i < this->NTnode->pointing_childs.size(); i++){
      cout<<this->NTnode->pointing_childs[i]->etiqueta<<" ";
    }
    cout<<endl;
    //cout<<"From NonTerminalNode: "<<this->NTnode->etiqueta<<endl;
    //*this->NTcontext->writer << this->NTnode->etiqueta <<endl;
    for(unsigned int i = 0; i < this->NTnode->pointing_childs.size(); i++){
      NonTerminalNode(this->NTnode->pointing_childs[i], this->NTcontext).interprets();
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------- NON TERMINALS (Declaration) ---------------------------------------------------------------
// AT THIS POINT THE COMPILER WILL START TO WORK ONLY WITH THIS COMPILER

class S : public NonTerminalNode{
public:
  using NonTerminalNode::NonTerminalNode;  // Construtor inheritance, be sure using c++11
  void interprets();
};

class PRINCIPAL : public NonTerminalNode{
public:
  using NonTerminalNode::NonTerminalNode;  // Construtor inheritance, be sure using c++11
  void interprets();
};

class STMT : public NonTerminalNode{
public:
  using NonTerminalNode::NonTerminalNode;  // Construtor inheritance, be sure using c++11
  void interprets();
};

class SIMPLE_STMT : public NonTerminalNode{
public:
  using NonTerminalNode::NonTerminalNode;  // Construtor inheritance, be sure using c++11
  void interprets();
};

class ONLY_SSTMT : public NonTerminalNode{
public:
  using NonTerminalNode::NonTerminalNode;  // Construtor inheritance, be sure using c++11
  void interprets();
};

class COMPOUND_STMT : public NonTerminalNode{
public:
  using NonTerminalNode::NonTerminalNode;  // Construtor inheritance, be sure using c++11
  void interprets();
};

class IFEX2 : public NonTerminalNode{
public:
  using NonTerminalNode::NonTerminalNode;  // Construtor inheritance, be sure using c++11
  void interprets();
};

class NEX : public NonTerminalNode{
public:
  using NonTerminalNode::NonTerminalNode;  // Construtor inheritance, be sure using c++11
  void interprets();
};

class NEX_EP : public NonTerminalNode{
public:
  using NonTerminalNode::NonTerminalNode;  // Construtor inheritance, be sure using c++11
  void interprets();
};

class NEX_T : public NonTerminalNode{
public:
  using NonTerminalNode::NonTerminalNode;  // Construtor inheritance, be sure using c++11
  void interprets();
};

class NEX_TP : public NonTerminalNode{
public:
  using NonTerminalNode::NonTerminalNode;  // Construtor inheritance, be sure using c++11
  void interprets();
};

class NEX_F : public NonTerminalNode{
public:
  using NonTerminalNode::NonTerminalNode;  // Construtor inheritance, be sure using c++11
  void interprets();
};

class TPDEF : public NonTerminalNode{
public:
  using NonTerminalNode::NonTerminalNode;  // Construtor inheritance, be sure using c++11
  void interprets();
};

class TPDEF_SUB : public NonTerminalNode{
public:
  using NonTerminalNode::NonTerminalNode;  // Construtor inheritance, be sure using c++11
  void interprets();
};

class DEFDEF : public NonTerminalNode{
public:
  using NonTerminalNode::NonTerminalNode;  // Construtor inheritance, be sure using c++11
  void interprets();
};

class EqualTo : public NonTerminalNode{
public:
  using NonTerminalNode::NonTerminalNode;  // Construtor inheritance, be sure using c++11
  void interprets();
};

class E : public NonTerminalNode{
public:
  using NonTerminalNode::NonTerminalNode;  // Construtor inheritance, be sure using c++11
  void interprets();
};

class Ep : public NonTerminalNode{
public:
  using NonTerminalNode::NonTerminalNode;  // Construtor inheritance, be sure using c++11
  void interprets();
};

class T : public NonTerminalNode{
public:
  using NonTerminalNode::NonTerminalNode;  // Construtor inheritance, be sure using c++11
  void interprets();
};

class Tp : public NonTerminalNode{
public:
  using NonTerminalNode::NonTerminalNode;  // Construtor inheritance, be sure using c++11
  void interprets();
};

class F : public NonTerminalNode{
public:
  using NonTerminalNode::NonTerminalNode;  // Construtor inheritance, be sure using c++11
  void interprets();
};

class SEqual : public NonTerminalNode{
public:
  using NonTerminalNode::NonTerminalNode;  // Construtor inheritance, be sure using c++11
  void interprets();
};

class AAsig : public NonTerminalNode{
public:
  using NonTerminalNode::NonTerminalNode;  // Construtor inheritance, be sure using c++11
  void interprets();
};

class SComp : public NonTerminalNode{
public:
  using NonTerminalNode::NonTerminalNode;  // Construtor inheritance, be sure using c++11
  void interprets();
};

class BComp : public NonTerminalNode{
public:
  using NonTerminalNode::NonTerminalNode;  // Construtor inheritance, be sure using c++11
  void interprets();
};

class Atom : public NonTerminalNode{
public:
  using NonTerminalNode::NonTerminalNode;  // Construtor inheritance, be sure using c++11
  void interprets();
};

//----------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------- TERMINALS (Declaration) ---------------------------------------------------------------
class principal : public TerminalNode{
public:
  using TerminalNode::TerminalNode; // Construtor inheritance, be sure using c++11
  void interprets();
};

class left_par : public TerminalNode{
public:
  using TerminalNode::TerminalNode; // Construtor inheritance, be sure using c++11
  void interprets();
};

class right_par : public TerminalNode{
public:
  using TerminalNode::TerminalNode; // Construtor inheritance, be sure using c++11
  void interprets();
};

class arrow : public TerminalNode{
public:
  using TerminalNode::TerminalNode; // Construtor inheritance, be sure using c++11
  void interprets();
};

class retorna : public TerminalNode{
public:
  using TerminalNode::TerminalNode; // Construtor inheritance, be sure using c++11
  void interprets();
};

class dpoint : public TerminalNode{
public:
  using TerminalNode::TerminalNode; // Construtor inheritance, be sure using c++11
  void interprets();
};

class dcomma : public TerminalNode{
public:
  using TerminalNode::TerminalNode; // Construtor inheritance, be sure using c++11
  void interprets();
};

class empty : public TerminalNode{
public:
  using TerminalNode::TerminalNode; // Construtor inheritance, be sure using c++11
  void interprets();
};

class id : public TerminalNode{
public:
  using TerminalNode::TerminalNode; // Construtor inheritance, be sure using c++11
  void interprets();
};

class num : public TerminalNode{
public:
  using TerminalNode::TerminalNode; // Construtor inheritance, be sure using c++11
  void interprets();
};

class si : public TerminalNode{
public:
  using TerminalNode::TerminalNode; // Construtor inheritance, be sure using c++11
  void interprets();
};

class entonces : public TerminalNode{
public:
  using TerminalNode::TerminalNode; // Construtor inheritance, be sure using c++11
  void interprets();
};

class fin : public TerminalNode{
public:
  using TerminalNode::TerminalNode; // Construtor inheritance, be sure using c++11
  void interprets();
};

class mientras : public TerminalNode{
public:
  using TerminalNode::TerminalNode; // Construtor inheritance, be sure using c++11
  void interprets();
};

class para : public TerminalNode{
public:
  using TerminalNode::TerminalNode; // Construtor inheritance, be sure using c++11
  void interprets();
};

class considerando : public TerminalNode{
public:
  using TerminalNode::TerminalNode; // Construtor inheritance, be sure using c++11
  void interprets();
};

class sino : public TerminalNode{
public:
  using TerminalNode::TerminalNode; // Construtor inheritance, be sure using c++11
  void interprets();
};

class finalmente : public TerminalNode{
public:
  using TerminalNode::TerminalNode; // Construtor inheritance, be sure using c++11
  void interprets();
};

class variable : public TerminalNode{
public:
  using TerminalNode::TerminalNode; // Construtor inheritance, be sure using c++11
  void interprets();
};

class comma : public TerminalNode{
public:
  using TerminalNode::TerminalNode; // Construtor inheritance, be sure using c++11
  void interprets();
};

class suma : public TerminalNode{
public:
  using TerminalNode::TerminalNode; // Construtor inheritance, be sure using c++11
  void interprets();
};

class resta : public TerminalNode{
public:
  using TerminalNode::TerminalNode; // Construtor inheritance, be sure using c++11
  void interprets();
};

class multiplicacion : public TerminalNode{
public:
  using TerminalNode::TerminalNode; // Construtor inheritance, be sure using c++11
  void interprets();
};

class division : public TerminalNode{
public:
  using TerminalNode::TerminalNode; // Construtor inheritance, be sure using c++11
  void interprets();
};

//-------------------------------------- NON TERMINALS (Development) ---------------------------------------------------------------
inline void S::interprets(){
  if(this->NTnode->pointing_childs.size() != (unsigned)this->NTnode->next_to_choose){
    cout<<"Incongruencia lexica en: "<<this->NTnode->etiqueta<<endl;
    return;
  }
  else{ // Assuming pointing_childs[0] -> PRINCIPAL and pointing_childs[1] STMT
    PRINCIPAL(this->NTnode->pointing_childs[0], this->NTcontext).interprets();
    STMT(this->NTnode->pointing_childs[1],      this->NTcontext).interprets();
    *this->NTcontext->writer << "}"<<endl;
  }
}

inline void PRINCIPAL::interprets(){
  if(this->NTnode->pointing_childs.size() != (unsigned)this->NTnode->next_to_choose){
    cout<<"Incongruencia lexica en: "<<this->NTnode->etiqueta<<endl;
    return;
  }
  else{
    *this->NTcontext->writer << "int main";
    //principal(this->NTnode->pointing_childs[0],  this->NTcontext).interprets();
    left_par(this->NTnode->pointing_childs[1],   this->NTcontext).interprets();
    right_par(this->NTnode->pointing_childs[2],  this->NTcontext).interprets();
    *this->NTcontext->writer << "{"<<endl;

    //arrow(this->NTnode->pointing_childs[3],      this->NTcontext).interprets();
    //retorna(this->NTnode->pointing_childs[4],    this->NTcontext).interprets();
    //Atom(this->NTnode->pointing_childs[5],       this->NTcontext).interprets();
    dpoint(this->NTnode->pointing_childs[6],     this->NTcontext).interprets();
  }
}

inline void STMT::interprets(){
  if(this->NTnode->pointing_childs.size() != (unsigned)this->NTnode->next_to_choose){
    cout<<"Incongruencia lexica en: "<<this->NTnode->etiqueta<<endl;
    return;
  }
  else{ // Assuming pointing_childs[0] -> PRINCIPAL and pointing_childs[1] STMT
    if(this->NTnode->pointing_childs[0]->etiqueta == "SIMPLE_STMT"){
      SIMPLE_STMT(this->NTnode->pointing_childs[0],   this->NTcontext).interprets();
      dcomma(this->NTnode->pointing_childs[1],      this->NTcontext).interprets();
      STMT(this->NTnode->pointing_childs[2],        this->NTcontext).interprets();
    }
    else if(this->NTnode->pointing_childs[0]->etiqueta == "COMPOUND_STMT"){
      COMPOUND_STMT(this->NTnode->pointing_childs[0], this->NTcontext).interprets();
      //dcomma(this->NTnode->pointing_childs[1],        this->NTcontext).interprets();
      STMT(this->NTnode->pointing_childs[2],          this->NTcontext).interprets();
    }
    else{
      empty(this->NTnode->pointing_childs[0], this->NTcontext).interprets();
    }
  }
}

inline void SIMPLE_STMT::interprets(){
  if(this->NTnode->pointing_childs.size() != (unsigned)this->NTnode->next_to_choose){
    cout<<"Incongruencia lexica en: "<<this->NTnode->etiqueta<<endl;
    return;
  }
  else{ // Assuming pointing_childs[0] -> PRINCIPAL and pointing_childs[1] STMT
    if(this->NTnode->pointing_childs[0]->etiqueta == "TPDEF"){
      TPDEF(this->NTnode->pointing_childs[0], this->NTcontext).interprets();
    }
    else{
      id(this->NTnode->pointing_childs[0], this->NTcontext).interprets();
      DEFDEF(this->NTnode->pointing_childs[1], this->NTcontext).interprets();
    }
  }
}

inline void ONLY_SSTMT::interprets(){
  if(this->NTnode->pointing_childs.size() != (unsigned)this->NTnode->next_to_choose){
    cout<<"Incongruencia lexica en: "<<this->NTnode->etiqueta<<endl;
    return;
  }
  else{ // Assuming pointing_childs[0] -> PRINCIPAL and pointing_childs[1] STMT
    if(this->NTnode->pointing_childs[0]->etiqueta == "TPDEF"){
      TPDEF(this->NTnode->pointing_childs[0],      this->NTcontext).interprets();
      dcomma(this->NTnode->pointing_childs[1],     this->NTcontext).interprets();
      ONLY_SSTMT(this->NTnode->pointing_childs[2], this->NTcontext).interprets();
    }
    else if(this->NTnode->pointing_childs[0]->etiqueta == "id"){
      id(this->NTnode->pointing_childs[0],         this->NTcontext).interprets();
      DEFDEF(this->NTnode->pointing_childs[1],     this->NTcontext).interprets();
      dcomma(this->NTnode->pointing_childs[2],     this->NTcontext).interprets();
      ONLY_SSTMT(this->NTnode->pointing_childs[3], this->NTcontext).interprets();
    }
    else{
      empty(this->NTnode->pointing_childs[0], this->NTcontext).interprets();
    }

  }
}

inline void COMPOUND_STMT::interprets(){
  if(this->NTnode->pointing_childs.size() != (unsigned)this->NTnode->next_to_choose){
    cout<<"Incongruencia lexica en: "<<this->NTnode->etiqueta<<endl;
    return;
  }
  else{ // Assuming pointing_childs[0] -> PRINCIPAL and pointing_childs[1] STMT
    if(this->NTnode->pointing_childs[0]->etiqueta == "si"){
      *this->NTcontext->writer << "if (";
      //si(this->NTnode->pointing_childs[0],         this->NTcontext).interprets();
      NEX(this->NTnode->pointing_childs[1],        this->NTcontext).interprets();
      //entonces(this->NTnode->pointing_childs[2],   this->NTcontext).interprets();
      //dpoint(this->NTnode->pointing_childs[3],     this->NTcontext).interprets();
      *this->NTcontext->writer << ") {"<<endl;
      ONLY_SSTMT(this->NTnode->pointing_childs[4], this->NTcontext).interprets();
      *this->NTcontext->writer << "}"<<endl;
      IFEX2(this->NTnode->pointing_childs[5],      this->NTcontext).interprets();
      //fin(this->NTnode->pointing_childs[6],        this->NTcontext).interprets();
    }
    else if(this->NTnode->pointing_childs[0]->etiqueta == "mientras"){
      *this->NTcontext->writer << "while (";
      //mientras(this->NTnode->pointing_childs[0],   this->NTcontext).interprets();
      NEX(this->NTnode->pointing_childs[1],        this->NTcontext).interprets();
      *this->NTcontext->writer << ") {"<<endl;
      //entonces(this->NTnode->pointing_childs[2],   this->NTcontext).interprets();
      //dpoint(this->NTnode->pointing_childs[3],     this->NTcontext).interprets();
      ONLY_SSTMT(this->NTnode->pointing_childs[4], this->NTcontext).interprets();
      *this->NTcontext->writer << "}"<<endl;
      //fin(this->NTnode->pointing_childs[5],        this->NTcontext).interprets();
    }
    else{
      //para(this->NTnode->pointing_childs[0],         this->NTcontext).interprets();
      *this->NTcontext->writer << "for ( ";
      TPDEF(this->NTnode->pointing_childs[1],        this->NTcontext).interprets();
      *this->NTcontext->writer << " ; ";
      //considerando(this->NTnode->pointing_childs[2], this->NTcontext).interprets();
      NEX(this->NTnode->pointing_childs[3],          this->NTcontext).interprets();
      *this->NTcontext->writer << " ; ) {"<<endl;
      //entonces(this->NTnode->pointing_childs[4],     this->NTcontext).interprets();
      //dpoint(this->NTnode->pointing_childs[5],       this->NTcontext).interprets();
      ONLY_SSTMT(this->NTnode->pointing_childs[6],   this->NTcontext).interprets();
      *this->NTcontext->writer << "}"<<endl;
      //fin(this->NTnode->pointing_childs[7],          this->NTcontext).interprets();

    }
  }
}

inline void IFEX2::interprets(){
  if(this->NTnode->pointing_childs.size() != (unsigned)this->NTnode->next_to_choose){
    cout<<"Incongruencia lexica en: "<<this->NTnode->etiqueta<<endl;
    return;
  }
  else{ // Assuming pointing_childs[0] -> PRINCIPAL and pointing_childs[1] STMT
    if(this->NTnode->pointing_childs[0]->etiqueta == "sino"){
      *this->NTcontext->writer << "else if (";
      //sino(this->NTnode->pointing_childs[0],       this->NTcontext).interprets();
      NEX(this->NTnode->pointing_childs[1],        this->NTcontext).interprets();
      *this->NTcontext->writer << ") {"<<endl;
      //entonces(this->NTnode->pointing_childs[2],   this->NTcontext).interprets();
      //dpoint(this->NTnode->pointing_childs[3],     this->NTcontext).interprets();
      ONLY_SSTMT(this->NTnode->pointing_childs[4], this->NTcontext).interprets();
      *this->NTcontext->writer << "} "<<endl;
      IFEX2(this->NTnode->pointing_childs[5],      this->NTcontext).interprets();
    }
    if(this->NTnode->pointing_childs[0]->etiqueta == "finalmente"){
      *this->NTcontext->writer << "else {"<<endl;
      //finalmente(this->NTnode->pointing_childs[0], this->NTcontext).interprets();
      //dpoint(this->NTnode->pointing_childs[1],     this->NTcontext).interprets();
      ONLY_SSTMT(this->NTnode->pointing_childs[2], this->NTcontext).interprets();
      *this->NTcontext->writer << "}"<<endl;
    }
    else {
      empty(this->NTnode->pointing_childs[0],      this->NTcontext).interprets();
    }
  }
}

inline void NEX::interprets(){
  if(this->NTnode->pointing_childs.size() != (unsigned)this->NTnode->next_to_choose){
    cout<<"Incongruencia lexica en: "<<this->NTnode->etiqueta<<endl;
    return;
  }
  else{ // Assuming pointing_childs[0] -> PRINCIPAL and pointing_childs[1] STMT
    NEX_T(this->NTnode->pointing_childs[0], this->NTcontext).interprets();
    NEX_EP(this->NTnode->pointing_childs[1], this->NTcontext).interprets();
  }
}

inline void NEX_EP::interprets(){
  if(this->NTnode->pointing_childs.size() != (unsigned)this->NTnode->next_to_choose){
    cout<<"Incongruencia lexica en: "<<this->NTnode->etiqueta<<endl;
    return;
  }
  else{ // Assuming pointing_childs[0] -> PRINCIPAL and pointing_childs[1] STMT
    if(this->NTnode->pointing_childs[0]->etiqueta == "BComp"){
      BComp(this->NTnode->pointing_childs[0], this->NTcontext).interprets();
      NEX_T(this->NTnode->pointing_childs[1], this->NTcontext).interprets();
      NEX_EP(this->NTnode->pointing_childs[2], this->NTcontext).interprets();
    }
    else{
      empty(this->NTnode->pointing_childs[0], this->NTcontext).interprets();
    }
  }
}

inline void NEX_T::interprets(){
  if(this->NTnode->pointing_childs.size() != (unsigned)this->NTnode->next_to_choose){
    cout<<"Incongruencia lexica en: "<<this->NTnode->etiqueta<<endl;
    return;
  }
  else{ // Assuming pointing_childs[0] -> PRINCIPAL and pointing_childs[1] STMT
    NEX_F(this->NTnode->pointing_childs[0], this->NTcontext).interprets();
    NEX_TP(this->NTnode->pointing_childs[1], this->NTcontext).interprets();
  }
}

inline void NEX_TP::interprets(){
  if(this->NTnode->pointing_childs.size() != (unsigned)this->NTnode->next_to_choose){
    cout<<"Incongruencia lexica en: "<<this->NTnode->etiqueta<<endl;
    return;
  }
  else{ // Assuming pointing_childs[0] -> PRINCIPAL and pointing_childs[1] STMT
    if(this->NTnode->pointing_childs[0]->etiqueta == "SComp"){
      SComp(this->NTnode->pointing_childs[0], this->NTcontext).interprets();
      NEX_F(this->NTnode->pointing_childs[1], this->NTcontext).interprets();
      NEX_TP(this->NTnode->pointing_childs[2], this->NTcontext).interprets();
    }
    else{
      empty(this->NTnode->pointing_childs[0], this->NTcontext).interprets();
    }
  }
}

inline void NEX_F::interprets(){
  if(this->NTnode->pointing_childs.size() != (unsigned)this->NTnode->next_to_choose){
    cout<<"Incongruencia lexica en: "<<this->NTnode->etiqueta<<endl;
    return;
  }
  else{ // Assuming pointing_childs[0] -> PRINCIPAL and pointing_childs[1] STMT
    /*WARNING*/
    if(this->NTnode->pointing_childs[0]->etiqueta == "("){
      left_par(this->NTnode->pointing_childs[0], this->NTcontext).interprets();
      NEX(this->NTnode->pointing_childs[1], this->NTcontext).interprets();
      right_par(this->NTnode->pointing_childs[2], this->NTcontext).interprets();
    }
    else{
      id(this->NTnode->pointing_childs[0], this->NTcontext).interprets();
    }
  }
}

inline void TPDEF::interprets(){
  //cout<<"On "<<this->NTnode->etiqueta<<" Childs: ";
  //for(unsigned int i = 0; i < this->NTnode->pointing_childs.size(); i++){
  //  cout<<this->NTnode->pointing_childs[i]->etiqueta<<" ";
  //}
  //cout<<"Parent "<<this->NTnode->parent->etiqueta<<endl;

  if(this->NTnode->pointing_childs.size() != (unsigned)this->NTnode->next_to_choose){
    cout<<"Incongruencia lexica en: "<<this->NTnode->etiqueta<<endl;
    return;
  }
  else{ // Assuming pointing_childs[0] -> PRINCIPAL and pointing_childs[1] STMT
    variable(this->NTnode->pointing_childs[0], this->NTcontext).interprets();
    id(this->NTnode->pointing_childs[1], this->NTcontext).interprets();
    TPDEF_SUB(this->NTnode->pointing_childs[2], this->NTcontext).interprets();
  }
}

inline void TPDEF_SUB::interprets(){
  if(this->NTnode->pointing_childs.size() != (unsigned)this->NTnode->next_to_choose){
    cout<<"Incongruencia lexica en: "<<this->NTnode->etiqueta<<endl;
    return;
  }
  else{ // Assuming pointing_childs[0] -> PRINCIPAL and pointing_childs[1] STMT
    if(this->NTnode->pointing_childs[0]->etiqueta == ","){
      comma(this->NTnode->pointing_childs[0], this->NTcontext).interprets();
      id(this->NTnode->pointing_childs[1], this->NTcontext).interprets();
      TPDEF_SUB(this->NTnode->pointing_childs[2], this->NTcontext).interprets();
    }
    else if(this->NTnode->pointing_childs[0]->etiqueta == "EqualTo"){
      EqualTo(this->NTnode->pointing_childs[0], this->NTcontext).interprets();
    }
    else{
      empty(this->NTnode->pointing_childs[0], this->NTcontext).interprets();
    }
  }
}

inline void DEFDEF::interprets(){
  if(this->NTnode->pointing_childs.size() != (unsigned)this->NTnode->next_to_choose){
    cout<<"Incongruencia lexica en: "<<this->NTnode->etiqueta<<endl;
    return;
  }
  else{ // Assuming pointing_childs[0] -> PRINCIPAL and pointing_childs[1] STMT
    if(this->NTnode->pointing_childs[0]->etiqueta == "EqualTo"){
      EqualTo(this->NTnode->pointing_childs[0], this->NTcontext).interprets();
    }
    else{
      AAsig(this->NTnode->pointing_childs[0], this->NTcontext).interprets();
    }
  }
}

inline void EqualTo::interprets(){
  if(this->NTnode->pointing_childs.size() != (unsigned)this->NTnode->next_to_choose){
    cout<<"Incongruencia lexica en: "<<this->NTnode->etiqueta<<endl;
    return;
  }
  else{ // Assuming pointing_childs[0] -> PRINCIPAL and pointing_childs[1] STM

    SEqual(this->NTnode->pointing_childs[0], this->NTcontext).interprets();
    E(this->NTnode->pointing_childs[1], this->NTcontext).interprets();
  }
}

inline void E::interprets(){
  if(this->NTnode->pointing_childs.size() != (unsigned)this->NTnode->next_to_choose){
    cout<<"Incongruencia lexica en: "<<this->NTnode->etiqueta<<endl;
    return;
  }
  else{ // Assuming pointing_childs[0] -> PRINCIPAL and pointing_childs[1] STMT
    T(this->NTnode->pointing_childs[0], this->NTcontext).interprets();
    Ep(this->NTnode->pointing_childs[1], this->NTcontext).interprets();
  }
}

inline void Ep::interprets(){
  if(this->NTnode->pointing_childs.size() != (unsigned)this->NTnode->next_to_choose){
    cout<<"Incongruencia lexica en: "<<this->NTnode->etiqueta<<endl;
    return;
  }
  else{ // Assuming pointing_childs[0] -> PRINCIPAL and pointing_childs[1] STMT
    if(this->NTnode->pointing_childs[0]->etiqueta == "+"){
      suma(this->NTnode->pointing_childs[0], this->NTcontext).interprets();
      T(this->NTnode->pointing_childs[1], this->NTcontext).interprets();
      Ep(this->NTnode->pointing_childs[2], this->NTcontext).interprets();
    }
    else if(this->NTnode->pointing_childs[0]->etiqueta == "-"){
      resta(this->NTnode->pointing_childs[0], this->NTcontext).interprets();
      T(this->NTnode->pointing_childs[1], this->NTcontext).interprets();
      Ep(this->NTnode->pointing_childs[2], this->NTcontext).interprets();
    }
    else{
      empty(this->NTnode->pointing_childs[0], this->NTcontext).interprets();
    }
  }
}

inline void T::interprets(){
  if(this->NTnode->pointing_childs.size() != (unsigned)this->NTnode->next_to_choose){
    cout<<"Incongruencia lexica en: "<<this->NTnode->etiqueta<<endl;
    return;
  }
  else{ // Assuming pointing_childs[0] -> PRINCIPAL and pointing_childs[1] STMT
    F(this->NTnode->pointing_childs[0], this->NTcontext).interprets();
    Tp(this->NTnode->pointing_childs[1], this->NTcontext).interprets();
  }
}

inline void Tp::interprets(){
  if(this->NTnode->pointing_childs.size() != (unsigned)this->NTnode->next_to_choose){
    cout<<"Incongruencia lexica en: "<<this->NTnode->etiqueta<<endl;
    return;
  }
  else{ // Assuming pointing_childs[0] -> PRINCIPAL and pointing_childs[1] STMT
    if(this->NTnode->pointing_childs[0]->etiqueta == "*"){
      multiplicacion(this->NTnode->pointing_childs[0], this->NTcontext).interprets();
      F(this->NTnode->pointing_childs[1], this->NTcontext).interprets();
      Tp(this->NTnode->pointing_childs[2], this->NTcontext).interprets();
    }
    else if(this->NTnode->pointing_childs[0]->etiqueta == "/"){
      division(this->NTnode->pointing_childs[0], this->NTcontext).interprets();
      F(this->NTnode->pointing_childs[1], this->NTcontext).interprets();
      Tp(this->NTnode->pointing_childs[2], this->NTcontext).interprets();
    }
    else{
      empty(this->NTnode->pointing_childs[0], this->NTcontext).interprets();
    }
  }
}

inline void F::interprets(){
  if(this->NTnode->pointing_childs.size() != (unsigned)this->NTnode->next_to_choose){
    cout<<"Incongruencia lexica en: "<<this->NTnode->etiqueta<<endl;
    return;
  }
  else{ // Assuming pointing_childs[0] -> PRINCIPAL and pointing_childs[1] STMT
    if(this->NTnode->pointing_childs[0]->etiqueta == "("){
      left_par(this->NTnode->pointing_childs[0],  this->NTcontext).interprets();
      E(this->NTnode->pointing_childs[1],         this->NTcontext).interprets();
      right_par(this->NTnode->pointing_childs[2], this->NTcontext).interprets();
    }
    else{
      Atom(this->NTnode->pointing_childs[0],  this->NTcontext).interprets();
    }
  }
}

inline void SEqual::interprets(){
  if(this->NTnode->pointing_childs.size() != (unsigned)this->NTnode->next_to_choose){
    cout<<"Incongruencia lexica en: "<<this->NTnode->etiqueta<<endl;
    return;
  }
  else{ // Assuming pointing_childs[0] -> PRINCIPAL and pointing_childs[1] STMT
    if(this->NTnode->pointing_childs[0]->etiqueta == "="){
      *this->NTcontext->writer << "=";
    }
    else if(this->NTnode->pointing_childs[0]->etiqueta == "+="){
      *this->NTcontext->writer << "+=";
    }
    else if(this->NTnode->pointing_childs[0]->etiqueta == "-="){
      *this->NTcontext->writer << "-=";
    }
    else{
      *this->NTcontext->writer << "*=";
    }

  }
}

inline void AAsig::interprets(){
  if(this->NTnode->pointing_childs.size() != (unsigned)this->NTnode->next_to_choose){
    cout<<"Incongruencia lexica en: "<<this->NTnode->etiqueta<<endl;
    return;
  }
  else{ // Assuming pointing_childs[0] -> PRINCIPAL and pointing_childs[1] STMT
    if(this->NTnode->pointing_childs[0]->etiqueta == "++"){
      *this->NTcontext->writer << this->NTnode->etiqueta<<endl;
    }
    else{
      *this->NTcontext->writer << this->NTnode->etiqueta<<endl;
    }

  }
}

inline void SComp::interprets(){
  if(this->NTnode->pointing_childs.size() != (unsigned)this->NTnode->next_to_choose){
    cout<<"Incongruencia lexica en: "<<this->NTnode->etiqueta<<endl;
    return;
  }
  else{ // Assuming pointing_childs[0] -> PRINCIPAL and pointing_childs[1] STMT
    if(this->NTnode->pointing_childs[0]->etiqueta == ">="){
      *this->NTcontext->writer << ">=";
    }
    else if(this->NTnode->pointing_childs[0]->etiqueta == "<="){
      *this->NTcontext->writer << "<=";
    }
    else if(this->NTnode->pointing_childs[0]->etiqueta == "!="){
      *this->NTcontext->writer << "!=";
    }
    else if(this->NTnode->pointing_childs[0]->etiqueta == "=="){
      *this->NTcontext->writer << "==";
    }
    else if(this->NTnode->pointing_childs[0]->etiqueta == "<>"){
      *this->NTcontext->writer << "!=";
    }
    else if(this->NTnode->pointing_childs[0]->etiqueta == "<"){
      *this->NTcontext->writer << "<";
    }
    else{ // <>
      *this->NTcontext->writer << ">";
    }
  }
}

inline void BComp::interprets(){
  if(this->NTnode->pointing_childs.size() != (unsigned)this->NTnode->next_to_choose){
    cout<<"Incongruencia lexica en: "<<this->NTnode->etiqueta<<endl;
    return;
  }
  else{ // Assuming pointing_childs[0] -> PRINCIPAL and pointing_childs[1] STMT
    if(this->NTnode->pointing_childs[0]->etiqueta == "yy"){
      *this->NTcontext->writer << "&&";
    }
    else{ // oo
      *this->NTcontext->writer << "||";
    }
  }
}

inline void Atom::interprets(){
  if(this->NTnode->pointing_childs.size() != (unsigned)this->NTnode->next_to_choose){
    cout<<"Incongruencia lexica en: "<<this->NTnode->etiqueta<<endl;
    return;
  }
  else{ // Assuming pointing_childs[0] -> PRINCIPAL and pointing_childs[1] STMT
    if(this->NTnode->pointing_childs[0]->etiqueta == "num"){
      num(this->NTnode->pointing_childs[0],  this->NTcontext).interprets();
    }
    else{
      id(this->NTnode->pointing_childs[0],  this->NTcontext).interprets();
    }

  }
}

//-------------------------------------- TERMINALS (Development) ---------------------------------------------------------------
inline void principal::interprets(){
  //*this->NTcontext->writer << this->NTnode->etiqueta<<endl;
}

inline void left_par::interprets(){
  *this->NTcontext->writer << this->NTnode->etiqueta;
}

inline void right_par::interprets(){
  *this->NTcontext->writer << this->NTnode->etiqueta;
}

inline void arrow::interprets(){
  //*this->NTcontext->writer << this->NTnode->etiqueta<<endl;
}

inline void retorna::interprets(){
  //*this->NTcontext->writer << this->NTnode->etiqueta<<endl;
}

inline void dpoint::interprets(){
  //*this->NTcontext->writer << this->NTnode->etiqueta<<endl;
  *this->NTcontext->writer <<endl;
}

inline void dcomma::interprets(){
  *this->NTcontext->writer << this->NTnode->etiqueta<<endl;
}

inline void empty::interprets(){
  //*this->NTcontext->writer << this->NTnode->etiqueta<<endl;
}

inline void id::interprets(){
  *this->NTcontext->writer << this->NTnode->lexema_to_semantic->second();
}

inline void num::interprets(){
  *this->NTcontext->writer << this->NTnode->lexema_to_semantic->second();
}

inline void si::interprets(){
  //*this->NTcontext->writer << this->NTnode->etiqueta<<endl;
}

inline void entonces::interprets(){
  //*this->NTcontext->writer << this->NTnode->etiqueta<<endl;
}

inline void fin::interprets(){
  //*this->NTcontext->writer << this->NTnode->etiqueta<<endl;
}

inline void mientras::interprets(){
  //*this->NTcontext->writer << this->NTnode->etiqueta<<endl;
}

inline void para::interprets(){
  //*this->NTcontext->writer << this->NTnode->etiqueta<<endl;
}

inline void considerando::interprets(){
  //*this->NTcontext->writer << this->NTnode->etiqueta<<endl;
}

inline void sino::interprets(){
  //*this->NTcontext->writer << this->NTnode->etiqueta<<endl;
}

inline void finalmente::interprets(){
  //*this->NTcontext->writer << this->NTnode->etiqueta<<endl;
}

inline void variable::interprets(){
  *this->NTcontext->writer << this->NTnode->lexema_to_semantic->second() << " ";
}

inline void comma::interprets(){
  *this->NTcontext->writer <<this->NTnode->etiqueta << " ";
}

inline void suma::interprets(){
  *this->NTcontext->writer <<" "<<this->NTnode->etiqueta;
}

inline void resta::interprets(){
  *this->NTcontext->writer <<" "<<this->NTnode->etiqueta;
}

inline void multiplicacion::interprets(){
  *this->NTcontext->writer << this->NTnode->etiqueta;
}

inline void division::interprets(){
  *this->NTcontext->writer << this->NTnode->etiqueta;
}


















#endif

























// This line has no a porpuse
