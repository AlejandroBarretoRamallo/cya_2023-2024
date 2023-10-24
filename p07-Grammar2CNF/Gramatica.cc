#include "Gramatica.h"

Alfabeto Gramatica::GetAlfabeto() {
  return alfabeto;
}

Gramatica::Gramatica(std::set<char> conjunto_no_terminales_, Alfabeto alfabeto_) {
  conjunto_no_terminales = conjunto_no_terminales_;
  alfabeto = alfabeto_;
}

std::set<char> Gramatica::GetNoTerminales() {
  return conjunto_no_terminales;
}