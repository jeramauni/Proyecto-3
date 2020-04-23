#pragma once

#include "json.hpp"
#include <OgreVector3.h>

using json = nlohmann::json;

class WEManager;
class Container;
class Vector3;

class DataManager {
public:

	//Main loader
	std::vector<Container*> Load(const std::string& map_file, const std::string& prefabs_file, bool debug_mode);
	void setWEM(WEManager* wem);

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
	std::vector<Container*> ProcessMap(std::vector<std::vector<std::string>> map, json prefabs, bool debug);
	Container* CreateEntity(std::string& id, json prefabs, uint32_t n_entities, Ogre::Vector3 position_);
	Ogre::Vector3 setProperPosition(int row, int column, int layer, char xyz[3], float size_tiles, float size_layer);

	// Puntero al motor
	WEManager* _weM;
};