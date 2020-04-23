#pragma once

#include "json.hpp"

using json = nlohmann::json;

class WEManager;
class Container;

class DataManager {
public:

	//Main loader
	std::vector<Container*> Load(const std::string& map_file, const std::string& prefabs_file);
	void setWEM(WEManager* wem);

private:

	//Readers
	json ReadJson(const std::string& file_name);
	std::vector<std::vector<std::string>> ReadMap(const std::string& file_name);

	//Debugs
	void DebugJson(json json_file);
	void DebugMap(std::vector<std::vector<std::string>> map, bool output_debugTxt);

	//Auxiliares
	bool ReadNext(std::ifstream& input);
	std::vector<std::string> GetWords(std::string& s);
	std::vector<Container*> ProcessMap(std::vector<std::vector<std::string>> map, json prefabs);
	Container* CreateEntity(std::string id, json prefabs, uint32_t n_entities);

	// Puntero al motor
	WEManager* _weM;
};