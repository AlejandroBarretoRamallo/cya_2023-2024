#include <iostream>
#include "Alfabeto.h"
#include <fstream>
#include "Gramatica.h"
#include <map>

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
  char terminal, no_terminal, simbolo_arranque;
  std::set<char> elementos_gr;
  int nterminales;
  input >> nterminales;
  for(int i = 0; i < nterminales; ++i) {  // leemos el alfabeto de la gramatica
    input >> terminal;
    elementos_gr.insert(terminal);
  }
  Alfabeto alfabeto_gr(elementos_gr);  //c creamos alfabeto con sus correspondientes simbolos
  int n_no_terminales;
  input >> n_no_terminales;
  input >> simbolo_arranque;
  n_no_terminales -= 1;
  std::set<char> no_terminales;
  for(int i = 0; i < n_no_terminales; ++i) {    // leemos todos los no terminales
    input >> no_terminal;
    int no_terminal_ = int(no_terminal);
    if(no_terminal_ < 65 || no_terminal_ > 90) {   // nos aseguramos de que sean no terminales(mayuscula)
      std::cout << "A especificado un terminal como no terminal. Error\n";
      return 0;
    }
    no_terminales.insert(no_terminal);
  }
  typedef std::multimap<char, std::string> produccion;   // cada no terminal contiene claves con todas sus produccciones
  produccion produccion_a;   
  int num_producciones;
  input >> num_producciones;
  char simbolo;
  std::string produccion_;
  for(int i = 0; i < num_producciones; ++i) { 
    input >> simbolo >> produccion_;
    produccion_a.emplace(simbolo, produccion_);  // añadimos a cada no termianl sus producciones
  }
  Gramatica gramatica_1(no_terminales, alfabeto_gr, simbolo_arranque, produccion_a);  // creamos la gramatica
  if(gramatica_1.ComprobarProduccionesVacias()) {
    std::cout << "Error. Se han introducido producciones vacias\n";
    return 0;
  }
  if(gramatica_1.ComprobarProduccionesUnitarias()) {
    std::cout << "Error. Se han introducido producciones unitarias\n";
    return 0;
  }
  std::cout << gramatica_1;
  gramatica_1.TransformarCNF();
  std::cout << gramatica_1;
  std::ofstream output(output_gra);
}