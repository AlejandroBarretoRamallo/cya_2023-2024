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

void Gramatica::BorrarProduccionesVacias() {
  
}

void Gramatica::BorrarProduccionesUnitarias() {
  auto iterador = conjunto_no_terminales.begin();
  while(iterador != conjunto_no_terminales.end()) {
    char elemento = *iterador;
    auto encontrar = producciones.find(elemento);
    if(encontrar != producciones.end()) {
      auto rango = producciones.equal_range(elemento);
      for(auto it = rango.first; it != rango.second; ++it) {
        std::string produccion_A = it -> second;
        int no_terminal = int(produccion_A[0]);
        if(produccion_A.size() == 1 && no_terminal >= 65 && no_terminal <= 90 ) {
          if(elemento == produccion_A[0]) {
            it = producciones.erase(it);
          }
          else {                                                                              //pendiente
          }
        }
      }
    }
    ++iterador;
  }
}

void Gramatica::BorrarSimbolosInutiles() {
  // etapa 1
  std::string conjunto = "";
  auto iterador = conjunto_no_terminales.begin();
  while(iterador != conjunto_no_terminales.end()) {
    char no_terminal = *iterador;
    if(no_terminal == arranque) {
      ++iterador;
      continue;
    }
    auto encontrado = producciones.find(no_terminal);
    if(encontrado != producciones.end()) {
      auto rango = producciones.equal_range(no_terminal);
      bool solo_terminales = 1;
      for(auto it = rango.first; it != rango.second; ++it) {
        std::string cadena = it -> second;
        for(int i = 0; i < cadena.size(); ++i) {
          int cadena_ = int(cadena[i]);
          if(cadena_ >= 65 && cadena_ <= 90  && cadena != "&") {
            solo_terminales = 0;
          }
        }
        if(solo_terminales) {
          conjunto += no_terminal;
        }
        if(solo_terminales) {
        break;
        }
      }
    }
    ++iterador;
  }
  bool added = 1;
  while(added) {
    added = 0;
      iterador = conjunto_no_terminales.begin();
      while (iterador != conjunto_no_terminales.end()) {
        char no_terminal = *iterador;
        auto encontrar = producciones.find(no_terminal);
        bool pertenece = 1;
        if(encontrar != producciones.end()) {
          auto rango = producciones.equal_range(no_terminal);
          std::string cadena;
          for(auto it = rango.first; it != rango.second; ++it) {
            pertenece = 1;
            cadena = it -> second;
            for(int i = 0; i < cadena.size(); ++i) {
              bool pertenece_ = 0;
              if(cadena[i] < 65 || cadena[i] > 90) {    // sia lgo falla, es la parta de alfa
                if(i == 0) {
                  pertenece_ = 1;
                }
                break;
              }
              for(int j = 0; j < conjunto.size(); ++j) {
                if(conjunto[j] == cadena[i]) {
                  pertenece = 1;
                }
              }
              if(!pertenece_) {
                pertenece = 0;
                break;
              }
            }
            if(pertenece) {
              bool encontrado = 0;
              for(int i = 0 ; i < conjunto.size(); ++i) {
                if(conjunto[i] == it -> first) {
                  encontrado = 1;
                }
              }
              if(!encontrado) {
                conjunto += it -> first;
              }
            }
          }
        }
        ++iterador;
      }
  }
  bool perteneceA = 0;
  std::string eliminar = "";
  for(char no_term:conjunto_no_terminales) {
    perteneceA = 0;
    for(int i = 0; i < conjunto.size(); ++i) {
      if(conjunto[i] == no_term) {
        perteneceA = 1;
      }
    }
    if(!perteneceA) {
      eliminar += no_term;
    }
  }
  for(int i = 0; i < eliminar.size(); ++i) {
    conjunto_no_terminales.erase(eliminar[i]);
  }
  iterador = conjunto_no_terminales.begin();
  while(iterador != conjunto_no_terminales.end()) {
    char elemento = *iterador;
    auto encontrar = producciones.find(elemento);
    bool añadir = 0;
    if(encontrar != producciones.end()) {
      auto rango = producciones.equal_range(elemento);
      for(auto it = rango.first; it != rango.second;) {
        std::string produccion_A = it -> second;
        for(int i = 0; i < produccion_A.size(); ++i) {
          if(produccion_A[i] >= 65 && produccion_A[i] <= 90) {
            int count = conjunto_no_terminales.count(produccion_A[i]);
            if(count == 0) {
              it = producciones.erase(it);
              añadir = 0;
              break;
            }
            else {
              añadir = 1;
            }
          }
          else {
            añadir = 1;
          }
        }
        if(añadir) {
          ++it;
        }
      }
    }
    ++iterador; 
  }
  char elemento = arranque;
  auto encontrar = producciones.find(elemento);
  bool añadir = 0;
  if(encontrar != producciones.end()) {
    auto rango = producciones.equal_range(elemento);
    for(auto it = rango.first; it != rango.second;) {
      std::string produccion_A = it -> second;
      for(int i = 0; i < produccion_A.size(); ++i) {
        if(produccion_A[i] >= 65 && produccion_A[i] <= 90) {
          int count = conjunto_no_terminales.count(produccion_A[i]);
          if(count == 0) {
            it = producciones.erase(it);
            añadir = 0;
            break;
          }
          else {
            añadir = 1;
          }
        }
        else {
          añadir = 1;
        }
      }
      if(añadir) {
        ++it;
      }
    }
  }
  // etapa 2
  std::string j = "";
  j += arranque;
  std::string v = j;
  std::string sumatorio = "";
  while(j != "") {
    // j = j - {A}
    std::string j_ = "";
    char no_term = j[0];
    for(int i = 1; i <= j.size(); ++i) {
      j_ += j[i];
    }
    j.resize(0);
    j = j_;
    auto encontrar = producciones.find(no_term);
    if(encontrar != producciones.end()) {
      auto rango = producciones.equal_range(no_term);
      for(auto it = rango.first; it != rango.second; ++it) {
        std::string cadena = it -> second;
        for(int i = 0; i < cadena.size(); ++i) {  // error sumatorio, corregir
          int cadena_ = int(cadena[i]);
          if(cadena_ >= 65 && cadena_ <= 90) {
            continue;
          }
          else {
            sumatorio += cadena[i];
            std::cout << cadena[i];
          }
        }
        std::string no_terminales;
        for(int i = 0; i < cadena.size(); ++i) {
          int cadena_ = int(cadena[i]);
          if(cadena_ < 65 || cadena_ > 90) {
            continue;
          }
          else {
            no_terminales += cadena[i];
          }
        }
        for(int i = 0; i < no_terminales.size(); ++i) {
          bool pertenece = 0;
          for(int k = 0; k < v.size(); ++k) {
            if(v[k] == no_terminales[i]) {
              pertenece = 1;
            }
          }
          if(!pertenece) {
            v += no_terminales[i];
            j += no_terminales[i];
          }
        }
      }
      bool perteneceA = 0;
      std::string eliminar = "";
      for(char no_term:conjunto_no_terminales) {
        perteneceA = 0;
        for(int i = 0; i < v.size(); ++i) {
          if(v[i] == no_term) {
            perteneceA = 1;
          }
        }
        if(!perteneceA) {
          eliminar += no_term;
        }
      }
      for(int i = 0; i < eliminar.size(); ++i) {
        conjunto_no_terminales.erase(eliminar[i]);
      }
      std::set<char> alph = alfabeto.GetSet();
      std::string eliminar_ = "";
      for(char term:alph) {
        perteneceA = 0;
        for(int i = 0; i < sumatorio.size(); ++i) {
          if(sumatorio[i] == term) {
            perteneceA = 1;
          }
        }
        if(!perteneceA) {
          eliminar_ += term;
        }
        //revisar cadena eliminar_ y eliminar producciones con algun elemento de eleminar o eliminar_
      }
    }
    j.resize(j.size() - 1);
  }
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



/**auto iterador = conjunto_no_terminales.begin();
  while(iterador != conjunto_no_terminales.end()) {
    char elemento = *iterador;
    auto encontrar = producciones.find(elemento);
    if(encontrar != producciones.end()) {
      auto rango = producciones.equal_range(elemento);
      for(auto it = rango.first; it != rango.second;) {
        if(it -> second == "&") {
          it = producciones.erase(it); // quitar las producciones epsilon
          auto rango_ = producciones.equal_range(arranque);
          //añadir producciones a s
          for(auto it_ = rango_.first; it_ != rango_.second; ++it_) {
            std::string produccion_A = it_ -> second;
            for(int i = 0; i < produccion_A.size(); ++i) {
              if (produccion_A[i] == elemento) {
                std::string nueva_produccion = "";
                for(int j = 0; j < produccion_A.size(); ++j) {
                  if(produccion_A[j] != elemento) {
                    nueva_produccion += produccion_A[j];
                  }
                }
                if(nueva_produccion != "") {
                  producciones.emplace(arranque, nueva_produccion);
                }
              }
            }
          }
          //añadir producciones al no terminal que producia epsilon
          for(auto it_ = rango.first; it_ != rango.second; ++it_)  {
            std::string produccion_elem = it_ -> second;
            for(int i = 0; i < produccion_elem.size(); ++i) {
              if(produccion_elem[i] == elemento) {
                std::string nueva_produccion = "";
                for(int j = 0; j < produccion_elem.size(); ++j) {
                  if(produccion_elem[j] != elemento) {
                    nueva_produccion += produccion_elem[j];
                  }
                }
                if(nueva_produccion != "") {
                  producciones.emplace(elemento, nueva_produccion);
                }
              }
            }
          }
        } else {
          ++it;
        }
      }
    }
    ++iterador;
  }
**/