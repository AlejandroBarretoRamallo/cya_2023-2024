#pragma once
#include <iostream>
#include "Estado.h"
#include <vector>

class ConjuntoEstados {
  public:
    ConjuntoEstados(std::vector<Estado> estados_);
    void AddEstados(Estado estado);
    std::vector<Estado> GetEstadoActual();
    void AddEstadoActual(Estado estado);
    std::vector<Estado> GetVector();
    std::vector<Estado> GetProxEstado();
    void AddProxEstado(Estado estado);
    void VaciarProxEstado();
    void VaciarEstadoActual();
  private:
    std::vector<Estado> estados;
    std::vector<Estado> EstadoActual;
    std::vector<Estado> ProximosEstados;
};