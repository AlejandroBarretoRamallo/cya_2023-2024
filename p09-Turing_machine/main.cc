#include "TuringMachine.h"
#include <fstream>

/**
 * @brief Comprueba que el numero de parametros sea correcto
 * @param argc Numero de parametros
 * @return si el numero es el adecuado o no
*/

bool CheckCorrectParameters(int argc) {
  if (argc == 2 || argc == 3) {
    return true;
  }
  return false;
}

/**
 * @brief Simula una maquina de Turing
 * @param argc Numero de parametros
 * @param argv Conjunto de parametros
*/

int main(int argc, char *argv[]) {
  if (!CheckCorrectParameters(argc)) {  // comprobar el numero de parametros
    std::cout << "No se han pasado el numero correcto de parametros.Puedes utilizar --h para mas informacion\n";
    return 0;
  }
  std::string nombre_archivo = argv[1];
  if (nombre_archivo == "--h") {   // comprobar si se quiere imprimir ayuda
    std::cout << "Se debe indicar el nombre de un archivo .tm con una maquina de turing especificada y un archivo.tape con el contenido inicial de la cinta\n";
    return 0;
  }
  if (argc == 2 && nombre_archivo != "--h") {
    std::cout << "Se estan introduciendo los parametros incorrectos. Consulta --h\n";
    return 0;
  }
  std::string cinta = "$";
  std::string cadena;
  std::string arhcivo_cadena = argv[2];
  std::ifstream input2(arhcivo_cadena); // abrir el .tape
  input2 >> cadena;
  cinta += cadena;
  cinta += '$';
  TuringMachine MaquinaTuring(nombre_archivo); // creamos la maquina de turing
  if (!MaquinaTuring.GetFileOpened()) {
    return 0;
  }
  MaquinaTuring.PrintMachine();
  if (MaquinaTuring.ReadString(cinta)) { // compruebo si la cadena pertenece
    std::cout << "Cadena ACEPTADA\n";
  }
  else {
    std::cout << "Cadena NO ACEPTADA\n";
  }
  return 0;
}

