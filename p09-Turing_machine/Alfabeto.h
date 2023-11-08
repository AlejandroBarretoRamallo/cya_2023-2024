#pragma once
#include <iostream>
#include <set>
#include <string>

class Alfabeto {
  public:
    Alfabeto(std::set<char> caracteres_);
    Alfabeto();
    std::set<char> GetSet();
    void GetSet(std::set<char> set);
    void RemoveSet();
    void Push(char);
  private:
  std::set<char> caracteres;
};

std::ostream& operator<<(std::ostream& out, Alfabeto& a);   // sobrecarga del operador <<