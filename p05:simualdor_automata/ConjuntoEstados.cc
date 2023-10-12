#include "ConjuntoEstados.h"
#include <vector>

ConjuntoEstados::ConjuntoEstados(std::vector<Estado> estados_) {
  estados = estados_;
}

void ConjuntoEstados::AddEstados(Estado estado) {
  estados.push_back(estado);
}

std::vector<Estado> ConjuntoEstados::GetVector() {
  return estados;
}

void ConjuntoEstados::SetEstadoActual(int estado_actual_) {
  EstadoActual = estado_actual_;
}

int ConjuntoEstados::GetEstadoActual() {
  return EstadoActual;
}