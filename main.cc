#include "TuringMachine.h"

/**
 * @brief Comprueba que el numero de parametros sea correcto
 * @param argc Numero de parametros
 * @return si el numero es el adecuado o no
*/

bool CheckCorrectParameters(int argc) {
  return argc == 2 ? true : false;
}

/**
 * @brief Simula una maquina de Turing
 * @param argc Numero de parametros
 * @param argv Conjunto de parametros
*/

int main(int argc, char *argv[]) {
  if (!CheckCorrectParameters(argc)) {  // comprobar el numero de parametros
    std::cout << "No se han pasado el numero correcto de parametros.Puedes utilizar -h para mas informacion\n";
    return 0;
  }
  std::string nombre_archivo = argv[1];
  if (nombre_archivo == "-h") {   // comprobar si se quiere imprimir ayuda
    std::cout << "Se debe indicar el nombre de un archivo .tm con una maquina de turing especificada\n";
    return 0;
  }
  std::string cinta = "$";
  std::cout << "Introduce una cadena para comprobar si pertenece al lenguaje reconocido por la maquina de Turing\n";
  std::string cadena;
  std::cin >> cadena;
  for(char caracter : cadena) {
    cinta += caracter;
  }
  cinta += '$';
  TuringMachine MaquinaTuring(nombre_archivo); // creamos la maquina de turing
  if (MaquinaTuring.ReadString(cinta)) { // compruebo si la cadena pertenece
    std::cout << "Cadena aceptada\n";
  }
  else {
    std::cout << "Cadena no aceptada\n";
  }
  return 0;
}

