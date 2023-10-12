#pragma once
#include <iostream>
#include "Estado.h"
#include <vector>

class ConjuntoEstados {
  public:
    ConjuntoEstados(std::vector<Estado> estados_);
    void AddEstados(Estado estado);
    void SetEstadoActual(int estado_actual);
    int GetEstadoActual();
    std::vector<Estado> GetVector();
  private:
    std::vector<Estado> estados;
    int EstadoActual;
};