#ifndef CATSINTATIC_H
#define CATSINTATIC_H


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

#include "lexical_lexema.h"
#include "lexical_buffer.h"
#include "m_functions.h"


class CATsintatic{
public:
  string route_to_gramatica;
  ifstream file_reader;

  vector<string> terminals;
  vector<string> non_terminals;

  string component_separator;
  string empty_component;
  string grammar_root;
  unordered_map<string, vector<vector<string>> > productions;

  bool sintatic_state;
  string error_type;

  CATsintatic(string = "->", string = "lambda");
  ~CATsintatic();

  void set_grammar_to_read(string);
  void grammar_reader(); // Accept grammars with only one production in the right side. For multiple definitions, use multiples lines
    string grammar_reader_helper();
    void grammar_construction(string); // Process line_by_line -> separate terminals from non_terminals;
    void _get_terminals_and_non_terminals(); // Inner functions, dont use them !!

  vector<string> get_primeros(string);
  vector<string> get_siguientes(string);
  void fill_dictionary();

  void set_error(string = "Error desconocido");
  void report_error();
  void print(bool = false);
};

CATsintatic::CATsintatic(string _componente_separator, string _empty_component){
  this->route_to_gramatica = "";
  this->terminals = vector<string>(0, "");
  this->non_terminals = vector<string>(0, "");

  this->component_separator = _componente_separator;
  this->empty_component = _empty_component;
  this->grammar_root = "";

  this->sintatic_state = true;
  this->error_type = "";
}

CATsintatic::~CATsintatic(){}

void CATsintatic::set_grammar_to_read(string new_route){
  this->route_to_gramatica = new_route;
}

void CATsintatic::grammar_reader(){
  this->file_reader = ifstream(this->route_to_gramatica);
  if(!file_reader.is_open()){this->route_to_gramatica = "";}
  if(this->route_to_gramatica == ""){
    cout<<"CAT: Ruta a la gramatica incorrecta"<<endl;
    return;
  }
  else{
    string current_statement = "";
    while(true){
      current_statement = this->grammar_reader_helper();
      if(current_statement != "eof"){
        //cout<<"Insertando linea: "<<current_statement<<endl;
        this->grammar_construction(current_statement);
      }
      else{
        break;
      }
    }
    this->_get_terminals_and_non_terminals();
  }
  cout<<endl<<"CAT//: Gramatica completa"<<endl;
}

string CATsintatic::grammar_reader_helper(){
  string answer = "";
  if(!getline(this->file_reader, answer).eof()){
    return answer;
  }
  else{
    return "eof";
  }
}

void CATsintatic::grammar_construction(string grammar_line){
  if(!grammar_line.size()){
    return; // Avoid empty lines y grammar file
  }

  vector<string> splitted_line = string_split(grammar_line); // m_functions -> splitted_line[0] : production root, splitted_line[1] : separator, splitted_line[2:] -> right part of production
  if(this->productions.find(splitted_line[0]) == this->productions.end()){ // If left part in production is not added we created
    this->productions.insert( make_pair(splitted_line[0], vector<vector<string>>{vector<string>{vector<string>(splitted_line.begin()+2, splitted_line.end())}} ));
  }
  else{ // Otherwise we just append production with the same initializer
    this->productions.at(splitted_line[0]).push_back(vector<string>{vector<string>(splitted_line.begin()+2, splitted_line.end())});
  }

  //Defining root production. Works only once.
  if(!this->grammar_root.size()){
    this->grammar_root = splitted_line[0];
  }
  return;
}

void CATsintatic::_get_terminals_and_non_terminals(){
  unordered_set<string> s;
  unordered_map<string, vector<vector<string>>>::iterator it;
  for(it = this->productions.begin(); it != this->productions.end(); it++){
      this->non_terminals.push_back(it->first);
      for(unsigned int i = 0; i < it->second.size(); i++){
        for(unsigned int k = 0; k < it->second[i].size(); k++){
          if(this->productions.find(it->second[i][k]) == this->productions.end()){
            s.insert(it->second[i][k]); // Taken from: https://stackoverflow.com/questions/1041620/whats-the-most-efficient-way-to-erase-duplicates-and-sort-a-vector
          }
        }
      }
  }
  this->terminals.assign(s.begin(), s.end());
}

// not_terminal could be a terminal or non_termninal... maybe a different would be necessary
vector<string> CATsintatic::get_primeros(string not_terminal){
  // not_terminal is in terminals : existe en el connjunto de terminales // algorithm
  if( std::find(this->terminals.begin(), this->terminals.end(), not_terminal) != this->terminals.end()){
    return vector<string>{not_terminal};
  }
  else if(this->productions.find(not_terminal) == this->productions.end() ){
    this->set_error("En primeros: " + not_terminal + " no existe.");
    return vector<string>{};
  }
  else{
    vector<string> g_primeros = vector<string>(0, "");
    for(unsigned int i = 0; i < this->productions.at(not_terminal).size(); i++){
      string next_not_terminal = this->productions.at(not_terminal)[i][0];

      vector<string> candidates_to_first = this->productions.at(not_terminal)[i];
      unsigned int start_on = 0;

      if(candidates_to_first[start_on] == not_terminal){ /*WARNING: Woul better just to report cases of left recursion*/
        /*while(candidates_to_first[start_on] == not_terminal){start_on++;}
        if(start_on >= candidates_to_first.size()){
          this->set_error("En primeros: Recursion por la izquierda inevitable.");
          return vector<string>{};
        }*/
        this->set_error("En primeros: Recursion por la izquierda inevitable -> " + not_terminal + " - " + candidates_to_first[start_on]);
        return vector<string>{};
      }

      vector<string> temp = this->get_primeros(candidates_to_first[start_on]);

      vector<string>::iterator it;
      it = find(temp.begin(), temp.end(), this->empty_component);
      if(it != temp.end()){
        start_on++;
        while(it != temp.end()){
          if(start_on >= candidates_to_first.size()){break;}
          else{
            temp.erase(it);
            vector<string> temp_2 = this->get_primeros(candidates_to_first[start_on]);
            temp.insert(temp.end(), temp_2.begin(), temp_2.end());
            it = find(temp.begin(), temp.end(), this->empty_component);
            start_on++;
            }
        }

      }
      g_primeros.insert( g_primeros.end(), temp.begin(), temp.end() );
    }
    unordered_set<string> s(g_primeros.begin(), g_primeros.end()); // Avoiding duplicates values -> Not very common
    g_primeros.assign(s.begin(), s.end());
    return g_primeros;
  }
}

vector<string> CATsintatic::get_siguientes(string not_terminal){
  if( std::find(this->terminals.begin(), this->terminals.end(), not_terminal) != this->terminals.end()){
    return vector<string>{not_terminal};
  }
  else if(this->productions.find(not_terminal) == this->productions.end() ){
    this->set_error("En siguientes: " + not_terminal + " no existe.");
    return vector<string>{};
  }
  else{
    vector<string> a_siguiente = vector<string>(0, "");
    if(not_terminal == this->grammar_root){
      a_siguiente.push_back("$");
    }

    // Recorriendo raiz producciones
    for(unordered_map<string, vector<vector<string>>>::iterator it = this->productions.begin(); it != this->productions.end(); it++){
      //Recorriendo produccion en producciones
      for(unsigned int i = 0; i < it->second.size(); i++){
        //Recorriendo componentes de una produccion.
        for(unsigned int j = 0; j < it->second[i].size(); j++){
          if(not_terminal == it->second[i][j]){
              if( j+1 < it->second[i].size()){ // A -> i B b    : Next for B
                vector<string> temp = this->get_primeros(it->second[i][j+1]); // Remember, not duplicates returned in primeros

                vector<string>::iterator it2 = find(temp.begin(), temp.end(), this->empty_component);
                if(it2 != temp.end() ){
                  temp.erase(it2);
                  vector<string> temp_2 = this->get_siguientes(it->first);
                  temp.insert(temp.end(), temp_2.begin(), temp_2.end());
                }
                a_siguiente.insert(a_siguiente.end(), temp.begin(), temp.end());
              }
              else{ // A -> i B  // Next for B
                if(not_terminal != it->first){
                  vector<string> temp = this->get_siguientes(it->first);
                  a_siguiente.insert(a_siguiente.end(), temp.begin(), temp.end());
                }
              }
          }
        }
      }
    }
    unordered_set<string> s(a_siguiente.begin(), a_siguiente.end()); // Avoiding duplicates values -> Very common
    a_siguiente.assign(s.begin(), s.end());
    return a_siguiente;
  }
}

void CATsintatic::fill_dictionary(){
  for(unsigned int i = 0; i < this->non_terminals.size(); i++){
    
  }
}

void CATsintatic::set_error(string _error){
  this->sintatic_state = false;
  this->error_type = _error;
  this->report_error();
}

void CATsintatic::report_error(){
  cout<<"CAT:// Error sintactico -> "<<this->error_type<<endl;
}

void CATsintatic::print(bool extended){
  cout<<"Gramatica en: "<<this->route_to_gramatica<<endl;
  cout<<"Raiz de gramatica: "<<this->grammar_root<<endl;
  cout<<"No terminales: ";
  print_vector(this->non_terminals); cout<<endl;
  cout<<"Terminales: ";
  print_vector(this->terminals); cout<<endl;

  if(extended){
    unordered_map<string, vector<vector<string>>>::iterator it;
    for(it = this->productions.begin(); it != this->productions.end(); it++){
      cout<<it->first<<" -> ";
      for(unsigned int i = 0; i < it->second.size(); i++){
        cout<<endl<<"\t";
        print_vector(it->second[i]);
      }
      cout<<endl;
    }
  }
}

#endif
