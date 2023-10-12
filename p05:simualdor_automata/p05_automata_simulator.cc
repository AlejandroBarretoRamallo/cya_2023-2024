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
  FA >> estado_arranque;
  int estado, estado_siguiente;
  char simbolo_;
  int nombre_estado = 0;
  std::vector<Estado> estados;
  ConjuntoEstados conjunto_estados(estados);
  std::map <char, int> transiciones;
  for(int i = 0; i < numero_estados; ++i) { // crear todos los estados y meterlos en el vector de ConjuntoEstados
    Estado q(transiciones);
    conjunto_estados.AddEstados(q);
  }
  while(FA >> simbolo_) {   // bucle while para crear el automata finito
    if(simbolo_ == ' ') {
      continue;
    }
    FA >> estado >> estado_siguiente;
    conjunto_estados.GetVector()[estado].AddTransicion(estado_siguiente, simbolo_);
  }
  std::ifstream cadenas(fichero_cadenas);
  if(!cadenas.is_open()) {
    std::cout << "Error, no se pudo abrir el archivo " << fichero_cadenas << "\n";
    return 0;
  }
  std::string cadena;
  int posicion_cadena = 0;
  while(getline(cadenas, cadena)) {  // bucle while para reconocer las cadenas 
    conjunto_estados.SetEstadoActual(estado_arranque); // iniciamos en el estado de arranque
    int estado_actual = conjunto_estados.GetEstadoActual();
    conjunto_estados.GetVector()[estado_actual];
  }
}