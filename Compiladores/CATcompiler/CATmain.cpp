#include <iostream>
#include "code/CATlexical.h"

/*WARNING*/
#include <unordered_map>

using namespace std;

int main(){
  CATlexical lexical_analizer;
  lexical_analizer.set_doc_to_read("Test/FirstExample.cat");
  lexical_analizer.reader();

  /*
  unordered_map<string, string>:: iterator it;
  it = lexical_analizer.reserved_words.find("si");
  if(it == lexical_analizer.reserved_words.end()){
    cout<<"No existe este valor"<<endl;
  }
  else{
    cout<<(*it).second<<endl;
  }
  */

  return 0;
}
