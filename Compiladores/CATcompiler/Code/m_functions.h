#ifndef M_FUNCTIONS_H
#define M_FUNCTIONS_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

template<class T>
void print_vector(vector<T>& in_vec, bool insolate = false){
  for(unsigned int i = 0; i < in_vec.size(); i++){
    if(insolate){
      cout<<"_"<<in_vec[i]<<"_ ";
    }
    else{
      cout<<in_vec[i]<<" ";
    }
  }
}

void print_string_delayed(string in_string){
  for(unsigned int i = 0; i < in_string.size(); i++){
    if(in_string[i] == ' ')
      cout<<"->"<<"SPC"<<"<-";
    else{
      cout<<"->"<<in_string[i]<<"<-";
    }
  }

}

// Taken from: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
vector<string> string_split(string phrase_to_separate, string delimiter = " "){
  vector<string> tokens;
  size_t prev = 0, pos = 0;
  do{
    pos = phrase_to_separate.find(delimiter, prev);
    if(pos == string::npos) pos = phrase_to_separate.length();
    string token = phrase_to_separate.substr(prev, pos - prev);
    if(!token.empty()) tokens.push_back(token);
    prev = pos + delimiter.length();
  }
  while(pos < phrase_to_separate.length() && prev < phrase_to_separate.length());
  /*
  cout<<phrase_to_separate<<endl;
  for(unsigned int i = 0; i < tokens.size(); i++){
   cout<<"_"<<tokens[i]<<"_"<<endl;
 }*/
  return tokens;
}

#endif
