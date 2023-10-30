#include <iostream>
#pragma once
#include "Alfabeto.h"
#include <map>

class Gramatica {
  public:
    Alfabeto GetAlfabeto(); // constructor
    Gramatica(std::set<char> conjunto_no_terminales_, Alfabeto alfabeto, char arranque_, std::multimap<char, std::string> producciones_); // constructor con parametros
    std::set<char> GetNoTerminales();  //getter
    char GetArranque();   //getter
    std::multimap<char, std::string> GetProducciones();  //getter
    bool ComprobarProduccionesVacias();    
    bool ComprobarProduccionesUnitarias();
    void TransformarCNF();   // metodo para pasar a FNC
  private:
    std::set<char> conjunto_no_terminales;  
    Alfabeto alfabeto;   //conjunto de terminales
    char arranque;  //estado arranque
    std::multimap<char, std::string> producciones;  
};

std::ostream& operator<<(std::ostream& out, Gramatica& a);   // sobrecarga del operador <<