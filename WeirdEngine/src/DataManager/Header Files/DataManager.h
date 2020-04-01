#pragma once

#include "json.hpp"
#include "EntityC.h"
#include <vector>
using json = nlohmann::json;

// Componentes
#include "ComponentFactory.h"

class DataManager {
public:
	DataManager();
	~DataManager() {};

	json ReadJson(const std::string& file_name);
	void Debug(json json_file);

	std::vector<EntityC*> Load(const std::string& map_file, const std::string& prefabs_file);
	std::vector<EntityC*> LoadSceneEntities(const std::string& entities_file);
private:

	//Factorias
	//std::map<Ogre::String, 

	// Factories
	//GmInputFactory* _gmiF;
	//RenderFactory* _rF;
	TransformFactory* _tF;

	// Components
	//GmInputComponent* GmiComp;
	TransformComponent* tComp;
	//RenderComponent* rComp;
};