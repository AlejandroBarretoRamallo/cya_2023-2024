#pragma once
#include <iostream>
#include <map>
#include <utility>
#include <vector>

class Estado{
  public:
    Estado(std::map <char, std::vector<int>> transiciones_, bool aceptacion_, int ntransiciones_);
    Estado();
    void AddTransicion(char simbolo, int estado_siguiente);
    std::map<char,std::vector<int>> GetMap();
    bool IsAccepted();
    void SetIsAccepted(bool aceptacion_);
    void SetNtransiciones(int ntransiciones_);
    int GetNtransiciones();
  private:
    std::map <char, std::vector<int>> transiciones;
    int ntransiciones;
    bool aceptacion;
};