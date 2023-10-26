#include "Gramatica.h"
#include <map>

typedef std::multimap<char, std::string> produccion_;

Alfabeto Gramatica::GetAlfabeto() {
  return alfabeto;
}

Gramatica::Gramatica(std::set<char> conjunto_no_terminales_, Alfabeto alfabeto_, char arranque_, std::multimap<char, std::string> producciones_) {
  conjunto_no_terminales = conjunto_no_terminales_;
  alfabeto = alfabeto_;
  arranque = arranque_;
  producciones = producciones_;
}

std::set<char> Gramatica::GetNoTerminales() {
  return conjunto_no_terminales;
}

char Gramatica::GetArranque() {
  return arranque;
}

std::multimap<char, std::string> Gramatica::GetProducciones() {
  return producciones;
}

bool Gramatica::ComprobarProduccionesVacias() {
  auto iterador = conjunto_no_terminales.begin();
  while(iterador != conjunto_no_terminales.end()) {
  char no_terminal = *iterador;
  auto rango = producciones.equal_range(no_terminal);
  for(auto it = rango.first; it != rango.second; ++it) {
    std::string cadena = it -> second;
    for(int i = 0; i < cadena.size(); ++i) {
      if(cadena[i] == '&') {
        return 1;
      }
    }
  }
    ++iterador;
  }
  return 0;
}

bool Gramatica::ComprobarProduccionesUnitarias() {
  auto iterador = conjunto_no_terminales.begin();
  while(iterador != conjunto_no_terminales.end()) {
    char no_terminal = *iterador;
    auto rango = producciones.equal_range(no_terminal);
    for(auto it = rango.first; it != rango.second; ++it) {
      std::string cadena = it -> second;
      if(cadena.size() == 1 && cadena[0] >= 65 && cadena[0] <= 90) {
        return 1;
      }
    }
    ++iterador;
  }
  auto rango = producciones.equal_range(arranque);
  for(auto it = rango.first; it != rango.second; ++it) {
    std::string cadena = it -> second;
    if(cadena.size() == 1 && cadena[0] >= 65 && cadena[0] <= 90) {
      return 1;
    }
  }
  return 0;
}

std::ostream& operator<<(std::ostream& out, Gramatica& a) {
  std::cout << "--------------------\n";
  typedef std::multimap<char, std::string> produccion_;
  char arranque = a.GetArranque();
  std::cout << arranque << "---> ";
  produccion_ produccionesS = a.GetProducciones();
  auto S = produccionesS.equal_range(arranque);
  for(auto it = S.first; it != S.second; ++it) {
    std::cout << it -> second;
    if(std::next(it) != S.second) {
      std::cout << "|";
    }
  }
  std::cout <<std::endl;
  Alfabeto alfabeto = a.GetAlfabeto();
  std::set<char> set = a.GetNoTerminales();
  auto iterador = set.begin();
  for(int i = 0; i < set.size(); ++i) {
    char no_terminal = *iterador;
    auto encontrar = produccionesS.find(no_terminal);
    if(encontrar != produccionesS.end()) {
      auto rango = produccionesS.equal_range(no_terminal);
      std::cout << no_terminal << "---> ";
      for(auto it = rango.first; it != rango.second; ++it) {
        std::cout << it -> second;
        if(std::next(it) != rango.second) {
          std::cout << "|";
        }
      }
      std::cout << std::endl;
    }
    ++iterador;
  }
  std::cout << "-------------------------\n";
  return out;
}

void Gramatica::TransformarCNF() {
  conjunto_no_terminales.insert(arranque);
  auto iterador = conjunto_no_terminales.begin();
  while(iterador != conjunto_no_terminales.end()) {
    char no_terminal = *iterador;
    auto rango = producciones.equal_range(no_terminal);
    std::string cadena;
    for(auto it = rango.first; it != rango.second; ++it) {
      cadena = it -> second;
      if(cadena.size() >= 2) {
        for(int i = 1; i < cadena.size(); ++i) {
          int cadena_ = int(cadena[i]);
          if(cadena_ < 65 || cadena_ > 90) {
            std::string letras = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            bool pertenece = 0;
            for(int j = 0; j < letras.size(); ++j) {
              pertenece = 0;
              for(auto elemento : conjunto_no_terminales) {
                if(elemento == letras[j]) {
                  pertenece = 1;
                  break;
                }
              }
              if(!pertenece) {
                conjunto_no_terminales.insert(letras[j]);
                std::string terminal = "";
                terminal += cadena[i];
                it -> second[i] = letras[j];
                producciones.emplace(letras[j], terminal);
                break;
              }
            }
          }
        }
      }
    }
    ++iterador;
  }
  iterador = conjunto_no_terminales.begin();
  while(iterador != conjunto_no_terminales.end()) {
    char no_terminal = *iterador;
    if(no_terminal == arranque) {
      ++iterador;
      continue;
    }
    auto rango = producciones.equal_range(no_terminal);/**
    for(auto it = rango.first; it != rango.second; ++it) {
      std::string cadena = it -> second;
      int cadena_ = int(cadena[0]);
      if(cadena.size() != 1 || (cadena_ >= 65 && cadena_ <=90 )) {
        continue;
      }
      char terminal = cadena[0];
      auto iterador_ = conjunto_no_terminales.begin();
      while(iterador_ != conjunto_no_terminales.end()) {
        char no_terminal_ = *iterador_;
        auto rango_ = producciones.equal_range(no_terminal_);
        for(auto it_ = rango_.first; it_ != rango_.second;) {
          std::string cadena2 = it_ -> second;
          if(cadena2.size() == 1 && cadena[0] == terminal) {
            it_ = producciones.erase(it_);

          }
          else {
            ++it_;
          }
        }
        ++iterador_;
      }
    }**/
    ++iterador;
  }
  conjunto_no_terminales.erase(arranque);
}