#include "Alfabeto_copy.h"


Alfabeto::Alfabeto(std::set<char> caracteres_){
  caracteres = caracteres_;
}

std::set<char> Alfabeto::GetSet() {
  return caracteres;
}

void Alfabeto::SetSet(std::set<char> set) {
  caracteres = set;
}

void Alfabeto::RemoveSet() {
  std::set<char> set = caracteres;
  for (auto& carcater : set) {
    caracteres.erase(carcater);
  }
}

void Alfabeto::Push(char simbolo) {
  caracteres.insert(simbolo);
}

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