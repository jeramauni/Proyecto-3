#pragma once

#include "json.hpp"
#include "EntityC.h"
#include <vector>
using json = nlohmann::json;

// Componentes
#include "ComponentFactory.h"

class DataManager {
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
	std::vector<EntityC*> ProcessMap(std::vector<std::vector<std::string>> map, json prefabs);
	EntityC* CreateEntity(std::string id, json prefabs, uint32_t n_entities);
};