#include <iostream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

void print(vector<int>&);
void fill_vector(vector<int>&, int);

int main(){
  vector<int> a = {1, 2, 3, 4, 5};
  vector<int>::iterator it;
  it = find(a.begin(), a.end(), 100);
  it = a.end();
  if(it > a.end()){
    cout<<"More"<<endl;
  }
  else{
    cout<<"Equal"<<endl;
  }
  //cout<<*(it-1)<<endl;
  //cout<<*(a.end()-1)<<endl;

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
