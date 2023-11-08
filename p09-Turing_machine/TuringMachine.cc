#include "TuringMachine.h"
#include <fstream>

/**
 * @brief Constructor que lee un fichero con una maquina de turing especificada
 * @param input El nombre del fichero
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
    EstadosFinales.push_back(cadena[i] - 48);
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
    alfabeto_cinta.Push(read_simbol);  // añadir los simbolos que puede leer al alfabeto 
  }
}