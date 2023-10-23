#include "Automata_copy.h"
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

void Automata::EpsilonTransiciones(std::vector<char> &estados_){
  bool added = 1;
  int indice = 0;
  bool pertenece ;
  while (added) { // seguir revisanod hasta que no se haya añadido nada
    pertenece = 0;
    added = 0;
    if (indice < estados_.size() && indice < estados.size()) {      // evitar que se salga de rango
      std::multimap<char, int> map = estados[indice].GetMap();
      estados[indice].SetVisitado();  //visitar nodo
      auto rango = map.find('&');
      if (rango != map.end()) { // comprobar si hay epsilon transiciones
        auto rango_ = map.equal_range('&'); // rango_ contiene la epsilon_transicion
        for (auto it = rango_.first; it != rango_.second; ++it) {
          pertenece = 0;
          for (int i = 0; i < estados_.size(); ++i) {
          if (it -> second == estados_[i]) {
            pertenece = 1;
          }
          }
          if (!pertenece) {
            estados_.push_back(it -> second);  // añadir la epsilon transicion
            added = 1;
          }
        }
      } 
    }
    ++indice;
  }
}

void Automata::Move(char simbolo, std::vector<char> conjunto_estados) {
  std::vector<char> delta;
  for (int i = 0; i < conjunto_estados.size(); ++i) {  
    std::multimap <char, int > map = estados.at(conjunto_estados[i]).GetMap(); // recorremos las transiciones de los estados que pertenecen al estado actual
    auto rango = map.equal_range(simbolo);  // rango contiene todos los valores asociados a un simbolo concreto
    for (auto it_ = rango.first; it_ != rango.second; ++it_) {
      delta.push_back(it_ ->second); // accedemos al vector de estados y añadimos el correspondiente a proximo estado
    }
  }
  conjunto_estados.clear();
  conjunto_estados = delta;
}
