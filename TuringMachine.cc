#include "TuringMachine.h"
#include <fstream>

/**
 * @brief Constructor que lee un fichero con una maquina de turing especificada
 * @param archivo_entrada El nombre del fichero
*/

TuringMachine::TuringMachine(std::string archivo_entrada) {
  std::ifstream input(archivo_entrada); // abrir fichero de entrada
  std::string linea;
  input >> NumEstados;
  input >> EstadoArranque;
  std::string cadena;
  getline(input, cadena);
  getline(input, cadena);
  for (int i = 0; i < cadena.size(); ++i) { // leer estados finales
    EstadosFinales.insert(cadena[i] - 48);
    ++i;
  }
  int NumTuplas;
  input >> NumTuplas;
  int actual_state, estado_siguiente;
  char read_simbol, write_simbol, move;
  for (int i = 0; i < NumTuplas; ++i) {  // leer todas las tuplas
    input >> actual_state >> read_simbol  >> write_simbol >> move >> estado_siguiente;
    Tupla tupla(actual_state, estado_siguiente, read_simbol, write_simbol, move); // construir una tupla por cada liena
    Tuplas.push_back(tupla);  // añadir la tupla al conjunto de tuplas
    AlfabetoCinta.Push(read_simbol);  // añadir los simbolos que puede leer al alfabeto 
  }
  EstadoActual = EstadoArranque;
  CabezaLectura = 1;
  IsStopped = 0;
}

/**
 * @brief Comprueba si dada una cinta y una cadena, la cadena pertenece al lenguaje
 * @brief reconocido por la maquina de turing
 * @param cadena Cadena a comprobar
 * @param cinta La cinta con la cadena y los blancos
 * @return Si la cadena pertenece o no
*/

bool TuringMachine::ReadString(std::string cinta) {
  while (!IsStopped) {
    if (!FindTupla(EstadoActual, cinta[CabezaLectura])) {
      IsStopped = true;
      continue;
    }
    
  }
  for (int estado : EstadosFinales) {
    if (estado == EstadoActual) {
      return true;
    }
  }
  return false;
}

/**
 * @brief Busca si hay alguna transicion definida para el estado actual y el simbolo que se lee
 * @param actual_state Estado en el que se encuentra la maquina
 * @param elemento Caracter que lee la maquina
 * @return -1 si no se ha encontrado, en cualquier otro caso devuelve su posicion en el vector
*/

int TuringMachine::FindTupla(int actual_state, char elemento) {
  for (int i = 0; i < Tuplas.size(); ++i) {
    if (Tuplas[i].GetEstadoActual() == actual_state && Tuplas[i].GetReadSimbol() == elemento) {
      return i;
    }
  }
  return -1;
}