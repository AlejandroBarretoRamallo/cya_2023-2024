#include "Estado_copy.h"
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
  visitado = 0;
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
  visitado = 0;
}

int Estado::GetNtransiciones() {
  return ntransiciones;
}

bool Estado::Visitado() {
  return visitado;
}

void Estado::SetVisitado() {
  visitado = 1;
}

void Estado::SetNoVisitado() {
  visitado = 0;
}

