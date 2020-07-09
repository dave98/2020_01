#include <iostream>
//#include "code/CATlexical.h"
#include "code/CATsintatic.h"
#include "code/m_functions.h"

#include "code/sintatic_table.h"

#include <vector>
#include <string>

using namespace std;

int main(){
  /*CATlexical lexical_analizer;
  lexical_analizer.set_doc_to_read("Test/ThirdExample.cat");
  lexical_analizer.reader();
  lexical_analizer.print();
  */

  string key1 = "key1";
  string key2 = "key2";
  vector<string> values = {"val1", "val2", "val3"};

  sintatic_table table_test;
  table_test.insert(key1, key2, values);

  cout<<endl<<"Finished correctly"<<endl;




/*
  CATsintatic sintatic_analizer;
  sintatic_analizer.set_grammar_to_read("Test/grammar2.gcat");
  //sintatic_analizer.set_grammar_to_read("Code/CATGrammar.py");
  sintatic_analizer.grammar_reader();
  sintatic_analizer.print();
*/


  // Test primeros y siguientes.
  //vector<string> temp = sintatic_analizer.get_siguientes("F");
  //print_vector(temp);
  //cout<<endl<<"Finished correctly"<<endl;



  return 0;
}
