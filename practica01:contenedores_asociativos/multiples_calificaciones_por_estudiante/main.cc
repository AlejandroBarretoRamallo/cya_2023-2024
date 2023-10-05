// Universidad de La Laguna
// Escuela Superior de Ingenierıa y Tecnologıa
// Grado en Ingenierıa Inform´atica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Practica 1: Contenedores asociativos
// Autor: Jose Alejandro Barreto Ramallo
// Correo: alu0101552774@ull.edu.es
// Fecha: 14/09/2023
// Archivo main.cc
// Contiene la funci´on main del proyecto que lee un
// archivo de texto que contiene pares e claves y notas,
// para luego imprimir por pantalla cada clave con una o mas notas
// Referencias:
// Enlaces de interes:
// Historial de revisiones
// 12/09/2023 - Creacion (primera version) del codigo
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <map>
#include "multiples_calificaciones_por_estudiante.h"

int main(int argc, char *argv[]) {
	if(argc < 2) {
		std::cout << "Error. Se debe especificar el nombre de un archivo de texto en el comando." << std::endl;
		return 0;
	}
	std::string nombre_fichero = argv[1];
	std::ifstream archivo(nombre_fichero);
	std::map <std::string, std::vector<float>> claves_;
	alumnado alumnos(claves_);
	std::string nombre;
	float nota;
	while(!archivo.eof()) {
		archivo >> nombre >> nota;
		alumnos.set_map(nombre, nota);	
	}
	alumnos.read_map();
	alumnos.add_data();
	alumnos.read_map();
	return 0;
}