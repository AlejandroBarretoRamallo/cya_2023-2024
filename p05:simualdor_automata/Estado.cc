#include "Estado.h"
#include <vector>

void Estado::AddTransicion(char simbolo, int estado_siguiente) {
  transiciones.insert({estado_siguiente, simbolo}); // ir añadiendo las transiciones en el multimap
}
std::multimap<char, int> Estado::GetMap() {
  return transiciones;
}

Estado::Estado() {
  transiciones = std::multimap<char, int> ();
  aceptacion = bool ();
  ntransiciones = int();
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

Estado::Estado(std::multimap<char, int> transiciones_, bool aceptacion_, int ntransiciones_) {
  transiciones = transiciones_;
  aceptacion = aceptacion_;
  ntransiciones = ntransiciones_;
}

int Estado::GetNtransiciones() {
  return ntransiciones;
}

