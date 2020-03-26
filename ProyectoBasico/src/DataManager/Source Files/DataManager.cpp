// DataManager.cpp : Define las funciones de la biblioteca estática.

#include "DataManager.h"
#include <iostream>
#include <fstream>

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