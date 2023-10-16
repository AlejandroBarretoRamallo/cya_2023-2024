#include "Automata.h"
#include <vector>

Automata::Automata(std::vector<Estado> estados_) {
  estados = estados_;
  EstadoActual = std::vector<Estado>();
  ProximosEstados = std::vector<Estado>();
}

void Automata::AddEstados(Estado estado) {
  estados.push_back(estado);
}

std::vector<Estado> Automata::GetVector() {
  return estados;
}

void Automata::AddEstadoActual(Estado estado_actual_) {
  EstadoActual.push_back(estado_actual_);
}

std::vector<Estado> Automata::GetEstadoActual() {
  return EstadoActual;
}

std::vector<Estado> Automata::GetProxEstado() {
  return ProximosEstados;
}

void Automata::AddProxEstado(Estado estado) {
  ProximosEstados.push_back(estado);
}

void Automata::VaciarProxEstado() {
  ProximosEstados.resize(0);
}

void Automata::VaciarEstadoActual() {
  EstadoActual.resize(0);
}
