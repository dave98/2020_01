#ifndef M_FUNCTIONS_H
#define M_FUNCTIONS_H

#include <iostream>
#include <vector>

using namespace std;

template<class T>
void print_vector(vector<T>& in_vec){
  for(unsigned int i = 0; i < in_vec.size(); i++){
    cout<<in_vec[i]<<"";
  }
}

void print_string_delayed(string in_string){
  for(unsigned int i = 0; i < in_string.size(); i++){
    if(in_string[i] == ' ')
      cout<<"->"<<"SPC"<<"<-";
    else{
      cout<<"->"<<in_string[i]<<"<-";
    }
  }

}


#endif
