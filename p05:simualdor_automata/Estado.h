#pragma once
#include <iostream>
#include <map>
#include <utility>

class Estado{
  public:
    Estado(std::map <char, int> transiciones_);
    void AddTransicion(char simbolo, int estado_siguiente);
    std::map<char, int> GetMap();
  private:
    std::map <char, int> transiciones;
};