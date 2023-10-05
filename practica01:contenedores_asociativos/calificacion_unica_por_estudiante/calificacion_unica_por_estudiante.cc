#include "calificacion_unica_por_estudiante.h"
#include <iostream>
#include <utility>
#include <map>
#include <string>

alumnado::alumnado(std::map <std::string, float> claves_) {  //constructor
    claves = claves_;
    return;
}

std::map <std::string, float> alumnado::get_map() {  //getter
    return claves;
}

void alumnado::set_map(std::string nombre, float nota) { //setter
    claves[nombre] = nota;
    return;
}

void alumnado::read_map() {
    for(auto i = claves.begin(); i != claves.end(); ++i) {  //recorre la variable y muestra por pantalla los pares
    std::cout << (*i).first << ": " << (*i).second << std::endl;
  }
}

void alumnado::add_data() {
  bool add;
  std::cout << "¿Desea añadir algun elemento? 1(si) o 0(no)" << std::endl; 
  std::cin >> add;
  while(add) {
    std::cout << "Indique el alu y la nota: " << std::endl;
    std::string nombre;
    float nota;
    std::cin >> nombre >> nota;
    if(get_map()[nombre] > nota) {  // comprobar si la nota es mayor que la ya asignada o no
      continue;
    }
    set_map(nombre, nota);
    std::cout << "¿Desea añadir algun elemento? 1(si) o 0(no)" << std::endl;
    std::cin >> add;
  }
}