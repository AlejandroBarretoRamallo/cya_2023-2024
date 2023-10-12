#include "Estado.h"
#include <vector>

Estado::Estado(std::map <char, std::vector<int>> transiciones_) {
  transiciones = transiciones_;
}

void Estado::AddTransicion(char simbolo, int estado_siguiente) {
  transiciones[simbolo].push_back(estado_siguiente);
}

std::map<char, std::vector<int>> Estado::GetMap() {
  return transiciones;
}

bool Estado::IsAccepted() {
  return aceptacion;
}

int Estado::GetNtransiciones() {
  return ntransiciones;
}

void Estado::SetIsAccepted(bool aceptacion_) {
  aceptacion = aceptacion_;
}

void Estado::SetNtransiciones(int ntransiciones_) {
  ntransiciones = ntransiciones_;
}