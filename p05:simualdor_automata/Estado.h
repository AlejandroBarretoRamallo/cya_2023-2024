#pragma once
#include <iostream>
#include <map>
#include <utility>
#include <vector>

class Estado{
  public:
    Estado(std::map <char, std::vector<int>> transiciones_);
    void AddTransicion(char simbolo, int estado_siguiente);
    std::map<char,std::vector<int>> GetMap();
    bool IsAccepted();
    int GetNtransiciones();
    void SetIsAccepted(bool aceptacion_);
    void SetNtransiciones(int ntransiciones_);
  private:
    std::map <char, std::vector<int>> transiciones;
    int ntransiciones;
    bool aceptacion;
};