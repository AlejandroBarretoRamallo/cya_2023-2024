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
  while (iterador != conjunto_no_terminales.end()) {  // nrecorrer no terminales
  char no_terminal = *iterador;
  auto rango = producciones.equal_range(no_terminal);
  for (auto it = rango.first; it != rango.second; ++it) {  // recorrer producciones
    std::string cadena = it -> second;
    for (int i = 0; i < cadena.size(); ++i) {  // comprobar si algun no terminal que no sea el de arranque produce &
      if (cadena[i] == '&') {
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
  while (iterador != conjunto_no_terminales.end()) {  // recorrer lkos no terminales
    char no_terminal = *iterador;
    auto rango = producciones.equal_range(no_terminal);
    for (auto it = rango.first; it != rango.second; ++it) {   // recorrer sus producciones
      std::string cadena = it -> second;
      if(cadena.size() == 1 && cadena[0] >= 65 && cadena[0] <= 90) {   // compropbar que no hayan producciones unitarias
        return 1;
      }
    }
    ++iterador;
  }
  auto rango = producciones.equal_range(arranque);  // comprobamos tambien si el estado de arranque no contiene producciones unicas
  for (auto it = rango.first; it != rango.second; ++it) {
    std::string cadena = it -> second;
    if (cadena.size() == 1 && cadena[0] >= 65 && cadena[0] <= 90) {
      return 1;
    }
  }
  return 0;
}

std::ostream& operator<<(std::ostream& out, Gramatica& a) {
  std::cout << "-------------------------\n";
  typedef std::multimap<char, std::string> produccion_;
  char arranque = a.GetArranque();  // empezamos por recorre rproducciones dle estado de arranque
  std::cout << arranque << "---> ";
  produccion_ produccionesS = a.GetProducciones();
  auto S = produccionesS.equal_range(arranque);
  for (auto it = S.first; it != S.second; ++it) {  // recorremos las producciones
    std::cout << it -> second;
    if (std::next(it) != S.second) {
      std::cout << "|";
    }
  }
  std::cout <<std::endl;
  Alfabeto alfabeto = a.GetAlfabeto();
  std::set<char> set = a.GetNoTerminales();
  auto iterador = set.begin();
  for (int i = 0; i < set.size(); ++i) { // recorremos los no terminales
    char no_terminal = *iterador;
    auto encontrar = produccionesS.find(no_terminal);
    if (encontrar != produccionesS.end()) {
      auto rango = produccionesS.equal_range(no_terminal);
      std::cout << no_terminal << "---> ";
      for(auto it = rango.first; it != rango.second; ++it) {   // recorremos sus producciones
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
  int num = 0;
    while (iterador != conjunto_no_terminales.end()) { // recorro los no terminales
    num = 0;
    char no_terminal = *iterador;
    auto rango = producciones.equal_range(no_terminal);
    std::string cadena;
    for (auto it = rango.first; it != rango.second; ++it) {  // compruebo si cada no terminal tiene una unica produccion
      ++num;
    }
    for (auto it = rango.first; it != rango.second; ++it) {  // recorro las difderentes producciones
      std::string cadena = it -> second;
      int cadena_ = int(cadena[0]);
      if(cadena.size() == 1 && (cadena_ < 65 || cadena_ > 90) && num <= 1) {  // si tieen euna unica produccion y es un terminal, guardarla en la string de peoducciones unicas de terminales ya añadidas
        added += cadena[0];
      }
    }
    ++iterador;
  }
  iterador = conjunto_no_terminales.begin();
  while (iterador != conjunto_no_terminales.end()) { // recorro los char
    char no_terminal = *iterador;
    auto rango = producciones.equal_range(no_terminal);
    std::string cadena;
    for (auto it = rango.first; it != rango.second; ++it) {  // recorro las difderentes producciones
      cadena = it -> second;
      if (cadena.size() >= 2) {   // solo recorro las producciones con 2 o mas simbolos
        for (int i = 0; i < cadena.size(); ++i) {  // recorro una produccion
          int cadena_ = int(cadena[i]);
          if (cadena_ < 65 || cadena_ > 90) { // si es no terminal busco una letra no utilizada para asignarla a el no terminal
            std::string letras = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            bool pertenece = 0;
            for (int j = 0; j < letras.size(); ++j) {
              pertenece = 0;
              for (auto elemento : conjunto_no_terminales) {
                if(elemento == letras[j]) {
                  pertenece = 1;
                  break;
                }
              }
              if (!pertenece) {
                bool terminal_ = 0;
                for (int k = 0; k < added.size(); ++k) {
                  if(added[k] == cadena[i]) {
                    terminal_ = 1;
                    break;
                  }
                }
                if (!terminal_) {
                conjunto_no_terminales.insert(letras[j]);  // añado el no terminal a las producciones y al conjunto no terminales
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
  std::map<char, char> producciones_unicas;
  iterador = conjunto_no_terminales.begin();
  while (iterador != conjunto_no_terminales.end()) { // recorro los char
    char no_terminal = *iterador;
    auto encontrar = producciones.find(no_terminal);
    if (encontrar == producciones.end()) {
      ++iterador;
      continue;
    }
    auto rango = producciones.equal_range(no_terminal);
    std::string cadena;
    num = 0;
    for (auto it = rango.first; it != rango.second; ++it) {
      ++num;
    }
    for (auto it = rango.first; it != rango.second; ++it) {  // recorro las difderentes producciones
    std::string cadena = it -> second;
    int cadena_ = int(cadena[0]);
      if (cadena.size() == 1 && (cadena_ < 65 || cadena_ > 90) && num <= 1) {  // revisar las producciones unicas de terminales
        char element = it -> first;
        producciones_unicas.emplace(element, cadena[0]);
      }
    }
    ++iterador;
  }
  //meter producciones unicas de terminales
  iterador = conjunto_no_terminales.begin();
  while (iterador != conjunto_no_terminales.end()) { // recorro los char
    char no_terminal = *iterador;
    auto rango = producciones.equal_range(no_terminal);
    std::string cadena;
    for (auto it = rango.first; it != rango.second; ++it) {  // recorro las difderentes producciones
      cadena = it -> second;
      if (cadena.size() > 1) {
        for (int i = 0; i < cadena.size(); ++i) {
          bool pertenece = 0;
          for (int j = 0; j < added.size(); ++j) {
            if (added[j] == cadena[i]) {
              pertenece = 1;
              break;
            }
          }
          if (!pertenece) {
            continue;
          }
          for (auto iterator = producciones_unicas.begin(); iterator != producciones_unicas.end(); ++iterator) {
            auto range = producciones_unicas.equal_range(iterator -> first);
            for (auto it_ = range.first; it_ != range.second; ++it_) {     // cambiar el no terminal
              if (it_ -> second == cadena[i]) {
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
  std::string prox_cadenas;
  std::string cadenas_actuales;
  for (auto elemento : conjunto_no_terminales) {
    auto rango = producciones.equal_range(elemento);
    for (auto it = rango.first; it != rango.second;) {  // revisar cadenas mayores o iguasles que tres
      prox_cadenas = "";
      cadenas_actuales = "";
      std::string cadena = it -> second;
      if (cadena.size() < 3) {
        ++it;
        continue;
      }
      std::string letras = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
      bool pertenece = 0;
      for (int i = 0; i < cadena.size() -2; ++i) {
        for (int j = 0; j < letras.size(); ++j) {
          pertenece = 0;
          for (auto elemento : conjunto_no_terminales) {
            if (elemento == letras[j]) {
              pertenece = 1;
              break;
            }
          }
          if (!pertenece) {
            prox_cadenas += letras[j];
            conjunto_no_terminales.insert(letras[j]);  // crear no terminales necesarios
            break;
          }
        }
      }
      for (int i = 0; i < cadena.size(); ++i) {
        cadenas_actuales += cadena[i];   // meter en una string los no terminales que ya estaban 
      }
      std::string cadenas = "";
      for (int i = 0; i < cadenas_actuales.size() - 1; ++i) {  // algoritmo para sustitur y reemplazar unas producciones por otras
        cadenas = "";
        if (i == 0) {
          cadenas += cadenas_actuales[0];
          cadenas += prox_cadenas[0];
          producciones.emplace(it -> first, cadenas);
          continue;
        }
        if (i == cadenas_actuales.size() - 2) {
          cadenas += cadenas_actuales[i];
          cadenas += cadenas_actuales[i + 1];
          producciones.emplace(prox_cadenas[i - 1], cadenas);
          break;
        }
        cadenas += cadenas_actuales[i];
        cadenas += prox_cadenas[i];
        producciones.emplace(prox_cadenas[i - 1], cadenas);            
      }
      it = producciones.erase(it);  // borrar produccion de tamaño >= 3
    }
  }
  conjunto_no_terminales.erase(arranque);
}