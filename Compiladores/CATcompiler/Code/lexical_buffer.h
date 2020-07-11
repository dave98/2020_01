#ifndef LEXICAL_BUFFER_H
#define LEXICAL_BUFFER_H

#include <iostream>
#include <vector>
#include <map>

#include "m_functions.h"
using namespace std;

// Esta clase mantiene una para de buffer que almacenan los statements por linea
class lexical_buffer{
public:
  vector<vector<char>> main_buffer; // main_buffer[0] -> left_buffer
                                    // main_buffer[1] -> right_buffer
  bool used_buffer;
  vector<char>::iterator lookahead_pointer;
  vector<char>::iterator backward_pointer;

  lexical_buffer();
  ~lexical_buffer();

  void fill_buffer(string);
  int get_actual_buffer_size();
  int get_scope();
    char get_next();
    char get_actual();
    char get_next_no_change();
    char get_back_no_change();

    void go_back();
    void update_backward();

  void print_one_buffer(int); //0 for left, 1 to rigth
  void print_actual_buffer(); // print last used buffer
};

lexical_buffer::lexical_buffer(){
  this->main_buffer = vector<vector<char>>(2, vector<char>(6, 'a'));
  this->used_buffer = true;  // 0(false) left buffer, 1(true) right buffer
  this->lookahead_pointer = this->main_buffer[this->used_buffer].begin();
  this->backward_pointer  = this->main_buffer[this->used_buffer].begin();
}

lexical_buffer::~lexical_buffer(){
}

// Intercambio automático entre buffer izquierdo y buffer derecho
void lexical_buffer::fill_buffer(string in_sentence){
  this->used_buffer = !this->used_buffer;
  this->main_buffer[this->used_buffer] = vector<char>(in_sentence.begin(), in_sentence.end());
  this->main_buffer[this->used_buffer].push_back('@');
  this->lookahead_pointer = this->main_buffer[this->used_buffer].begin();
  this->backward_pointer =  this->main_buffer[this->used_buffer].begin();

}

int lexical_buffer::get_actual_buffer_size(){
  return this->main_buffer[this->used_buffer].size();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int lexical_buffer::get_scope(){
  if(this->get_actual_buffer_size() == 1 ){ // which means only '@' is in the buffer
    return -1;
  }

  int answer = 0;
  while(*this->lookahead_pointer == ' '){
    this->lookahead_pointer++;
    answer++;
  }
  this->lookahead_pointer--; // Retornando uno pues tras los espacios me puedo comer una letra
  this->backward_pointer = lookahead_pointer;
  return answer/2;
}

// Return the actual content in lookahead_pointer and go one ahead.
// If the actual content is the end of the line, it returns @.
char lexical_buffer::get_next(){
  this->lookahead_pointer++;
  if(this->lookahead_pointer != this->main_buffer[this->used_buffer].end()){
    return *this->lookahead_pointer;
  }
  else{
    //this->lookahead_pointer--; // Keep consistency in the end of the line  /*WARNING*/
    return '@';
  }
}

char lexical_buffer::get_actual(){ /*WARNING: Impredictable behavior*/
  return *this->lookahead_pointer;
}


char lexical_buffer::get_next_no_change(){
  if(this->lookahead_pointer + 1 != this->main_buffer[this->used_buffer].end()){
    return *(this->lookahead_pointer + 1);
  }
  else{
    return '@';
  }
}

char lexical_buffer::get_back_no_change(){
  if(this->lookahead_pointer - 1 != this->main_buffer[this->used_buffer].begin()){
    return *(this->lookahead_pointer - 1);
  }
  else{
    return *(this->lookahead_pointer);
  }

}



// Manda un paso para atras a lookahead_pointer si en caso no esta al inicio.
void lexical_buffer::go_back(){
  this->lookahead_pointer--;
  return;
  //cout<<*this->lookahead_pointer<<"<->"<<*this->main_buffer[this->used_buffer].begin()<<endl;
  /*if(this->lookahead_pointer != this->main_buffer[this->used_buffer].begin()){
    this->lookahead_pointer--;
    return;
  }
  else{
    return;
  }*/
}

// Put the backward pointer a the same position as the lookahead_pointer.
void lexical_buffer::update_backward(){
  this->backward_pointer = this->lookahead_pointer;
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
  cout<<this->used_buffer<<" |";
  print_vector(this->main_buffer[this->used_buffer]);
  cout<<"|"<<endl;
  return;
}





#endif
