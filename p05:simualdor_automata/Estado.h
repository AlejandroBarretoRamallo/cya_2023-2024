#pragma once
#include <iostream>
#include <map>
#include <utility>
#include <vector>

class Estado{
  public:
    Estado(std::multimap <char, int> transiciones_, bool aceptacion_, int ntransiciones_);
    Estado();
    void AddTransicion(char simbolo, int estado_siguiente);
    std::multimap<char, int> GetMap();
    bool IsAccepted();
    void SetIsAccepted(bool aceptacion_);
    void SetNtransiciones(int ntransiciones_);
    int GetNtransiciones();
  private:
    std::multimap <char, int> transiciones;
    int ntransiciones;
    bool aceptacion;
};