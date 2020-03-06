#include "../jsonv350.hpp"
using namespace std;
// Lectura de Archivo.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <vector>
#include <fstream>
using json = nlohmann::json;
#include <iostream>

int main()
{
	fstream stream("entities.json");

	struct Componente
	{
		string id;
	};

	struct transform:Componente
	{
		int posicion[3];
		int escala[3];
		int rotacion[3];
	};

	struct physic :Componente
	{
		bool collision;
		int escala[3];
	};


	struct Entity
	{
		string id;
		vector<Componente*> c;

	};


	json file;
	stream >> file;
	file = file.at("Entities");

	int size = file.size();

	for(int i = 0; i < size; i++){
		Entity e;
		e.id = file[i].at["id"].get<string>();
		for (int j = 0; j < size; j++) {
			string tipo = (file[i].at["components"][j].at["id"].get<string>());
			if ("physic") physic c;
			break;
			}
			e.c.push_back(comp);

		}
	}
	//cout << j["Entities"]["id"];
}

