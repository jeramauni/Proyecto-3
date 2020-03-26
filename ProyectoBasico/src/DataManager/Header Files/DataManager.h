#pragma once

#include "json.hpp"
using json = nlohmann::json;

class DataManager 
{
public:
	json ReadJson(const std::string& file_name);
	void Debug(json json_file);
};