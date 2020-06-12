#include <iostream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

void print(vector<int>&);
void fill_vector(vector<int>&, int);

int main(){
  vector<int> a;
  fill_vector(a, 20);
  //print(a);
/*
  string identifier = ".0";
  regex re("[0-9]*.[0-9]+");
  if(regex_match(identifier, re)){
    cout<<"Si es valido"<<endl;
  }
  else{
    cout<<"No es valido"<<endl;
  }
*/
  char c_a = 'a';
  string s_a = "";
  s_a += c_a;
  return 0;
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
