#include "../jsonv350.hpp"
using namespace std;
// Lectura de Archivo.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <vector>
#include <fstream>
using json = nlohmann::json;
#include <iostream>
#include <fstream>

int main()
{
	fstream streamE("entities.json");
	fstream streamM("map.json");

	//stream.close();

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

	//struct physic :Componente
	//{
	//	bool collision;
	//	int escala[3];
	//};


	struct Entity
	{
		string id;
		vector<Componente*> c;

	};


	json entitiesFile;
	json mapFile;


	streamE >> entitiesFile;
	streamM >> mapFile;

	//file.dump(stream);
	entitiesFile = entitiesFile.at("Entities");
	mapFile = mapFile.at("Map");

	int sizeE = entitiesFile.size();
	int sizeM = mapFile.size();


	for (int i = 0; i < sizeM; i++) {		// recorre el mapa de entidades
		string id = mapFile[i].at["id"].get<string>();
		string nombre = mapFile[i].at["nombre"].get<string>();

		json entidad = entitiesFile[id];
		json components = mapFile[i].at["components"];

		for (int j = 0; j < components.size(); j++) {		//recorre los componentes
			string tipo = components[j].at["id"];
			entidad[tipo] = components[j];
			//crear un componente y pasarle los parámetros tipo json
		}

		entidad["nombre"] = nombre;

		//entidad ya tiene los componentes actualizados y un nuevo campo para el nombre

		

	}


	//for(int i = 0; i < size; i++){
	//	Entity e;
	//	//e.id = file[i].at["id"].get<string>();
	//	for (int j = 0; j < size; j++) {
	//		//string tipo = (file[i].at["components"][j].at["id"].get<string>());
	//		
	//		//e.c.push_back(comp);

	//	}
	//}
	//cout << j["Entities"]["id"];
}

