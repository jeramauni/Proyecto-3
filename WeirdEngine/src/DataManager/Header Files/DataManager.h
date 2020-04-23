#pragma once

#include "json.hpp"

using json = nlohmann::json;

class EntityC;

class DataManager {
public:

	//Main loader
	std::vector<EntityC*> Load(const std::string& map_file, const std::string& prefabs_file, bool debug_mode);

private:

	bool debug_ = true;

	//Readers
	json ReadJson(const std::string& file_name);
	std::vector<std::vector<std::string>> ReadMap(const std::string& file_name);

	//Debugs
	void DebugJson(json json_file);
	void DebugMap(std::vector<std::vector<std::string>> map, bool output_debugTxt);

	//Auxiliares
	bool ReadNext(std::ifstream& input);
	std::vector<std::string> GetWords(std::string& s);
	std::vector<EntityC*> ProcessMap(std::vector<std::vector<std::string>> map, json prefabs, bool debug);
	EntityC* CreateEntity(std::string& id, json prefabs, uint32_t n_entities);
};