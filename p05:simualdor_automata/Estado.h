#pragma once
#include <iostream>
#include <map>
#include <utility>
#include <vector>

class Estado{
  public:
    Estado(std::multimap <char, int> transiciones_, bool aceptacion_, int ntransiciones_); // constructor
    Estado(); // constructor por defecto
    void AddTransicion(char simbolo, int estado_siguiente);
    std::multimap<char, int> GetMap(); // getter
    bool IsAccepted();
    void SetIsAccepted(bool aceptacion_);  //setter
    void SetNtransiciones(int ntransiciones_); // setter
    int GetNtransiciones();  // getter
  private:
    std::multimap <char, int> transiciones;
    int ntransiciones;
    bool aceptacion;
};