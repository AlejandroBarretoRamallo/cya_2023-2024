#include <iostream>

class Tupla {
  public:
    Tupla(int estado_actual, int estado_siguiente, char read_simbol, char write_simbol, char move);
  private:
    int estado_actual_;
    int estado_siguiente_;
    char read_simbol_;
    char write_simbol_;
    char move_;;
};