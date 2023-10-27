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
  std::cout << "-------------------------\n";
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
  std::string added = "";
    while(iterador != conjunto_no_terminales.end()) { // recorro los char
    char no_terminal = *iterador;
    auto rango = producciones.equal_range(no_terminal);
    std::string cadena;
    for(auto it = rango.first; it != rango.second; ++it) {  // recorro las difderentes producciones
      std::string cadena = it -> second;
      int cadena_ = int(cadena[0]);
      if(cadena.size() == 1 && (cadena_ < 65 || cadena_ > 90)) {
        added += cadena[0];
      }
    }
    ++iterador;
  }
  iterador = conjunto_no_terminales.begin();
  while(iterador != conjunto_no_terminales.end()) { // recorro los char
    char no_terminal = *iterador;
    auto rango = producciones.equal_range(no_terminal);
    std::string cadena;
    for(auto it = rango.first; it != rango.second; ++it) {  // recorro las difderentes producciones
      cadena = it -> second;
      if(cadena.size() >= 2) {
        for(int i = 0; i < cadena.size(); ++i) {  // recorro una produccion
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
                bool terminal_ = 0;
                for(int k = 0; k < added.size(); ++k) {
                  if(added[k] == cadena[i]) {
                    terminal_ = 1;
                    break;
                  }
                }
                if(!terminal_) {
                conjunto_no_terminales.insert(letras[j]);
                std::string terminal = "";
                terminal += cadena[i];
                producciones.emplace(letras[j], terminal);
                added +=cadena[i];
                }
                break;
              }
            }
          }
        }
      }
      int cadena_ = int(cadena[0]);
    }
    ++iterador;
  }
  std::multimap<char, char> producciones_unicas;
  iterador = conjunto_no_terminales.begin();
  while(iterador != conjunto_no_terminales.end()) { // recorro los char
    char no_terminal = *iterador;
    auto rango = producciones.equal_range(no_terminal);
    std::string cadena;
    for(auto it = rango.first; it != rango.second; ++it) {  // recorro las difderentes producciones
    std::string cadena = it -> second;
    int cadena_ = int(cadena[0]);
      if(cadena.size() == 1 && (cadena_ < 65 || cadena_ > 90)) {
        char element = it -> first;
        producciones_unicas.emplace(element, cadena[0]);
      }
    }
    ++iterador;
  }
  iterador = conjunto_no_terminales.begin();
  while(iterador != conjunto_no_terminales.end()) { // recorro los char
    char no_terminal = *iterador;
    auto rango = producciones.equal_range(no_terminal);
    std::string cadena;
    for(auto it = rango.first; it != rango.second; ++it) {  // recorro las difderentes producciones
      cadena = it -> second;
      if(cadena.size() > 1) {
        for(int i = 0; i < cadena.size(); ++i) {
          bool pertenece = 0;
          for(int j = 0; j < added.size(); ++j) {
            if(added[j] == cadena[i]) {
              pertenece = 1;
              break;
            }
          }
          if(!pertenece) {
            continue;
          }
          for(auto iterator = producciones_unicas.begin(); iterator != producciones_unicas.end(); ++iterator) {
            auto range = producciones_unicas.equal_range(iterator -> first);
            for(auto it_ = range.first; it_ != range.second; ++it_) {
              if(it_ -> second == cadena[i]) {
                it -> second[i] = iterator -> first;
                break;
              }
            }
          }
        }
      }
    }
    ++iterador;
  }
  //mitad algoritmo
  //añadir todas las producciones de 2 no terminales
  std::multimap<char, std::string>  dobles_no_terminales;
  iterador = conjunto_no_terminales.begin();
    while(iterador != conjunto_no_terminales.end()) {
    char no_terminal = *iterador;
    auto rango = producciones.equal_range(no_terminal);
    for (auto it = rango.first; it != rango.second; ++it) {
      std::string cadena = it -> second;
      if(cadena.size() != 2) {
        continue;
      }
      int cadena0 = int(cadena[0]), cadena1 = int(cadena[1]);
      if(cadena0 >= 65 && cadena0 <= 90 && cadena1 >= 65 && cadena1 <= 90) {
        dobles_no_terminales.emplace(it -> first, cadena);
      }
    }
    ++iterador;
  }
   //despues de eso, volver a recorrer las producciones en busa de las que tengan longitud >= 3
   iterador = conjunto_no_terminales.begin();
  while(iterador != conjunto_no_terminales.end()) {
    char no_terminal = *iterador;
    auto rango = producciones.equal_range(no_terminal);
    for (auto it = rango.first; it != rango.second; ++it) {
      std::string cadena = it -> second;
      if(cadena.size() < 3) {
        continue;
      }
      for(int i = cadena.size() - 2; i < cadena.size(); ++i) {
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
          bool added = 0;
          
          //despues de eso, volver a recorrer las producciones en busa de las que tengan longitud >= 3
          //comrpobar si ya hay alguna produccion que ya tenga unicamente Bn Dn
          //si no hay, añadirlas
          //guardar en un multimap todas las añadidas
          //buscar en todas las producciones, y si se encuentra alguna de las añadidas, sustituirla por su produccion
          break;
        }
        }
      }
    }
    ++iterador;
  }
  conjunto_no_terminales.erase(arranque);
}