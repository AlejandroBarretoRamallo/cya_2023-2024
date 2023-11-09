#include "Tupla.h"

/**
 * @brief Constructor
 * @param EstadoActual Estado de la maquina
 * @param EstadoSiguiente Estado al que va a ir la maquina
 * @param ReadSimbol Simbolo que lee
 * @param WriteSimbol Simbolo que se escribe
 * @param Move A que lado se mueve la maquina
*/

Tupla::Tupla(int EstadoActual, int EstadoSiguiente, char ReadSimbol, char WriteSimbol, char Move) {
  EstadoActual_ = EstadoActual;
  EstadoSiguiente_ = EstadoSiguiente;
  ReadSimbol_ = ReadSimbol;
  WriteSimbol_ = WriteSimbol;
  Move_ = Move;
}

/**
 * @brief getter
 * @return Estado actual
*/

int Tupla::GetEstadoActual() {
  return EstadoActual_;
}

/**
 * @brief getter
 * @return Estado siguiente
*/

int Tupla::GetEstadoSiguiente() {
  return EstadoSiguiente_;
}

/**
 * @brief getter
 * @return Simbolo que lee
*/

char Tupla::GetReadSimbol() {
  return ReadSimbol_;
}

/**
 * @brief getter
 * @return A que lado se mueve
*/

char Tupla::GetMove() {
  return Move_;
}

/**
 * @brief getter
 * @return Simbolo que lee
*/

char Tupla::GetWriteSimbol() {
  return WriteSimbol_;
}