#pragma once
#include <iostream>
#include <set>
#include <string>

class Alfabeto {
  public:
    Alfabeto(std::set<char> caracteres_);  //constructor
    std::set<char> GetSet();  //getter
    void SetSet(std::set<char> set);   //setter
    void RemoveSet();  //vaciar set
    void Push(char); // añadir elemntos al alfabeto
  private:
  std::set<char> caracteres;
};

std::ostream& operator<<(std::ostream& out, Alfabeto& a);