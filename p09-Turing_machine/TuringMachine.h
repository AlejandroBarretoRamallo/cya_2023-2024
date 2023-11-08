#include <iostream>
#include <vector>
#include "Tupla.h"
#include "Alfabeto.h"

class TuringMachine {
  public:
    TuringMachine(std::string fichero);
  private:
    int NumEstados;
    int EstadoArranque;
    std::vector<int> EstadosFinales;
    std::vector<Tupla> Tuplas;
    Alfabeto alfabeto_cinta;
};