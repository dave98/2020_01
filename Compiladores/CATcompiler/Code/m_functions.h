#ifndef M_FUNCTIONS_H
#define M_FUNCTIONS_H

#include <iostream>
#include <vector>

using namespace std;

template<class T>
void print_vector(vector<T>& in_vec){
  for(unsigned int i = 0; i < in_vec.size(); i++){
    cout<<in_vec[i]<<" ";
  }
  cout<<endl;
}


#endif
