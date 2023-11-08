#include "Tupla.h"

/**
 * @brief Constructor
 * @param estado_actual Estado de la maquina
 * @param estado_siguiente Estado al que va a ir la maquina
 * @param read_simbol Simbolo que lee
 * @param write_simbol Simbolo que se escribe
 * @param move A que lado se mueve la maquina
*/

Tupla::Tupla(int estado_actual, int estado_siguiente, char read_simbol, char write_simbol, char move) {
  estado_actual_ = estado_actual;
  estado_siguiente_ = estado_siguiente;
  read_simbol_ = read_simbol;
  write_simbol_ = write_simbol;
  move_ = move;
}