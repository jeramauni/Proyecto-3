#pragma once

#include "json.hpp"
#include "EntityC.h"
#include <vector>
using json = nlohmann::json;

class DataManager 
{
public:

	std::vector<EntityC*> Load(const std::string& map_file, const std::string& prefabs_file);

private:

	json ReadJson(const std::string& file_name);
	std::vector<std::vector<std::string>> ReadMap(const std::string& file_name);
	//Auxiliares
	void DebugJson(json json_file);
	void DebugMap(std::vector<std::vector<std::string>> map, bool output_debugTxt);
	bool ReadNext(std::ifstream& input);
	std::vector<std::string> GetWords(std::string& s);
};