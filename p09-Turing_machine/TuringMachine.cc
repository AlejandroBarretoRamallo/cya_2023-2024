#include "TuringMachine.h"
#include <fstream>

/**
 * @brief Constructor que lee un fichero con una maquina de turing especificada
 * @param archivo_entrada El nombre del fichero
*/

TuringMachine::TuringMachine(std::string archivo_entrada) {
  std::ifstream input(archivo_entrada); // abrir fichero de entrada
  if (!input.is_open()) {
    std::cout << "No se pudo abrir el archivo\n";
    FileOpened = 0;
    return;
  }
  FileOpened = 1;
  input >> NumEstados;
  input >> EstadoArranque;
  if (EstadoArranque > NumEstados - 1) {  // comprobar si el estado de arranque es correcto
    std::cout << "Error: el estado de arranque no existe \n";
    FileOpened = 0;
    return;
  }
  std::string cadena;
  getline(input, cadena);
  getline(input, cadena);
  for (int i = 0; i < cadena.size(); ++i) { // leer estados finales
    if (cadena[i] - 48 > NumEstados - 1) {
      std::cout << "Error: el estado de aceptacion " << i << " no existe \n";
      FileOpened = 0;
      return;
    }
    EstadosFinales.insert(cadena[i] - 48);
    ++i;
  }
  int NumTuplas;
  input >> NumTuplas;
  int actual_state, estado_siguiente;
  char read_simbol, write_simbol, move;
  for (int i = 0; i < NumTuplas; ++i) {  // leer todas las tuplas
    input >> actual_state >> read_simbol  >> write_simbol >> move >> estado_siguiente;
    Tupla tupla(actual_state, estado_siguiente, read_simbol, write_simbol, move); // construir una tupla por cada liena
    Tuplas.push_back(tupla);  // añadir la tupla al conjunto de tuplas
    AlfabetoCinta.Push(read_simbol);  // añadir los simbolos que puede leer al alfabeto 
  }
  EstadoActual = EstadoArranque;
  CabezaLectura = 1;
  IsStopped = 0;
}

/**
 * @brief Comprueba si dada una cinta y una cadena, la cadena pertenece al lenguaje
 * @brief reconocido por la maquina de turing
 * @param cadena Cadena a comprobar
 * @param cinta La cinta con la cadena y los blancos
 * @return Si la cadena pertenece o no
*/

bool TuringMachine::ReadString(std::string cinta) {
  int posicion_tupla = FindTupla(EstadoActual, cinta[CabezaLectura]);
  while (!IsStopped) {
    posicion_tupla = FindTupla(EstadoActual, cinta[CabezaLectura]);
    if (posicion_tupla == -1) { // findtupla devuelve menos 1 si no se ha encontrado
      IsStopped = true;
      continue;
    }
    Tupla tupla = Tuplas[posicion_tupla];
    // guardar los valores de la tupla
    char read_simbol = tupla.GetReadSimbol();  
    char write_simbol = tupla.GetWriteSimbol();  
    char move = tupla.GetMove();  
    int estado_siguiente = tupla.GetEstadoSiguiente(); 
    bool Read = read_simbol == write_simbol ? true : false; // comprobar si solo se lee o si tambien se escribe
    if (!Read) {
      cinta[CabezaLectura] = write_simbol; // sobreescribir el simbolo
      if (read_simbol == '$') { // comprobamos si el blanco que hay que añadir esta a la izquierda o a la derecha
        if (CabezaLectura != 0) {
          cinta += '$';  // añadir blanco al final
        }
        if (CabezaLectura == 0) {  // añadir blanco al principio
          std::string cadena = "$";
          cadena += cinta;
          cinta = cadena; 
          ++CabezaLectura; // como añadimos por la izquierda el indice incrementa en 1
        }
      }
    }
    switch (move) { // mover a izquierda o derecha la cabeza de lectura
      case 'L':
        --CabezaLectura;
        break;
      case 'R':
        ++CabezaLectura;      
        break;
      case 'S':
        break;
    }
    EstadoActual = estado_siguiente;
  }
  return Acepted(EstadoActual); // acepted compruba si el estado es de aceptracion o no
}

/**
 * @brief Comprueba si el estado es de aceptacion
 * @param Estado_final El estado en el que se paro la maquina
 * @return Si el estado es de aceptacion o no
*/

bool TuringMachine::Acepted(int Estado_final) {
  for (int estado : EstadosFinales) { // ver si el estado es de aceptacion
    if (estado == Estado_final) {
      return true;
    }
  }
  return false;
}

/**
 * @brief Busca si hay alguna transicion definida para el estado actual y el simbolo que se lee
 * @param actual_state Estado en el que se encuentra la maquina
 * @param elemento Caracter que lee la maquina
 * @return -1 si no se ha encontrado, en cualquier otro caso devuelve su posicion en el vector
*/

int TuringMachine::FindTupla(int actual_state, char elemento) {
  for (int i = 0; i < Tuplas.size(); ++i) {
    if (Tuplas[i].GetEstadoActual() == actual_state && Tuplas[i].GetReadSimbol() == elemento) {
      return i;
    }
  }
  return -1;
}

/**
 * @brief Getter
 * @return Si se pudo abrir el archivo o no
*/

bool TuringMachine::GetFileOpened() {
  return FileOpened;
}

/**
 * @brief Imprime los datos de la maquina de turing
*/

void TuringMachine::PrintMachine() {
  std::cout << NumEstados << "\n" << EstadoArranque << "\n"; // imprimir numero de estados y estado de arranque
  for (int estado_aceptacion : EstadosFinales) {  // imprimir estados de aceptacion
    std::cout << estado_aceptacion << " ";
  }
  std::cout << "\n" << Tuplas.size() << "\n";
  for (int i = 0; i < Tuplas.size(); ++i) {
    std::cout << Tuplas[i].GetEstadoActual() << " " << Tuplas[i].GetReadSimbol() << " " << Tuplas[i].GetWriteSimbol() << " ";
    std::cout << Tuplas[i].GetMove() << " " << Tuplas[i].GetEstadoSiguiente() << "\n";
  }
}