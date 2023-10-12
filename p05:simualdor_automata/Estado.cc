#include "Estado.h"

Estado::Estado(std::map <char, int> transiciones_) {
  transiciones = transiciones_;
}

void Estado::AddTransicion(char simbolo, int estado_siguiente) {
  transiciones[simbolo] = estado_siguiente;
}

std::map<char, int> Estado::GetMap() {
  return transiciones;
}

