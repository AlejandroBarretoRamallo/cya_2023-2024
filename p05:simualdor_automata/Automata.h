#pragma once
#include <iostream>
#include "Estado.h"
#include <vector>

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
  private:
    std::vector<Estado> estados;
    std::vector<Estado> EstadoActual;
    std::vector<Estado> ProximosEstados;
};