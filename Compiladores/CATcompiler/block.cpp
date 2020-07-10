#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include "Code/lexical_lexema.h"
#include "Code/m_functions.h"

using namespace std;

void print(vector<int>&);
void fill_vector(vector<int>&, int);

int main(){
  vector<lexical_lexema> a = {lexical_lexema("primer"), lexical_lexema("segundo")};
  cout<<a.back().first()<<endl;

  /*
  if(std::find(a.begin(), a.end(), 10) != a.end()){
    cout<<"Founded"<<endl;
  }
  else{
    cout<<"Not founded"<<endl;
  }
  */

}







void fill_vector(vector<int>& in_vec, int n){
  for(int i = 0; i < n; i++){
    in_vec.push_back(i);
  }
  return;
}


void print(vector<int>& input){
  for(unsigned int i = 0; i < input.size(); i++){
    cout<<i<<": "<<input[i]<<endl;
  }
}
