#ifndef SINTATIC_TABLE_H
#define SINTATIC_TABLE_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class sintatic_table{
public:
  unordered_map<string, unordered_map<string, vector<string> > > table;

  sintatic_table();
  ~sintatic_table();

  void insert(string, string, vector<string>);
  vector<string> get(string, string);
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
    //Do nothing -> It would mean a table update which is not allowed.
  }
}

vector<string> sintatic_table::get(string key1, string k2){//Use ctch expression

}


#endif
