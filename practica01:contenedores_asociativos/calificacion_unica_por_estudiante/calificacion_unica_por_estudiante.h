#pragma once
#include <map>
#include <utility>
#include <map>
#include <iostream>

class alumnado {
  public:
    alumnado(std::map <std::string, float> _claves);   //constructor
    std::map <std::string, float> get_map();        //getter
    void set_map(std::string nombre, float nota);      //setter
    void read_map();
    void add_data();
  private:
    std::map <std::string, float> claves;
};