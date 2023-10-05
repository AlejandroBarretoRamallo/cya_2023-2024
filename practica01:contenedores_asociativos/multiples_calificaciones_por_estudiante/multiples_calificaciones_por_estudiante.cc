#include "multiples_calificaciones_por_estudiante.h"
#include <iostream>
#include <vector>

alumnado::alumnado(std::map <std::string, std::vector<float>> claves_) {
  claves = claves_;
  return;
}

std::map <std::string, std::vector<float>> alumnado::get_map() {
  return claves;
}

void alumnado::set_map(std::string nombre, float notas) {
  std::vector<float> notas_ = claves[nombre];
  notas_.push_back(notas);
  claves[nombre] = notas_;
  return;
}

void alumnado::read_map(){
  for(auto i = claves.begin(); i != claves.end(); ++i) {
    std::cout << (*i).first << ": ";
    float minimo = (*i).second.at(0);
    float maximo = (*i).second.at(0);
    for(int j = 0; j < (*i).second.size(); ++j) {
      if((*i).second.at(j) < minimo) {
        minimo =(*i).second.at(j);
      }
      if((*i).second.at(j) > maximo) {
        maximo = (*i).second.at(j);
      }
      std::cout << (*i).second.at(j) << " ";
    }
    std::cout << "------[" << minimo << ", " << maximo << "]" << std::endl;
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
    set_map(nombre, nota);
    std::cout << "¿Desea añadir algun elemento? 1(si) o 0(no)" << std::endl;
    std::cin >> add;
 }
}

