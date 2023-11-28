#include "point_set.hpp"
#include "point_types.hpp"
#include "sub_tree.hpp"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Error, no se ha ntroducido el nombre del fichero\n";
    return 0;
  }
  std::string nombre_fichero = argv[1];
  std::ifstream input(nombre_fichero);
}