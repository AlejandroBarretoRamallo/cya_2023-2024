#pragma once
#include <iostream>
#include "Estado_copy.h"
#include <vector>
#include <set>

class Automata {
  public:
    Automata(std::vector<Estado> estados_);  //constructor
    void AddEstados(Estado estado); 
    std::vector<Estado> GetEstadoActual(); // getter
    void AddEstadoActual(Estado estado);  
    std::vector<Estado> GetVector(); // getter
    std::vector<Estado> GetProxEstado();  //getter
    void AddProxEstado(Estado estado);
    void VaciarProxEstado();
    void VaciarEstadoActual();
    void EpsilonTransiciones(std::vector<char> &estados_);
    void Move(char simolo, std::vector<char> conjunto_estados);
  private:
    std::vector<Estado> estados;
    std::vector<Estado> EstadoActual;
    std::vector<Estado> ProximosEstados;
};