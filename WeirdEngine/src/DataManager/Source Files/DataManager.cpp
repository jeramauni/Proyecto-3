// DataManager.cpp : Define las funciones de la biblioteca estática.
// BE AWARE! Los archivos de mapas y prefabs deben guardarse en el directorio resources del directorio exes del proyecto.
#include "DataManager.h"
#include <iostream>
#include <fstream>

DataManager::DataManager() {
	//rComp = _rF->Create();
	//iComp = _iF->Create();
	tComp = _tF->Create();
}

//Reads a .json file ande parses it to a json class instance
json DataManager::ReadJson(const std::string& file_name)
{
	json j;
	std::ifstream input;

	input.open(file_name);

	input >> j;
	input.close();

	return j;
}

//Outputs on console a readable debug of a json file
void DataManager::Debug(json json_file)
{
	int file_type = 0;
	if (json_file.begin().key() == "Map") { file_type = 1; }

	std::cout << "Debugging " << json_file.begin().key() << " file... " << '\n' << '\n';
	json_file = json_file.at(json_file.begin().key());

	//For each object in the file...
	for (size_t i = 0; i < json_file.size(); i++)
	{
		std::cout << "----------------------" << '\n';
		if (file_type) { std::cout << "id:     " << json_file[i].at("name") << '\n'; }	//Entity id (if map file)
		std::cout << "Entity: " << json_file[i].at("id") << '\n';						//Entity type

		std::cout << "Components :" << '\n';
		//For each element  in the object...
		if (!json_file[i].at("components").size())
		{
			std::cout << "\"None\"" << '\n';
		}
		else
		{
			//For each  component in components[]...
			for (size_t j = 0; j < json_file[i].at("components").size(); j++)
			{
				if (!file_type) { std::cout << '*' << json_file[i].at("components")[j].at("id") << '*' << '\n'; }	//Component type
				std::cout << json_file[i].at("components")[j] << '\n';								//Component description
			}
		}

		std::cout << "----------------------" << '\n';
	}
}


std::vector<EntityC*> DataManager::LoadSceneEntities(const std::string& entities_file) {
	//Vector de entidades del mapa
	std::vector<EntityC*> entities;
	bool fail = false;
	json ent;
	//Lectura y carga del archivo mapa ----------------------------------------
	try {
		ent = ReadJson(entities_file);
	}
	catch (const std::exception & e) {
		std::cerr << "Couldn't load the map file: \"" << entities_file << "\" \n" << e.what();
		fail = true;
	}

	ent = ent.at(ent.begin().key());

	//For each object in the file...
	for (size_t i = 0; i < ent.size(); i++)
	{
		//Entity type
		EntityC* e = new EntityC(ent[i].at("id"));

		//For each element  in the object...
		if (!ent[i].at("components").size())
		{
			std::cout << "\"None\"" << '\n';
		}
		else
		{
			//For each  component in components[]...
			for (size_t j = 0; j < ent[i].at("components").size(); j++)
			{
				//Componente de input
				if(ent[i].at("components")[j].at("id") == "input") {
					//iComp->Init(e);
				}
				// Componente transform
				else if (ent[i].at("components")[j].at("id") == "transform") {
					std::vector<int> p = ent[i].at("components")[j].at("posicion");
					Ogre::Vector3 pos = Ogre::Vector3(p[0], p[1], p[2]);
					std::vector<int> es = ent[i].at("components")[j].at("escala");
					Ogre::Vector3 esc = Ogre::Vector3(es[0], es[1], es[2]);
					std::vector<int> r = ent[i].at("components")[j].at("rotacion");
					Ogre::Vector3 rot = Ogre::Vector3(r[0], r[1], r[2]);
					tComp->Init(pos, esc, rot);
					e->AddComponent(tComp);
				}
				//std::cout << ent[i].at("components")[j] << '\n';								//Component description
			}
		}

		std::cout << "----------------------" << '\n';
		entities.push_back(e);
	}
	

	return entities;
}

std::vector<EntityC*> DataManager::Load(const std::string& map_file, const std::string& prefabs_file)
{
	//Vector de entidades del mapa
	std::vector<EntityC*> entities;
	json map;		//Map data
	json prefabs;	//Prefabs data

	//Error fuse
	bool fail = false;

	std::cout << "Game Data loading initiated... \n";

	//Lectura y carga del archivo mapa ----------------------------------------
	try	{
		map = ReadJson(map_file);
	}
	catch (const std::exception& e) {
		std::cerr << "Couldn't load the map file: \"" << map_file << "\" \n" << e.what();
		fail = true;
	}
	//-------------------------------------------------------------------------

	if (!fail) {		
		//Lectura y carga del archivo de prefabs ----------------------------------
		try	{
			prefabs = ReadJson(prefabs_file);
		}
		catch (const std::exception& e)	{
			std::cerr << "Couldn't load the prefabs file: \"" << prefabs_file << "\" \n" << e.what();
			fail = true;
		}
		//-------------------------------------------------------------------------
		if (!fail) {
			//----------------------------PLACEHOLDER----------------------------------
			Debug(map);
			Debug(prefabs);

			//-------------------------------------------------------------------------
			if (!fail)
			{
				std::cout << "Game Data loading finished successfully! \n";
			}
		}
	}
	return entities;
}