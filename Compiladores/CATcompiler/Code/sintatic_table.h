#ifndef SINTATIC_TABLE_H
#define SINTATIC_TABLE_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "m_functions.h"

using namespace std;

class sintatic_table{
public:
  unordered_map<string, unordered_map<string, vector<string> > > table;

  sintatic_table();
  ~sintatic_table();

  void insert(string, string, vector<string>);
  vector<string> get(string, string);
  void print();

};

sintatic_table::sintatic_table(){}
sintatic_table::~sintatic_table(){}

// Assuming incoming keys are stripped.
void sintatic_table::insert(string key1, string key2, vector<string> inter_val){
  // Si primer key no esta en la tabla
  if(this->table.find(key1) == this->table.end()){
    this->table.insert(make_pair(key1, unordered_map<string, vector<string>>() ));
    this->table[key1].insert( make_pair(key2, vector<string>{vector<string>(inter_val.begin(), inter_val.end())} ) );
  }
  else if(this->table[key1].find(key2) == this->table[key1].end()){
    this->table[key1].insert( make_pair(key2, vector<string>{vector<string>(inter_val.begin(), inter_val.end())}) );
  }
  else{
    cout<<"Advertencia - Valores de tabla no actualizable para "<<key1<<" y "<<key2<<endl;
    //Do nothing -> It would mean a table update which is not allowed.
  }
}

// No funciona con referencias directas. O sea su valor no puedo ser utilizado  hasta no ser colocado
// adecuadamente en una variable
vector<string> sintatic_table::get(string key1, string key2){//Use ctch expression
  if( (this->table.find(key1) != this->table.end()) && (this->table[key1].find(key2) != this->table[key1].end()) ){
    return this->table[key1][key2];
  }
  else{
    cout<<"Error en tabla - No existe valor descrito para "<<key1<<" y "<<key2<<endl;
    return vector<string>{};
  }
}

void sintatic_table::print(){
  unordered_map<string, unordered_map<string, vector<string>>>::iterator it;
  unordered_map<string, vector<string>>::iterator it2;
  for(it = this->table.begin(); it != this->table.end(); it++){
    cout<<it->first<<":"<<endl;
    for(it2 = it->second.begin(); it2 != it->second.end(); it2++){
      cout<<"    "<<it2->first<<" -> ";
      print_vector(it2->second);
      cout<<endl;
    }
  }
}

#endif
