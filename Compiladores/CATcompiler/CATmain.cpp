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

  CATsintatic sintatic_analizer;
  sintatic_analizer.set_grammar_to_read("Test/grammar1.gcat");
  //sintatic_analizer.set_grammar_to_read("Code/CATGrammar.py");
  sintatic_analizer.grammar_reader();
  sintatic_analizer.fill_dictionary();
  sintatic_analizer.my_table->print();
  //sintatic_analizer.print();

  sintatic_analizer.chain_validation("Test/validation1.cat");

  //sintatic_analizer.my_table->print();
  // Test primeros y siguientes.
  //vector<string> temp = sintatic_analizer.get_primeros("E");
  //vector<string> temp = sintatic_analizer.get_production("Tp", "+");
  //print_vector(temp);
  cout<<endl<<"Finished correctly"<<endl;



  return 0;
}
