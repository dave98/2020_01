#ifndef LEXICAL_BUFFER_H
#define LEXICAL_BUFFER_H

#include <iostream>
#include <vector>

#include "m_functions.h"

using namespace std;

// Esta clase mantiene una para de buffer que almacenan los statements por linea
class lexical_buffer{
public:
  vector<vector<char>> main_buffer; // main_buffer[0] -> left_buffer
                                    // main_buffer[1] -> right_buffer
  bool used_buffer;


  lexical_buffer();
  ~lexical_buffer();

  void fill_buffer(string);
  void print_one_buffer(int); //0 for left, 1 to rigth
  void print_actual_buffer(); // print last used buffer
};

lexical_buffer::lexical_buffer(){
  this->main_buffer = vector<vector<char>>(2, vector<char>(0, ' '));
  this->used_buffer = false;  // 0(false) left buffer, 1(true) right buffer
}

lexical_buffer::~lexical_buffer(){
}

// Intercambio automático entre buffer izquierdo y buffer derecho
void lexical_buffer::fill_buffer(string in_sentence){
  this->main_buffer[this->used_buffer] = vector<char>(in_sentence.begin(), in_sentence.end());
  this->used_buffer = !this->used_buffer;
}

void lexical_buffer::print_one_buffer(int in_buff){
  if(!in_buff){
    print_vector(this->main_buffer[0]);
  }
  else{
    print_vector(this->main_buffer[1]);
  }
  return;
}

void lexical_buffer::print_actual_buffer(){
  cout<<this->used_buffer<<" ";
  print_vector(this->main_buffer[this->used_buffer]);
  return;
}



#endif
