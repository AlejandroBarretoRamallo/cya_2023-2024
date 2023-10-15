#include "ConjuntoEstados.h"
#include <vector>

ConjuntoEstados::ConjuntoEstados(std::vector<Estado> estados_) {
  estados = estados_;
  EstadoActual = std::vector<Estado>();
  ProximosEstados = std::vector<Estado>();
}

void ConjuntoEstados::AddEstados(Estado estado) {
  estados.push_back(estado);
}

std::vector<Estado> ConjuntoEstados::GetVector() {
  return estados;
}

void ConjuntoEstados::AddEstadoActual(Estado estado_actual_) {
  EstadoActual.push_back(estado_actual_);
}

std::vector<Estado> ConjuntoEstados::GetEstadoActual() {
  return EstadoActual;
}

std::vector<Estado> ConjuntoEstados::GetProxEstado() {
  return ProximosEstados;
}

void ConjuntoEstados::AddProxEstado(Estado estado) {
  ProximosEstados.push_back(estado);
}

void ConjuntoEstados::VaciarProxEstado() {
  ProximosEstados.resize(0);
}

void ConjuntoEstados::VaciarEstadoActual() {
  EstadoActual.resize(0);
}
