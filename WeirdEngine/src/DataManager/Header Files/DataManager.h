#pragma once

#include "json.hpp"
#include "EntityC.h"
#include <vector>
using json = nlohmann::json;

class DataManager 
{
public:
	json ReadJson(const std::string& file_name);
	void Debug(json json_file);
	std::vector<EntityC*> Load(const std::string& map_file, const std::string& prefabs_file);
};