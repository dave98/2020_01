#include <iostream>
#include "code/CATlexical.h"

using namespace std;

int main(){
  CATlexical lexical_analizer;
  lexical_analizer.set_doc_to_read("Test/FirstExample.cat");
  lexical_analizer.reader();

  return 0;
}
