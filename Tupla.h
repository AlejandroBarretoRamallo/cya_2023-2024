#pragma once
#include <iostream>

class Tupla {
  public:
    Tupla(int EstadoActual, int EstadoSiguiente, char ReadSimbol, char WriteSimbol, char Move);
    int GetEstadoActual();
    int GetEstadoSiguiente();
    char GetReadSimbol();
    char GetMove();
    char GetWriteSimbol();
  private:
    int EstadoActual_;
    int EstadoSiguiente_;
    char ReadSimbol_;
    char WriteSimbol_;
    char Move_;
};