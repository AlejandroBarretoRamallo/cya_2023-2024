#include "Alfabeto.h"

/**
 * @brief constructor
 * @param caracteres_ conjunto de caracteres
*/

Alfabeto::Alfabeto(std::set<char> caracteres_){
  caracteres = caracteres_;
}

/**
 * @brief devuelve el alfabeto
 * @return El alfabeto
*/

std::set<char> Alfabeto::GetSet() {
  return caracteres;
}

/**
 * @brief Elimina el alfabeto
*/

void Alfabeto::RemoveSet() {
  std::set<char> set = caracteres;
  for (auto& carcater : set) {
    caracteres.erase(carcater);
  }
}

/**
 * @brief Aañade simbolos al alfabeto
 * @param simbolo Simbolo nuevo del alfabeto
*/

void Alfabeto::Push(char simbolo) {
  caracteres.insert(simbolo);
}

/**
 * @brief Muestra por pantalla el alfabeto
 * @param out El operador <<
 * @param a Un alfabeto
*/

std::ostream& operator<<(std::ostream& out, Alfabeto& a) {
	out << "{";
  auto iterador = a.GetSet().rbegin();  // puntero al final del set
	for (auto i : a.GetSet()) {  // bucle para imprimir el set
		if (*iterador == i) {
			out << i;
			continue;
		}
		out << i << ", ";
	}
	out << "}" << std::endl;
  return out;
}

/**
 * @brief constructor sin arametros
*/

Alfabeto::Alfabeto() {
  std::set<char> caracteres_;
  caracteres = caracteres_;
}