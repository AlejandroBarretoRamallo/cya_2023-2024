#pragma once
#include <map>
#include <vector>

class alumnado{
  public:
    alumnado(std::map <std::string, std::vector<float>> claves_);  //constructor
		std::map <std::string, std::vector<float>> get_map();          //getter
		void set_map(std::string nombre, float notas);                 //setter
		void read_map();
		void add_data();
	private:
		std::map <std::string, std::vector<float>> claves;
};