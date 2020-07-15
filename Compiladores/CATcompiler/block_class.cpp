#include <iostream>
#include <vector>
#include <string>
//#include "Code/TestNode.h"
#include "Code/sintatic_tree.h"

using namespace std;

class TestNode{
public:
  string name;
  vector<TestNode> childs;

  TestNode(string, vector<TestNode>);
  ~TestNode();
};

TestNode::TestNode(string _name, vector<TestNode> _childs){
  this->name = _name;
  this->childs = _childs;
}

TestNode::~TestNode(){}

class AbstractBase{
public:
  AbstractBase();
  ~AbstractBase();
  virtual void interprets() = 0;
};

AbstractBase::AbstractBase(){}
AbstractBase::~AbstractBase(){}

//---------------------------------------------------------------------------
class TerminalNode : public AbstractBase{
public:
  TestNode* NTnode;

  TerminalNode(TestNode*);
  ~TerminalNode();
  virtual void interprets();
};

inline TerminalNode::TerminalNode(TestNode* _NTnode){
  this->NTnode = _NTnode;
}

inline TerminalNode::~TerminalNode(){}

inline void TerminalNode::interprets(){
  cout<<"Interpreted from Terminal: "<<this->NTnode->name<<endl;
}


//---------------------------------------------------------------------------
class NonTerminalNode : public AbstractBase{
public:
  TestNode* NTnode;

  NonTerminalNode(TestNode*);
  ~NonTerminalNode();
  virtual void interprets();
};

inline NonTerminalNode::NonTerminalNode(TestNode* _NTnode){
  this->NTnode = _NTnode;
}

inline NonTerminalNode::~NonTerminalNode(){}

inline void NonTerminalNode::interprets(){
  if(this->NTnode->childs.size() == 0){
    TerminalNode(this->NTnode).interprets();
  }
  else{
    for(unsigned int i = 0; i < this->NTnode->childs.size(); i++){
      NonTerminalNode(&this->NTnode->childs[i]).interprets();
    }
  }
}

int main(){
  TestNode non_tree = TestNode("2", vector<TestNode>{ TestNode("3", vector<TestNode>{}) , TestNode("4", vector<TestNode>{}) });
  NonTerminalNode expression = NonTerminalNode(&non_tree);
  expression.interprets();
}























// This line hs no porpuse
