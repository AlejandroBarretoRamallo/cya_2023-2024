#include <iostream>
#include "Alfabeto.h"
#include <fstream>
#include "Estado.h"
#include "Automata.h"
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
    if(simbolos[i] != ' ' && simbolos[i] != '&') {
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
  Automata automata(estados);  // creamos el automata
  while(FA >> estado) {
    std::multimap <char, int> transiciones;
    FA >> aceptacion >> ntransiciones;
    for(int i = 0; i < ntransiciones; ++i) {
      FA >> simbolo_ >> estado_siguiente;
      bool pertenece_ = 0;
      for (const int &elemento : alfabeto_FA.GetSet()) {
        if(elemento == simbolo_) { // comprobamos que el elemtno pertenece al alfabeto
          transiciones.insert({simbolo_, estado_siguiente}); // añadimos cada simbolo a su correspondiente estado siguiente
          pertenece_ = 1;
          break;
        }
      }
      if(!pertenece_) {
        std::cout << simbolo_ << " no pertenece al alfabeto\n";
        return 0;
      }
    }
    Estado EstadoQ(transiciones, aceptacion, ntransiciones); // creamos el objeto estado
    automata.AddEstados(EstadoQ);  // añadimos el estado al automata
  }
  std::ifstream cadenas(fichero_cadenas);  // abrimos el fichero con las cadenas
  if(!cadenas.is_open()) {  // comprobar que s epudo abrir el segundo archivo
    std::cout << "Error abriendo el archivo " << fichero_cadenas << std::endl;
    return 0;
  }
  std::string cadena;
  int posicion_cadena;
  while(getline(cadenas, cadena)) {  // leemos las cadenas del segundo fichero
    int aceptado = 0;
    posicion_cadena = 0;
    automata.VaciarEstadoActual();
    automata.AddEstadoActual(automata.GetVector()[estado_arranque]); // empezamos en el estado de arranque
    while(cadena.length() > posicion_cadena) {
      bool pertenece = 0;
      for(int i = 0; i < automata.GetEstadoActual().size(); ++i) { // recorremos los estados actuales
        for (const int &elemento : alfabeto_FA.GetSet()) {
          if(elemento == cadena[posicion_cadena]) { // comprobamos que el elemtno pertenece al alfabeto
            pertenece = 1;
            break;
          }
        }
        if(!pertenece) {
          std::cout << cadena << "-----no aceptada\n";
          break;
        }
        std::multimap <char, int > map = automata.GetEstadoActual()[i].GetMap(); // recorremos las transiciones de los estados que pertenecen al estado actual
        auto rango = map.equal_range(cadena[posicion_cadena]);  // rango contiene todos los valores asociados a un simbolo concreto
        auto encontrar = map.find('&'); // comprobamos si hay & transiciones
        if(encontrar != map.end()) {
          auto rango_ = map.equal_range('&'); // rango_ contiene la epsilon_transicion
          for (auto it_ = rango.first; it_ != rango.second; ++it_) {
            automata.AddProxEstado(automata.GetVector()[it_ -> second]); // añadimos a proximo estado todo lo que tenga coomo transicion epsilon
          }
        }
        for (auto it_ = rango.first; it_ != rango.second; ++it_) {
          automata.AddProxEstado(automata.GetVector()[it_ -> second]); // accedemos al vector de estados y añadimos el correspondiente a proximo estado
        }
      }
      automata.VaciarEstadoActual(); 
      for(int i = 0; i < automata.GetProxEstado().size();++i) {
        automata.AddEstadoActual(automata.GetProxEstado()[i]); // actualizamos en estado actual copiando los estados de prox estados
      }
      automata.VaciarProxEstado(); // vaciamos prox estados para poder repetir el proceso
      if(!pertenece) {
          break;
        }
      ++posicion_cadena; // vamos avanzando por la cadena 
    }
    for(int i = 0; i < automata.GetEstadoActual().size();++i) {  // recorremos el estado actual que tambien sera el estado final
      if(automata.GetEstadoActual()[i].IsAccepted()) {  // si cualquiera de los estados actuales es dde aceptacion, la cadena es aceptada
        aceptado = 1;
        break;
      }
    }
    if(aceptado == 1) {
      std::cout << cadena << "-----aceptada\n";
    }
    else {
      std::cout << cadena << "-----no aceptada\n";
    }
  } 
}

