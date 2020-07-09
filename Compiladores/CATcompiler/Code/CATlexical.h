#ifndef CATLEXICAL_H
#define CATLEXICAL_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <regex>
#include <functional>

#include <windows.h>  /*WARNING*/

#include "lexical_buffer.h"
#include "lexical_lexema.h"

using namespace std;
typedef void (*pfunc)();

class CATlexical{
public:
  string route_actual_doc;      // Ruta hacia el documento actual siendo leido
  ifstream file_reader;         // ifstream de lectura
  lexical_buffer* in_buffer;     // Contenedor in_pair de statements
  regex re_word;
  regex re_number;

  vector<lexical_lexema*> lexema_for_sintactic;
  unordered_map<string, function<void()> > reserved_words;
  unordered_map<string, function<void()> > operators;

  bool lexical_state;
  string error_type;

  CATlexical();
      void initialize_reserved_words();
      void initialize_operators();
  ~CATlexical();

  void set_doc_to_read(string);  // Setea el documento a leer actualmente
  void reader();                 // Leer documento linea por linea y setear por buffer
    string reader_helper();      // Obtiene una linea del documento
    void process_line(int = 0);         // Procesa la línea de codigo en el buffer_actual
      void process_words();
      void process_numbers();
      void process_operator();
      bool is_word(string);
      bool is_number(string);
        void si(); // Tratamiento para if
        void sino();
        void mientras();
        void para();
        void entonces();
        void yy();
        void oo();
        void principal();
        void funcion();
        void retorna();
        void variable();

        void suma();
        void resta();
        void multiplicacion();
        void division();
        void asignacion();
        void relacional();

        void empty();
        void comentario();
        void puntuacion();
  bool continue_evaluation();
  void set_error(string);
  void report_error();
  void print();                  // Información del objeto

};

CATlexical::CATlexical(){
  this->route_actual_doc = "";
  this->in_buffer = new lexical_buffer();
  this->lexema_for_sintactic = vector<lexical_lexema*>(0, NULL);
  this->re_word = regex("[a-zA-Z]+");
  this->re_number = regex("[0-9][0-9]*(\\.[0-9]+)?");
  this->lexical_state = true;
  this->error_type = "";
  this->initialize_reserved_words();
  this->initialize_operators();
}

void CATlexical::initialize_reserved_words(){
  this->reserved_words["si"] =        bind(&CATlexical::si, this);
  this->reserved_words["sino"] =      bind(&CATlexical::sino, this);
  this->reserved_words["mientras"] =  bind(&CATlexical::mientras, this);
  this->reserved_words["para"] =      bind(&CATlexical::para, this);
  this->reserved_words["entonces"] =  bind(&CATlexical::entonces, this);
  this->reserved_words["yy"] =        bind(&CATlexical::yy, this);
  this->reserved_words["oo"] =        bind(&CATlexical::oo, this);
  this->reserved_words["principal"] = bind(&CATlexical::principal, this);
  this->reserved_words["funcion"] =   bind(&CATlexical::funcion, this);
  this->reserved_words["retorna"] =   bind(&CATlexical::retorna, this);
  this->reserved_words["variable"] =  bind(&CATlexical::variable, this);
}

// BNFA  structure
void CATlexical::initialize_operators(){
  this->operators["+"] =              bind(&CATlexical::suma, this);
  this->operators["-"] =              bind(&CATlexical::resta, this);
  this->operators["*"] =              bind(&CATlexical::multiplicacion, this);
  this->operators["/"] =              bind(&CATlexical::division, this);
  this->operators["="] =              bind(&CATlexical::asignacion, this);
  this->operators["<"] =              bind(&CATlexical::relacional, this);
  this->operators[">"] =              bind(&CATlexical::relacional, this);

  this->operators["$"] =              bind(&CATlexical::comentario, this);
  this->operators[" "] =              bind(&CATlexical::empty, this);
  this->operators["("] =              bind(&CATlexical::puntuacion, this);
  this->operators[")"] =              bind(&CATlexical::puntuacion, this);
  this->operators["["] =              bind(&CATlexical::puntuacion, this);
  this->operators["]"] =              bind(&CATlexical::puntuacion, this);
  this->operators[","] =              bind(&CATlexical::puntuacion, this);
  this->operators[":"] =              bind(&CATlexical::puntuacion, this);
  this->operators[";"] =              bind(&CATlexical::puntuacion, this);

}


CATlexical::~CATlexical(){
}

void CATlexical::set_doc_to_read(string new_route){
  this->route_actual_doc = new_route;
}


void CATlexical::reader(){
  this->file_reader = ifstream(this->route_actual_doc);
  if(!file_reader.is_open()){this->route_actual_doc = "";}

  if(this->route_actual_doc == ""){
    cout<<"CAT: Ruta no especifica o inexistente"<<endl;
    return;
  }
  else{
    string current_statement = "";
    int actual_line = 0;
    while(true){
      current_statement = this->reader_helper();
      if (current_statement != "eof"){
        this->in_buffer->fill_buffer(current_statement);
        this->process_line(actual_line);
        actual_line++;
      }
      else{
        break;
      }
    }
  }

  cout<<endl<<"CAT: Lectura Satisfactoria"<<endl;
}

// Funciona en base al apuntador ifstream: this->file_reader
// Conforme va leendo el apuntador alamacena su posición actual
string CATlexical::reader_helper(){
  string answer = "";
  if( !getline(this->file_reader, answer).eof()){
    return answer;
  }
  else{
    return "eof";
  }
}

// Procesamiento será realizado línea por linea
void CATlexical::process_line(int line_id){
  int scope_in_line = this->in_buffer->get_scope();
  if(scope_in_line == -1){ // Linea vacía
    return;
  }
  // At this point we know there is something in the line. El get_next will always be the fisrt character un expresion
  while(this->continue_evaluation() && this->in_buffer->get_next_no_change() != '@'){
    this->process_words();
    this->process_numbers();
    this->process_operator();

  }
  return;
}

void CATlexical::process_words(){
  string in_word = "";
  //cout<<"Process words: "<<"|"<<this->in_buffer->get_next_no_change()<<"|"<<endl;

  in_word += this->in_buffer->get_next();
  while(this->is_word(in_word)){
    in_word += this->in_buffer->get_next();
  }
  this->in_buffer->go_back();
  in_word.pop_back();

  unordered_map<string, function<void()>>::iterator it = this->reserved_words.find(in_word);
  if(it != this->reserved_words.end()){
    this->reserved_words[in_word]();
    return;
  }
  else if(this->is_word(in_word)){
    lexical_lexema* new_lexema = new lexical_lexema("identificador", in_word);
    this->lexema_for_sintactic.push_back(new_lexema);
    //cout<<*new_lexema<<endl;
    return;
  }
  else{
    return;
  }
}

void CATlexical::process_numbers(){
  string in_number = "";
  //cout<<"Process number: "<<"|"<<this->in_buffer->get_next_no_change()<<"|"<<endl;

  in_number += this->in_buffer->get_next();
  while(this->is_number(in_number)){
    in_number += this->in_buffer->get_next();
  }
  this->in_buffer->go_back();
  in_number.pop_back();

  if(this->is_number(in_number)){
    lexical_lexema* new_lexema = new lexical_lexema("numero", in_number);
    this->lexema_for_sintactic.push_back(new_lexema);
    //cout<<*new_lexema<<endl;
    return;
  }
  else{
    return;
  }
}

void CATlexical::process_operator(){
  string in_operator = "";
  //cout<<"Process operator: "<<"|"<<this->in_buffer->get_next_no_change()<<"|"<<endl;
  in_operator += this->in_buffer->get_next();
  unordered_map<string, function<void()>>::iterator it = this->operators.find(in_operator);
  if(it != this->operators.end()){ // Existe un operador
    this->operators[in_operator]();
    return;
  }
  else{
    this->in_buffer->go_back();
    return;
  }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////OPERATORS AND PUNTUATION/////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void CATlexical::suma(){
  lexical_lexema*  new_lexema = NULL;
  char continue_suma = this->in_buffer->get_next();
  switch (continue_suma) {
    case '=':
      new_lexema = new lexical_lexema("+="); //Asignación especial
      //cout<<*new_lexema<<endl;
      break;

    default:
      new_lexema = new lexical_lexema("+");  // Adicición
      //cout<<*new_lexema<<endl;
      this->in_buffer->go_back();
      break;
  }

  if (new_lexema != NULL){ /*WARNING*/
    this->lexema_for_sintactic.push_back(new_lexema);
  }
  else{
    return;
  }
}

void CATlexical::resta(){
  lexical_lexema*  new_lexema = NULL;
  char continue_resta = this->in_buffer->get_next();
  switch (continue_resta) {
    case '=':
      new_lexema = new lexical_lexema("-="); // Asignacion especial
      //cout<<*new_lexema<<endl;
      break;
    case '>':
      new_lexema = new lexical_lexema("->"); // Arrow
      //cout<<*new_lexema<<endl;
      break;

    default:
      new_lexema = new lexical_lexema("-"); // Resta
      //cout<<*new_lexema<<endl;
      this->in_buffer->go_back();
      break;
  }

  if (new_lexema != NULL){ /*WARNING*/
    this->lexema_for_sintactic.push_back(new_lexema);
  }
  else{
    return;
  }
}

void CATlexical::multiplicacion(){
  lexical_lexema*  new_lexema = NULL;
  char continue_multiplicacion = this->in_buffer->get_next();
  switch (continue_multiplicacion) {
    case '=':
      new_lexema = new lexical_lexema("*="); // Asignación especial
      break;

    default:
      new_lexema = new lexical_lexema("*"); // Multiplicación
      this->in_buffer->go_back();
      break;
  }

  if (new_lexema != NULL){ /*WARNING*/
    this->lexema_for_sintactic.push_back(new_lexema);
  }
  else{
    return;
  }
}

void CATlexical::division(){
  lexical_lexema*  new_lexema = NULL;
  char continue_division = this->in_buffer->get_next();
  switch (continue_division) {
    case '=':
      new_lexema = new lexical_lexema("/="); // Asignación especial
      //cout<<*new_lexema<<endl;
      break;

    default:
      new_lexema = new lexical_lexema("/"); // División
      this->in_buffer->go_back();
      break;
  }

  if (new_lexema != NULL){ /*WARNING*/
    this->lexema_for_sintactic.push_back(new_lexema);
  }
  else{
    return;
  }
}

void CATlexical::asignacion(){
  lexical_lexema*  new_lexema = NULL;
  char continue_asignacion = this->in_buffer->get_next();
  switch (continue_asignacion) {
    case '=':
      new_lexema = new lexical_lexema("=="); // Comparación
      //cout<<*new_lexema<<endl;
      break;

    default:
      new_lexema = new lexical_lexema("="); // Asignacion
      //cout<<*new_lexema<<endl;
      this->in_buffer->go_back();
      break;
  }

  if (new_lexema != NULL){ /*WARNING*/
    this->lexema_for_sintactic.push_back(new_lexema);
  }
  else{
    return;
  }
}

void CATlexical::relacional(){
  lexical_lexema*  new_lexema = NULL;
  char evaluate_relacional = this->in_buffer->get_actual(); /*WARNING Impredictable behavior*/
  switch (evaluate_relacional) {
    case '<':
      evaluate_relacional = this->in_buffer->get_next_no_change();
      switch (evaluate_relacional) {
        case '=':
          new_lexema = new lexical_lexema("<="); // Comparación
          this->in_buffer->get_next(); // Ha avanzado uno el puntero delantero
          break;
        default:
          new_lexema = new lexical_lexema("<"); // Comparación
          break;
      }
      break;
    case '>':
      evaluate_relacional = this->in_buffer->get_next_no_change();
      switch (evaluate_relacional) {
        case '=':
          new_lexema = new lexical_lexema(">="); // Comparación
          this->in_buffer->get_next();
          break;
        default:
          new_lexema = new lexical_lexema(">"); // Comparación
          break;
      }
      break;
    default:
      return;
  }

  if (new_lexema != NULL){ /*WARNING*/
    this->lexema_for_sintactic.push_back(new_lexema);
  }
  else{
    return;
  }
}

void CATlexical::puntuacion(){
  lexical_lexema* new_lexema = NULL;
  char evaluate_puntuation = this->in_buffer->get_actual();
  switch (evaluate_puntuation) {
    case '(':
      new_lexema = new lexical_lexema("("); // Puntuacion
      //cout<<*new_lexema<<endl;
      break;
    case ')':
      new_lexema = new lexical_lexema(")"); // Puntuacion
      //cout<<*new_lexema<<endl;
      break;
    case '[':
      new_lexema = new lexical_lexema("["); // Puntuacion
      //cout<<*new_lexema<<endl;
      break;
    case ']':
      new_lexema = new lexical_lexema("]"); // Puntuacion
      //cout<<*new_lexema<<endl;
      break;
    case ',':
      new_lexema = new lexical_lexema(","); // Puntuacion
      //cout<<*new_lexema<<endl;
      break;
    case ':':
      new_lexema = new lexical_lexema(":"); // Puntuacion
      //cout<<*new_lexema<<endl;
      break;
    case ';':
      new_lexema = new lexical_lexema(";"); // Puntuacion
      break;
    default:
      return;
  }

  if (new_lexema != NULL){
    this->lexema_for_sintactic.push_back(new_lexema);
  }
  else{
    return;
  }
}

void CATlexical::comentario(){
  string comentario_deleted = "";

  char beetwen_comentario = this->in_buffer->get_next();
  comentario_deleted += beetwen_comentario;

  while(beetwen_comentario != '$'){
    beetwen_comentario = this->in_buffer->get_next();
    comentario_deleted += beetwen_comentario;

    if(beetwen_comentario == '@'){
      this->set_error("Comentario Inconcluso");
      return;
    }
  }

  cout<<"Comentario: "<<comentario_deleted<<endl;
  return;
}

void CATlexical::empty(){
  while(this->in_buffer->get_next() == ' '){
  }
  this->in_buffer->go_back();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////RESERVED WORDS///////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void CATlexical::si(){
  lexical_lexema* new_lexema = new lexical_lexema("si");
  this->lexema_for_sintactic.push_back(new_lexema);
}

void CATlexical::sino(){
  lexical_lexema* new_lexema = new lexical_lexema("sino");
  this->lexema_for_sintactic.push_back(new_lexema);
}

void CATlexical::mientras(){
  lexical_lexema* new_lexema = new lexical_lexema("mientras");
  this->lexema_for_sintactic.push_back(new_lexema);
}

void CATlexical::para(){
  lexical_lexema* new_lexema = new lexical_lexema("para");
  this->lexema_for_sintactic.push_back(new_lexema);
}

void CATlexical::entonces(){
  lexical_lexema* new_lexema = new lexical_lexema("entonces");
  this->lexema_for_sintactic.push_back(new_lexema);
}

void CATlexical::yy(){
  lexical_lexema* new_lexema = new lexical_lexema("yy");
  this->lexema_for_sintactic.push_back(new_lexema);
}

void CATlexical::oo(){
  lexical_lexema* new_lexema = new lexical_lexema("oo");
  this->lexema_for_sintactic.push_back(new_lexema);
}

void CATlexical::principal(){
  lexical_lexema* new_lexema = new lexical_lexema("principal");
  this->lexema_for_sintactic.push_back(new_lexema);
}

void CATlexical::funcion(){
  lexical_lexema* new_lexema = new lexical_lexema("funcion");
  this->lexema_for_sintactic.push_back(new_lexema);
}

void CATlexical::retorna(){
  lexical_lexema* new_lexema = new lexical_lexema("retorna");
  this->lexema_for_sintactic.push_back(new_lexema);
}

void CATlexical::variable(){
  lexical_lexema* new_lexema = new lexical_lexema("variable");
  this->lexema_for_sintactic.push_back(new_lexema);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CATlexical::is_word(string in_word){
  if(regex_match(in_word, this->re_word)){
    return true;
  }
  else{
    return false;
  }
}

bool CATlexical::is_number(string in_word){
  if(regex_match(in_word, this->re_number)){
    return true;
  }
  else{
    return false;
  }

}

bool CATlexical::continue_evaluation(){
  return this->lexical_state;
}

void CATlexical::set_error(string _error = "Error desconocido"){
  this->lexical_state = false;
  this->error_type = _error;
}

void CATlexical::report_error(){
  cout<<"\tError lexico en linea del tipo: "<<this->error_type<<endl;
}

void CATlexical::print(){
  cout<<"Codigo en: "<<this->route_actual_doc<<endl;
  cout<<"Lexical CAT: "<<endl;
  if(lexical_state){
    for(unsigned int k = 0; k < this->lexema_for_sintactic.size(); k++){
      cout<<*this->lexema_for_sintactic[k]<<endl;
    }
    cout<<endl;
  }
  else{
    this->report_error();
  }

}

#endif
