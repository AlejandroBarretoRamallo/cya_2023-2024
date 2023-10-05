#pragma once
#include <iostream>
#include <set>
#include <string>
#include <fstream>

class alfabeto {
  public:
    alfabeto(std::set<char> caracteres_);  //constructor
    std::set<char> get_set();  //getter
    void set_set(std::set<char> set);   //setter
    void remove_set();  //vaciar set
    void print_alfabeto(std::string salida, std::string entrada); //muestra el alfabeto
    void longitud_cadena(std::string salida, std::string entrada); //muestra lalongitud de la cadena
    void inversa(std::string salida, std::string entrada); // muestra la cadena invertida
    void prefijos(std::string salida, std::string entrada);  // muestra los prefijos de las cadenas
    void sufijos(std::string salida, std::string entrada);  // muestra los sufijos
    void concatenar(std::string salida, std::string entrada); // concatena una cadena con las que se encuentren en el fichero
  private:
  std::set<char> caracteres;
};

std::ostream& operator<<(std::ostream& out, alfabeto& a);