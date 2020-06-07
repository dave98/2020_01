#include <iostream>
#include <vector>

using namespace std;

int main(){
  vector<char> a;
  a = vector<char>(12, 'z');

  cout<<"a: "<<endl;
  for(unsigned int i = 0; i < a.size(); i++){
    cout<<i<<": "<<a[i]<<endl;
  }

  return 0;
}
