// Universidad de La Laguna
// Escuela Superior de Ingenierıa y Tecnolog´ıa
// Grado en Ingenierıa Informatica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Practica 1: Contenedores asociativos
// Autor: Nombre y Apellidos
// Correo: alu0101552774@ull.edu.es
// Fecha: 20/09/2023
// Archivo main.cc: programa cliente.
// Contiene la funcion main del proyecto que usa las clases X e Y
// para realizar multiples operaciones con cadenas
// Referencias:
// Enlaces de interes
// Historial de revisiones
// 12/09/2023 - Creacion (primera versi´on) del codigo

#include "strings.h"


int main(int argc, char* argv[]) {
  if(argc != 2 && argc != 4) {
		std::cout << "Se deben indicar tres parametros." << std::endl;
		std::cout << "Para saber como usar el programa utilice --help" << std::endl;
		return 0;
	}
	std::string entrada = argv[1];
	if(entrada == "--help") {
		std::cout << "Se debe introcir el fichero de entrada, el fichero de salida, y la opcion, que ";
		std::cout << "puede ser 1,2,3,4 o 5" << std::endl;
		std::cout << "Opcion 1 : escribir en el fichero de salida el alfabeto asociado a cada una de las cadenas de entrada. " << std::endl;
		std::cout << "Opcion 2 : escribir en el fichero de salida la longitud de cada cadena de entrada." << std::endl;
		std::cout << "Opcion 3 : escribir en el fichero de salida la inversa de cada cadena de entrada." << std::endl;
		std::cout << "Opcion 4 : escribir en el fichero de salida el conjunto de cadenas que son prefijos de la cadena de entrada correspondiente" << std::endl;
		std::cout << "Opcion 5 : escribir en el fichero de salida el conjunto de cadenas que son sufijos de cada cadena de entrada correspondiente " << std::endl;
		std::cout << "Opcion 6: pedir una cadna y concatenarla con el resto de cadenas del fichero " << std::endl;
		return 0;
	}
	std::string salida = argv[2];
	std::string opcion = argv[3];
	char opcion_ = opcion[0];
	std::set<char> caracteres_;
	alfabeto alfabeto_(caracteres_);
	switch (opcion_)
	{
	case '1':
		alfabeto_.print_alfabeto(salida, entrada);   // imprimir el afabeto
		break;
	case '2':
	alfabeto_.longitud_cadena(salida, entrada);   // imprimir la longitud
		break;
	case '3':
	alfabeto_.inversa(salida,entrada);    // imprimir la inversa
		break;
	case '4':alfabeto_.prefijos(salida, entrada);   // imprimir prefijos
		break;
	case '5':
		alfabeto_.sufijos(salida, entrada);  // imprimir sufijos
		break;
	case '6':
		alfabeto_.concatenar(salida,entrada);
		break;
	default:
		std::cout << "No se ha introducido una opcion valida" << std::endl;
		std::cout << "Para ver las distintas opciones use --help" << std::endl;
		break;
	}
	return 0;
}