#include <iostream>
#pragma once
#include "Alfabeto.h"

class Gramatica {
  public:
    Alfabeto GetAlfabeto();
    Gramatica(std::set<char> conjunto_no_terminales_, Alfabeto alfabeto);
    std::set<char> GetNoTerminales();
  private:
    std::set<char> conjunto_no_terminales;
    Alfabeto alfabeto;
};