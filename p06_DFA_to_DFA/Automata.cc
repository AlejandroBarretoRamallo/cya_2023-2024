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

void Automata::EpsilonTransiciones(std::vector<Estado> &estados_){
  bool added = 1;
  int indice = 0;
  bool pertenece ;
  while(added) {
    pertenece = 0;
    added = 0;
    if(!estados_[indice].Visitado() && indice < estados_.size() && indice < estados.size()) {
      std::multimap<char, int> map = estados_[indice].GetMap();
      estados[indice].SetVisitado();
      auto rango = map.find('&');
      if(rango != map.end()) {
        auto rango_ = map.equal_range('&'); // rango_ contiene la epsilon_transicion
        for(auto it = rango_.first; it != rango_.second; ++it) {
          for(int i = 0; i < estados_.size(); ++i) {
            if(estados_[i].GetMap() == estados[it -> second].GetMap() && estados_[i].GetNtransiciones() == estados[it -> second].GetNtransiciones() && estados_[i].IsAccepted() == estados[it -> second].IsAccepted()) {
              pertenece = 1;
            }
          }
          if(!pertenece) {
            estados_.push_back(estados[it -> second]);
          }
        }
        added = true;
      } 
    }
    ++indice;
  }
  for(int i = 0; i < estados.size(); ++i) {
    estados[i].SetNoVisitado();
  }
  for(int i = 0; i < estados_.size(); ++i) {
    estados_[i].SetNoVisitado();
  }
}

void Automata::Move(char simbolo, std::vector<Estado> conjunto_estados) {
  std::vector<Estado> delta;
  for(int i = 0; i < conjunto_estados.size(); ++i) {
    std::multimap <char, int > map = conjunto_estados[i].GetMap(); // recorremos las transiciones de los estados que pertenecen al estado actual
    auto rango = map.equal_range(simbolo);  // rango contiene todos los valores asociados a un simbolo concreto
    for (auto it_ = rango.first; it_ != rango.second; ++it_) {
      delta.push_back(estados[it_ -> second]); // accedemos al vector de estados y añadimos el correspondiente a proximo estado
    }
  }
  conjunto_estados.clear();
  conjunto_estados = delta;
}
