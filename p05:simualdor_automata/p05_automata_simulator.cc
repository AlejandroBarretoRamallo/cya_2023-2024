#include <iostream>
#include "Alfabeto.h"
#include <fstream>
#include "Estado.h"
#include "ConjuntoEstados.h"
#include <vector>

int main(int argc, char *argv[]) {
  if(argc < 2) {   // comprobar si solo se ha indicado el nombre del programa
    std::cout << "Modo de empleo: ./p05_automata_simulator input.fa input.txt \n";
    std::cout << "Pruebe ./p05_automata_simulator --help para mas informacion.\n";
    return 0;
  }
  std::string argv2 = argv[1];
  if(argv2 == "--help") {  // opcion para mostrar una breve ayuda sobre el comando
    std::cout << "Se deben pasar como argumentos dos archivos. El primero es un .fa \n";
    std::cout << "que debe contener la descripcion del automata, el segundo un .txt\n";
    std::cout << "que contiene cadenas las cuales se comprobará si son o no reconocidas por el automata finito\n";
    return 0;
  }
  if(argc != 3) {   //comprobar que se han pasado los parametros correctamente
    std::cout << "Modo de empleo: ./p05_automata_simulator input.fa input.txt \n";
    std::cout << "Pruebe ./p05_automata_simulator --help para mas informacion.\n";
    return 0;
  }
  std::string fichero_FA = argv[1];
  std::string fichero_cadenas = argv[2];
  std::ifstream FA(fichero_FA);
  if(!FA.is_open()) {     // comprobar si el archivo se pudo abrir
    std::cout << "Error: no se pudo abrir el archivo " << fichero_FA << "\n";
    return 0;
  }
  std::string simbolos;
  getline(FA,simbolos);  // leer la primera linea, que contiene los simbolos del alfabeto
  std::set<char> elementos_alfabeto;
  Alfabeto alfabeto_FA(elementos_alfabeto);  // creamos un objeto alfabeto
  for(int i = 0; i < simbolos.length(); ++i) {
    if(simbolos[i] != ' ') {
      alfabeto_FA.Push(simbolos[i]); // vamos insertando los simbolos en el alfabeto
    }
  }
  int numero_estados;
  FA >> numero_estados;  // la seungda linea nos indica el numero de estados del FA
  int estado_arranque;
  FA >> estado_arranque; // la tercera linea el estado de arranque
  int estado, estado_siguiente, ntransiciones, aceptacion;
  char simbolo_;
  std::vector<Estado> estados;
  ConjuntoEstados conjunto_estados(estados);
  std::map <char, std::vector<int>> transiciones;
  while(FA >> estado) {
    FA >> aceptacion >> ntransiciones;
    Estado q(transiciones, aceptacion, ntransiciones);
    conjunto_estados.AddEstados(q);
    for(int i = 0; i < ntransiciones; ++i) {
      while(true) {
        FA >> simbolo_;
        if(simbolo_ != ' ') {
          FA >> estado_siguiente;
          break;
        }
      }
      conjunto_estados.GetVector()[estado].AddTransicion(simbolo_, estado_siguiente); // posteriormente vamos metiendo las transiciones en el map;
    }

  }
  /**
  std::ifstream cadenas(fichero_cadenas);
  if(!cadenas.is_open()) {
    std::cout << "Error, no se pudo abrir el archivo " << fichero_cadenas << "\n";
    return 0;
  }
  std::string cadena;
  int posicion_cadena = 0;
  while(getline(cadenas, cadena)) {  // bucle while para reconocer las cadenas 
    posicion_cadena = 0;
    conjunto_estados.VaciarEstadoActual();
    conjunto_estados.AddEstadoActual(conjunto_estados.GetVector()[estado_arranque]);  // iniciamos en el estado de arranque
    while(cadena.length() > posicion_cadena) {
      for(int i = 0; i < conjunto_estados.GetEstadoActual().size(); ++i) { // recorremos los estados actuales
        std::vector<int> transiciones_ = conjunto_estados.GetEstadoActual()[i].GetMap().at(cadena[posicion_cadena]);  // miramos los estados siguientes
        for(int j = 0; j < transiciones_.size(); ++i) {
          conjunto_estados.AddProxEstado(conjunto_estados.GetVector()[transiciones_[j]]); // añadimos los estados a los que pasaremos
        }
      }
      conjunto_estados.VaciarEstadoActual(); // vaciamos el vector de estados actuales
      conjunto_estados.GetEstadoActual().resize(conjunto_estados.GetProxEstado().size());  //le cambianos el tamaño al de los proximos estados
      for(int i = 0; i < conjunto_estados.GetProxEstado().size(); ++i) {   // estado_actual = proximos estados
        conjunto_estados.AddEstadoActual(conjunto_estados.GetProxEstado()[i]);
      }
      conjunto_estados.VaciarProxEstado(); // vaciamos el vector de proximos estados
      ++posicion_cadena;
    }
    int aceptado = 0;
    for(int i = 0; i < conjunto_estados.GetEstadoActual().size(); ++i) {
      if(conjunto_estados.GetEstadoActual()[i].IsAccepted()) {
        aceptado = 1;
        break;
      }
    }
    if(aceptado == 0) {
      std::cout << cadena << "------------- no aceptada\n";
    }
    else {
      std::cout << cadena << "------------- aceptada\n";
    }
  } **/
}

