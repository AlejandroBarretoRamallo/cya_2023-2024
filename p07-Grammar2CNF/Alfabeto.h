#pragma once
#include <iostream>
#include <set>
#include <string>

class Alfabeto {
  public:
    Alfabeto(std::set<char> caracteres_);                   //@brief Constructor de la clase
                                                            //@Param Set de char para representar el alfabeto
                                                            //@Return No devuelve nada
    
    Alfabeto();

    std::set<char> GetSet();                                //@brief Funcion que devuelve los caracteres del alfabeto
                                                            //@Param no hay parametros
                                                            //@Return Devuelve el atributo caracteres, un set de tipo char

    void GetSet(std::set<char> set);                        //@brief Funcion para asignar un set a caracteres
                                                            //@Param Set de tipo char que representa un alfabeto
                                                            //@Return No devuelve nada

    void RemoveSet();                                       //@brief Funcion para vaciar caracteres
                                                            //@Param No hay parametros
                                                            //@Return No devuelve nada

    void Push(char);                                        //@brief Funcion para añadir siimbolos a caracteres
                                                            //@Param Elemento que sera añadido a caracteres y que pertenece al alfabeto
                                                            //@Return No devuelve nada

  private:
  std::set<char> caracteres;
};

std::ostream& operator<<(std::ostream& out, Alfabeto& a);   // sobrecarga del operador <<