#pragma once
#include <iostream>
#include <vector>
#include <set>
#include "Tupla.h"
#include "Alfabeto.h"

class TuringMachine {
  public:
    TuringMachine(std::string fichero);
    bool ReadString(std::string cinta);
    int FindTupla(int actual_state, char elemento);
    bool Acepted(int estado_final);
    bool GetFileOpened();
    void PrintMachine();
  private:
    int NumEstados;
    int EstadoArranque;
    std::set<int> EstadosFinales;
    std::vector<Tupla> Tuplas;
    Alfabeto AlfabetoCinta;
    int CabezaLectura;
    int EstadoActual;
    bool IsStopped;
    bool FileOpened;
};