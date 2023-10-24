#include <iostream>
#include "Alfabeto.h"
#include <fstream>
#include "Gramatica.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {   // comprobar si solo se ha indicado el nombre del programa
    std::cout << "Modo de empleo: ./p07-Grammar2CNF input.gra output.gr \n";
    std::cout << "Pruebe ./p07-Grammar2CNF --help para mas informacion\n";
    return 0;
  }
  std::string argv2 = argv[1];
  if (argv2 == "--help") {  // opcion para mostrar una breve ayuda sobre el comando
    std::cout << "Se deben pasar como argumentos dos archivos. El primero es un .gra \n";
    std::cout << "que debe contener la descripcion del una gramatica, el segundo un .gra\n";
    std::cout << "que al finlaizar el programa contendra la gramatica en forma normal de chonsky\n";
    return 0;
  }
  if (argc != 3) {   //comprobar que se han pasado los parametros correctamente
    std::cout << "Modo de empleo: ./p07-Grammar2CNF input.gra output.gr \n";
    std::cout << "Pruebe ./p07-Grammar2CNF --help para mas informacion\n";
    return 0;
  }
  std::string input_gra = argv[1];
  std::string output_gra = argv[2];
  std::ifstream input(input_gra);
  if (!input.is_open()) {     // comprobar si el archivo se pudo abrir
    std::cout << "Error: no se pudo abrir el archivo " << input_gra << "\n";
    return 0;
  }
  char terminal, no_terminal;
  std::set<char> elementos_gr;
  int nterminales;
  input >> nterminales;
  for(int i = 0; i < nterminales; ++i) {
    input >> terminal;
    int terminal_ = int(terminal);
    elementos_gr.insert(terminal);
  }
  Alfabeto alfabeto_gr(elementos_gr);
  int n_no_terminales;
  input >> n_no_terminales;
  std::set<char> no_terminales;
  for(int i = 0; i < n_no_terminales; ++i) {
    input >> no_terminal;
    int no_terminal_ = int(no_terminal);
    if(no_terminal_ < 65 || no_terminal_ > 90) {
      std::cout << "A especificado un terminal como no terminal. Error\n";
      return 0;
    }
    no_terminales.insert(no_terminal);
  }
  Gramatica gramatica_1(no_terminales, alfabeto_gr);
  
}