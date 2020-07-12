#include <iostream>
#include <vector>
#include <string>

#include "code/CATlexical.h"
#include "code/CATsintatic.h"
#include "code/CATsemantic.h"
#include "code/m_functions.h"
#include "code/supervisor_symbol_table.h"
#include "code/lexical_lexema.h"
#include "code/sintatic_tree.h"

using namespace std;

int main(){

  supervisor_symbol_table* global_table = new supervisor_symbol_table();

  CATlexical lexical_analizer(global_table);
  lexical_analizer.set_doc_to_read("Test/CATprogram1.cat");
  lexical_analizer.reader();
  vector<lexical_lexema*> lexemas_in = lexical_analizer.get_lexemas(); // lexical part returns lexemas founded
  //global_table->print();

  CATsintatic sintatic_analizer(global_table);
  sintatic_analizer.set_grammar_to_read("Test/CATgrammar.gcat");
  sintatic_analizer.grammar_reader();
  sintatic_analizer.fill_dictionary();
  sintatic_analizer.set_lexemas(lexemas_in);
  //sintatic_analizer.my_table->print();
  sintatic_analizer.chain_validation("", false);


  sintatic_tree* temp_tree = sintatic_analizer.get_tree_for_semantics();
  CATsemantic semantic_analyzer(temp_tree);
  semantic_analyzer.print_tree();
  semantic_analyzer.generate_code();


  cout<<endl<<"Finished correctly"<<endl;

  return 0;
}
