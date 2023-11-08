#include <iostream>
#pragma once
#include "Alfabeto.h"
#include <map>

class Gramatica {
  public:
    Alfabeto GetAlfabeto();
    Gramatica(std::set<char> conjunto_no_terminales_, Alfabeto alfabeto, char arranque_, std::multimap<char, std::string> producciones_);
    std::set<char> GetNoTerminales();
    char GetArranque();
    std::multimap<char, std::string> GetProducciones();
    bool ComprobarProduccionesVacias();
    bool ComprobarProduccionesUnitarias();
    void TransformarCNF();
  private:
    std::set<char> conjunto_no_terminales;
    Alfabeto alfabeto;
    char arranque;
    std::multimap<char, std::string> producciones;
};

std::ostream& operator<<(std::ostream& out, Gramatica& a);   // sobrecarga del operador <<