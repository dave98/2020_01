#include <iostream>
#include <vector>
#include <string>

using namespace std;

void print(vector<char>&);

int main(){
  string s_a = "haruki  murakami";
  string s_b = "hiraku  makimura";
  vector<char> a = vector<char>(0, ' ');
  a = vector<char>(s_a.begin(), s_a.end());
  a = vector<char>(s_b.begin(), s_b.end());

  //cout<<s_a<<endl;
  //print(a);
  bool gh = true;
  cout<<"gh: "<<!!gh<<endl;

  return 0;
}

void print(vector<char>& input){
  for(unsigned int i = 0; i < input.size(); i++){
    if(input[i] == '\t')
      cout<<i<<": tab"<<endl;
    else{
      cout<<i<<": "<<input[i]<<endl;
    }
  }
}
