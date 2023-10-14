#include "Estado.h"
#include <vector>

Estado::Estado(std::map <char, std::vector<int>> transiciones_, bool aceptacion_, int ntransiciones_) {
  ntransiciones = ntransiciones_;
  aceptacion = aceptacion_;
  transiciones = transiciones_;
}

void Estado::AddTransicion(char simbolo, int estado_siguiente) {
  transiciones[simbolo].push_back(estado_siguiente);
  //for(int i = 0; i < transiciones[simbolo].size(); ++i) {
    //std::cout << transiciones[simbolo][i] << " ";
  //}
  std::cout << transiciones[simbolo].size();
}

std::map<char, std::vector<int>> Estado::GetMap() {
  return transiciones;
}

bool Estado::IsAccepted() {
  return aceptacion;
}

void Estado::SetIsAccepted(bool aceptacion_) {
  aceptacion = aceptacion_;
}

void Estado::SetNtransiciones(int ntransiciones_) {
  ntransiciones = ntransiciones_;
}

Estado::Estado() {
  transiciones = std::map<char, std::vector<int>>();
  aceptacion = 0;
  ntransiciones = 0;
}

int Estado::GetNtransiciones() {
  return ntransiciones;
}

