#include <iostream>
#include "Alfabeto.h"
#include <fstream>
#include "Estado.h"
#include "Automata.h"


int main(int argc, char *argv[]) {
  if (argc < 2) {   // comprobar si solo se ha indicado el nombre del programa
    std::cout << "Modo de empleo: ./p05_NFA_simulator input.fa input.txt \n";
    std::cout << "Pruebe ./p05_NFA_simulator --help para mas informacion.\n";
    return 0;
  }
  std::string argv2 = argv[1];
  if (argv2 == "--help") {  // opcion para mostrar una breve ayuda sobre el comando
    std::cout << "Se deben pasar como argumentos dos archivos. El primero es un .fa \n";
    std::cout << "que debe contener la descripcion del NFA, el segundo un .txt\n";
    std::cout << "que contiene cadenas las cuales se comprobará si son o no reconocidas por el NFA finito\n";
    return 0;
  }
  if (argc != 3) {   //comprobar que se han pasado los parametros correctamente
    std::cout << "Modo de empleo: ./p05_NFA_simulator input.fa input.txt \n";
    std::cout << "Pruebe ./p05_NFA_simulator --help para mas informacion.\n";
    return 0;
  }
  std::string fichero_FA = argv[1];
  std::string fichero_DFA = argv[2];
  std::ifstream FA(fichero_FA);
  if (!FA.is_open()) {     // comprobar si el archivo se pudo abrir
    std::cout << "Error: no se pudo abrir el archivo " << fichero_FA << "\n";
    return 0;
  }
  std::string simbolos;
  getline(FA,simbolos);  // leer la primera linea, que contiene los simbolos del alfabeto
  std::set<char> elementos_alfabeto;
  Alfabeto alfabeto_FA(elementos_alfabeto);  // creamos un objeto alfabeto
  for (int i = 0; i < simbolos.length(); ++i) {
    if (simbolos[i] != ' ' && simbolos[i] != '&') {
      alfabeto_FA.Push(simbolos[i]); // vamos insertando los simbolos en el alfabeto
    }
  }
  int numero_estados;
  FA >> numero_estados;  // la seungda linea nos indica el numero de estados del FA
  int estado_arranque;
  FA >> estado_arranque; // la tercera linea el estado de arranque
  int estado, estado_siguiente, ntransiciones;
  bool aceptacion;
  char simbolo_;
  std::vector<Estado> estados;
  Automata NFA(estados);  // creamos el NFA
  while (FA >> estado) {
    std::multimap <char, int> transiciones;
    FA >> aceptacion >> ntransiciones;
    for (int i = 0; i < ntransiciones; ++i) {
      FA >> simbolo_ >> estado_siguiente;
      bool pertenece_ = 0;
      for (const int &elemento : alfabeto_FA.GetSet()) {
        if (elemento == simbolo_ || simbolo_ == '&') { // comprobamos que el elemtno pertenece al alfabeto
          transiciones.insert({simbolo_, estado_siguiente}); // añadimos cada simbolo a su correspondiente estado siguiente
          pertenece_ = 1;
          break;
        }
      }
      if (!pertenece_) {
        std::cout << simbolo_ << " no pertenece al alfabeto\n";
        return 0;
      }
    }
    Estado EstadoQ(transiciones, aceptacion, ntransiciones); // creamos el objeto estado
    NFA.AddEstados(EstadoQ);  // añadimos el estado al NFA
  }
  typedef std::vector<std::vector<char>> conjuntos_estados;
  conjuntos_estados conjuntos_estados_1;
  std::vector<char> estadoq;
  estadoq.push_back(estado_arranque);
  bool pertenece = 0;      // meto ese conjunto en el conjunto de estados
  int indice = 0;
  conjuntos_estados_1.push_back(estadoq);
  while (true) {   // recorro el vector e conjunto de estados
    estadoq = conjuntos_estados_1[indice];  
    for (const char& elemento : alfabeto_FA.GetSet()) {  // recoorro los elementos del alfabeto
      pertenece = 0;
      NFA.Move(elemento, estadoq);  //hago delta de ese estado q
      NFA.EpsilonTransiciones(estadoq); // epsilon clausura de delta
      for (int j = 0; j < conjuntos_estados_1.size(); ++j) {
        if (estadoq.size() == conjuntos_estados_1[j].size()) {
          for (int k = 0; k < estadoq.size(); ++k) {
            if (estadoq[k] == conjuntos_estados_1[j][k]) {
              pertenece = 1;
            }
          }
        }
      }
      if (!pertenece) { 
        conjuntos_estados_1.push_back(estadoq); // si no existe ese conjunto de estados, metelo
      } 
    }
    ++indice;
    if (indice >= conjuntos_estados_1.size()) {
      break;
    }
  }
  std::ofstream DFA(fichero_DFA);
  if (!DFA.is_open()) {
    std::cout << "Error, no se pudo abrir  el fichero " << fichero_DFA << std::endl;
    return 0;
  }
  for (const char& elemento : alfabeto_FA.GetSet()) {  // imprimimos el alfabeto en el documento
    DFA << elemento << " ";
  }
  DFA << std::endl;
  DFA << conjuntos_estados_1.size();  // imprimimos el numero de estados
  DFA << std::endl;  
  DFA << estado_arranque << std::endl;  // imprimimos el estado de arranque
  for (int i = 0 ; i < conjuntos_estados_1.size(); ++i) {
    int contador = 0;
    bool aceptado = 0;
    for (int j = 0; j < conjuntos_estados_1[i].size(); ++j) {  // comprobamos si cualquier estado del conjunto es aceptado
      if (NFA.GetVector()[conjuntos_estados_1[i][j]].IsAccepted()) {
        aceptado = 1;
      }
    }
    DFA << i << " " << aceptado << " ";
    int ntransiciones = 0;
    for (const char elemento : alfabeto_FA.GetSet()) {
      std::set<int> set;
      for (int j = 0; j < conjuntos_estados_1[i].size(); ++j) { //contar el numero de transiciones , sumando los tamaños de los set de cada uno de los simbolos del alfabeto
        std::multimap<char, int> map = NFA.GetVector()[conjuntos_estados_1[i][j]].GetMap();
        auto simbolo = map.find(elemento);
        if (simbolo != map.end()) { // comprobar que  hay valores asociados a esa clave
          auto rango = map.equal_range(elemento);  
          for(auto iterador = rango.first; iterador != rango.second; ++ iterador) {
            set.insert(iterador -> second);   // añadir elementos al set para asegurarnos de que no se repiten
          }
          ntransiciones += set.size();
        }
      }
    }
    DFA << ntransiciones << " ";
    for (const char elemento : alfabeto_FA.GetSet()) {
      std::set<int> set;
      for (int j = 0; j < conjuntos_estados_1[i].size(); ++j) {  // vamos recorriendo los elementos del alfabeto y sus transiciones metiendolasa en un set por simbolo para no repetir
        std::multimap<char, int> map = NFA.GetVector()[conjuntos_estados_1[i][j]].GetMap();
        auto simbolo = map.find(elemento);
        if (simbolo != map.end()) { // comprobar si hay valores asociados a esa clave
          auto rango = map.equal_range(elemento);
          for (auto iterador = rango.first; iterador != rango.second; ++ iterador) {
            set.insert(iterador -> second);   // meter la transicion en el set para evitar valores duplicados
          }
          for (auto elemento_ : set) {
            DFA << elemento << " " << elemento_ << " ";   // imprimimos las transiciones 
          }
          DFA << std::endl;
        }
      }
    }
  }
}