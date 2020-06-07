#ifndef LEXICAL_BUFFER_H
#define LEXICAL_BUFFER_H

#include <iostream>
#include <vector>

using namespace std;

class lexical_buffer{
public:
  vector<vector<char>> main_buffer; // main_buffer[0] -> left_buffer
                                    // main_buffer[1] -> right_buffer
  lexical_buffer();
  ~lexical_buffer();
};

lexical_buffer::lexical_buffer(){
  this->main_buffer = vector<vector<char>>(2, vector<char>(0, ' '));
}

#endif
