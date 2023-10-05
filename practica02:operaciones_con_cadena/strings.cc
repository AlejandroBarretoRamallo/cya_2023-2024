#include "strings.h"


alfabeto::alfabeto(std::set<char> caracteres_){
  caracteres = caracteres_;
}

std::set<char> alfabeto::get_set() {
  return caracteres;
}

void alfabeto::set_set(std::set<char> set) {
  caracteres = set;
}

void alfabeto::remove_set() {
  std::set<char> set = caracteres;
  for(auto& carcater : set) {
    caracteres.erase(carcater);
  }
}

void alfabeto::print_alfabeto(std::string salida, std::string entrada) {
	std::string cadena;
	std::ifstream archivo_entrada(entrada);
	if(!archivo_entrada.is_open()) {    // comprobar que el archivo se abrió correctamente
		std::cout << "No se puedo abrir el archivo" << std::endl;
		return;
	}
	std::ofstream archivo_salida(salida);
	while(getline(archivo_entrada, cadena)) {	   //obtener las cadenas del archivo
		for(auto i : cadena) {
			caracteres.insert(i);                  // añadir los caracteres al set
		}
		alfabeto set(get_set());
		archivo_salida << set;
		remove_set();  // vaciar el set
	}
}

void alfabeto::longitud_cadena(std::string salida, std::string entrada) {
	std::ifstream archivo_entrada(entrada);
	if(!archivo_entrada.is_open()) {  // comprobar que se abre correctamente el archivo
		std::cout << "No se puedo abrir el archivo" << std::endl;
		return;
	}
	std::string cadena;
	std::ofstream archivo_salida(salida);
	while(getline(archivo_entrada, cadena)) {	   // leer las cadenas del archivo
		int longitud = cadena.length();
		archivo_salida << longitud << std::endl;
	}
}

void alfabeto::inversa(std::string salida, std::string entrada) {
  std::string cadena;
  std::ifstream archivo_entrada(entrada);
  if(!archivo_entrada.is_open()) {   // comprobar que se abrio correctamente el archivo
    std::cout << "No se puedo abrir el archivo" << std::endl;
    return;
  }
  std::ofstream archivo_salida(salida);
  while(getline(archivo_entrada, cadena)) {   // leer las cadenas del archivo
		for(int i = cadena.length()-1; i >= 0; --i) {   //bucle para imprimir la cadena al reves
      archivo_salida << cadena[i];
		}
		archivo_salida << std::endl;
  }
}

void alfabeto::prefijos(std::string salida, std::string entrada) {
  std::ifstream archivo_entrada(entrada);
  std::ofstream archivo_salida(salida);
  if(!archivo_entrada.is_open()) {  // comprobar que se abrio correctamente el archivo
    std::cout << "No se a podido abrir el archivo" << std::endl;
    return;
  }
  std::string cadena;
  while(getline(archivo_entrada, cadena)) {   // leer cadenas del archivo
		archivo_salida << "{&, ";
		int contador = 0;
		for(int i = 0; i < cadena.length();++i) { //bucle para leer varias veces la cadena
			for(int j = 0; j <= contador; ++j) {   //bucle para imprimir la cadena
				archivo_salida << cadena[j];
				if(j == contador && contador + 1 != cadena.length()) {   // condicion para saber si es el ultimo elemento
					archivo_salida << ", ";
				}
			}
      ++contador;
		}
		archivo_salida << "}" << std::endl;
	}
}

void alfabeto::sufijos(std::string salida, std::string entrada) {
  std::ifstream archivo_entrada(entrada);
  std::ofstream archivo_salida(salida);
  if(!archivo_entrada.is_open()) {  // comprobar que el archivo se abrio correctamente
    std::cout << "No se a podido abrir el archivo" << std::endl;
    return;
  }
  std::string cadena;
  while(getline(archivo_entrada, cadena)) {  // leer cadenas del archivo
		archivo_salida << "{&, ";
		const int longitud = cadena.length();
		for(int i = 0; i < longitud; ++i) { // bucle para leer varias veces la cadena
			int contador = i;
			for(int j = longitud -1; j - contador < longitud; --contador) { // imprimir la cadena
				if((j - contador != longitud -1) || (j - contador == longitud -1 && i == longitud - 1)) { // detectar final de cadena
					archivo_salida << cadena[j - contador];
				}
				else {
					archivo_salida << cadena[j - contador] << ", ";
				}

			}
		}
		archivo_salida << "}" << std::endl;
	}
}

std::ostream& operator<<(std::ostream& out, alfabeto& a) {
	out << "{";
  auto iterador = a.get_set().rbegin();  // puntero al final del set
	for(auto i : a.get_set()) {  // bucle para imprimir el set
		if(*iterador == i) {
			out << i;
			continue;
		}
		out << i << ", ";
	}
	out << "}" << std::endl;
  return out;
}

void alfabeto::concatenar(std::string salida, std::string entrada) {
	std::cout << "Indique la cadena a concatenar: ";
	std::string cadena_;
	std::cin >> cadena_;
	std::ifstream archivo_entrada(entrada);
  	std::ofstream archivo_salida(salida);
  	if(!archivo_entrada.is_open()) {  // comprobar que el archivo se abrio correctamente
   		std::cout << "No se a podido abrir el archivo" << std::endl;
    	return;
  	}	
  	std::string cadena;
  	while(getline(archivo_entrada,cadena)) {
		for(int i = 0; i < cadena.length(); ++i) {
			archivo_salida << cadena[i];
		}
		if(cadena_ != "&") {
			for(int i = 0; i < cadena_.length(); ++i) {
				archivo_salida << cadena_[i];
			}
		}
		archivo_salida << std::endl;
	}
}
