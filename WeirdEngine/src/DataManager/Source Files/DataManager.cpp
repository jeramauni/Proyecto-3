// DataManager.cpp : Define las funciones de la biblioteca estática.
// BE AWARE! Los archivos de mapas y prefabs deben guardarse en el directorio resources del directorio exes del proyecto.

#include "DataManager.h"
#include "Container.h"
#include "ComponentFactory.h"

#include <iostream>
#include <fstream>
#include <ctime>
#include <map>

extern FactoriesGestor* factoriesGestor = FactoriesGestor::getInstance();

CREATE_REGISTER(Render);
CREATE_REGISTER(Transform);
CREATE_REGISTER(Test);
CREATE_REGISTER(Physics);

//Reads a .json file ande parses it to a json class instance
json DataManager::ReadJson(const std::string& file_name) {
	json j;
	std::ifstream input;
	//AUX
	std::string s;
	s = "resources/gameFiles/" + file_name;
	input.open(s);

	input >> j;

	input.close();
	return j;
}

std::vector<std::vector<std::string>> DataManager::ReadMap(const std::string& file_name) {
	std::vector<std::vector<std::string>> map;
	std::ifstream input;
	//AUX
	std::string s;

	s = "resources/gameFiles/" + file_name;
	input.open(s);
	s.clear();

	while (!input.eof())
	{
		//Si la siguiente linea se debe leer..
		if (ReadNext(input))
		{
			getline(input, s);
			map.push_back(GetWords(s));
		}
		else
		{
			getline(input, s);
		}
	}

	input.close();
	return map;
}

//Outputs on console a readable debug of a json file
void DataManager::DebugJson(json json_file)
{
	std::cout << '\n' << "---------------------------------------JsonDebug-Start--------------------------------------" << '\n';

	std::cout << "Debugging " << json_file.begin().key() << " file... " << '\n' << '\n';
	json_file = json_file.at(json_file.begin().key());

	//For each object in the file...
	for (std::size_t i = 0; i < json_file.size(); i++) {
		std::cout << "----------------------" << '\n';
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
			for (std::size_t j = 0; j < json_file[i].at("components").size(); j++)
			{
				std::cout << '*' << json_file[i].at("components")[j].at("id") << '*' << '\n'; 	//Component type
				std::cout << json_file[i].at("components")[j] << '\n';								//Component description
			}
		}

		std::cout << "----------------------" << '\n';
	}
	std::cout << '\n' << "---------------------------------------JsonDebug-End--------------------------------------" << '\n';
}

Container* DataManager::CreateEntity(std::string& id, json prefabs, uint32_t n_entities, Ogre::Vector3 position_)
{
	prefabs = prefabs.at(prefabs.begin().key());
	uint32_t i = 0;
	//Busqueda de id en el archivo de prefabs
	while (i < prefabs.size() && prefabs[i].at("id") != id)
	{		
		i++;
	}
	//Si no lo encuentra lo notifica y devuelve nullptr
	if (i >= prefabs.size())
	{
		std::cerr << "Entity " << id << " not found on prefabs file!" << '\n';
		return nullptr;
	}
	//Si lo encuentra crea y devuelve la entidad 
	else
	{
		//Hay que hacer la lectura de id's de componentes
		std::string entity_name = id + "_" + std::to_string(n_entities);
		//EntityC* e = new EntityC(entity_name);
		Container* e = new Container(entity_name, _weM);

		std::unordered_map<std::string, std::string> param;
		int size_ = prefabs[i].at("components").size();
		//Para cada componente en la lista de componentes
		for (std::size_t j = 0; j < size_; j++)
		{
			e->AddComponent(factoriesGestor->getFactories().at(prefabs[i].at("components")[j].at("id"))->Create());
			//Para cada parametro del componente excluyendo el id

			for (auto x = prefabs[i].at("components")[j].begin(); x != prefabs[i].at("components")[j].end(); x++)
			{

				param.insert(std::pair<std::string, std::string>(x.key(), x.value()));
			}
			e->getComponent(prefabs[i].at("components")[j].at("id"))->Init(param);
		}

		//Set the proper position of the entity
		if (e->hasComponent("Transform"))
		{
			static_cast<TransformComponent*>(e->getComponent("Transform"))->SetPosition(position_);
		}
		else
		{
			std::cerr << "Couldn't set " << e->GetEntityName() << " position to the one on the map. \n Position set to the one of its prefab. \n" ;
		}

		if (debug_) 
		{
			std::cout << "Entity " << entity_name << " successfully created at position: { ";
			Ogre::Vector3* v = static_cast<TransformComponent*>(e->getComponent("Transform"))->GetPosition();
			std::cout << v->x << ", " << v->y << ", " << v->z << " }" << '\n';
		}
		
		return e;
	}
}

void DataManager::DebugMap(std::vector<std::vector<std::string>> map, bool output_debugTxt)
{
	std::ofstream output;
	time_t now = time(0);
	char dateTime[26];
	std::string d_file_name;

	if (output_debugTxt) {
		d_file_name = "resources/gameFiles/mapDebugs/debug_map_";
		ctime_s(dateTime, sizeof(dateTime), &now);

		int i = 0;
		bool end = false;
		while (!end && i < sizeof(dateTime))
		{
			if (dateTime[i] == '\n')
			{
				end = true;
			}

			else if (dateTime[i] == ' ')
			{
				dateTime[i] = '_';
			}

			else if (dateTime[i] == ':')
			{
				dateTime[i] = '-';
			}
			
			if (!end)
			{
				d_file_name += dateTime[i];
				i++;
			}	
		}
		d_file_name += ".txt";

		std::cout << '\n' << "---------------------------------------MapDebug-Start--------------------------------------" << '\n';
		std::cout << "Map debug file created at: " << d_file_name << "\n";

		output.open(d_file_name);
	}

	for (auto i = map.begin(); i != map.end(); i++)
	{	
		if (output_debugTxt)
			output << "--------------------------------------" << '\n';
		std::cout << "--------------------------------------" << '\n';

		for (auto j = i->begin(); j != i->end(); j++)
		{
			if (output_debugTxt)
				output << j->c_str() << '|';
			std::cout << j->c_str() << '|';
		}
		if (output_debugTxt)
			output << '\n' << "--------------------------------------" << '\n';
		std::cout << '\n' << "--------------------------------------" << '\n';
	}
	std::cout << '\n' << "---------------------------------------MapDebug-End--------------------------------------" << '\n';
	if (output_debugTxt)
		output.close();
}

bool DataManager::ReadNext(std::ifstream& input)
{
	char c;
	c = input.peek();

	//Si es un salto de línea -> no lee 
	if (c == '\n')
		return false;

	//Si es un comentario -> no lee
	else if (c == '/')
	{
		input.get();
		c = input.peek();
		if (c == '/') 
			return false;		
	}

	//En cualquier otro caso si lee
	return true;
}

std::vector<std::string> DataManager::GetWords(std::string& s)
{
	std::vector<std::string> words;
	std::string word;
	for (auto x : s)
	{
		if (x == ' ')
		{
			words.push_back(word);
			word = "";
		}
		else
		{
			word = word + x;
		}
	}
	words.push_back(word);
	return words;
}

Ogre::Vector3 DataManager::setProperPosition(int row, int column, int layer, char xyz[3], float size_tiles, float size_layer)
{
	Ogre::Vector3 propperPos = { 0.0f, 0.0f, 0.0f };
	float x = 0.0, y = 0.0, z = 0.0;

	//Column value
	if (xyz[0] == 'x')		x = column * size_tiles;
	else if (xyz[0] == 'y')	y = column * size_tiles;
	else if (xyz[0] == 'z')	z = column * size_tiles;
	//Row value
	if (xyz[1] == 'x')		x = row * size_tiles;
	else if (xyz[1] == 'y')	y = row * size_tiles;
	else if (xyz[1] == 'z')	z = row * size_tiles;
	//Layer value
	if (xyz[2] == 'x')		x = size_layer;
	else if (xyz[2] == 'y')	y = size_layer;
	else if (xyz[2] == 'z')	z = size_layer;

	propperPos = { x, y, z};
	return propperPos;
}

std::vector<Container*> DataManager::ProcessMap(std::vector<std::vector<std::string>> map, json prefabs, bool debug)
{
	std::vector<Container*> entities;
	int n = std::stoi(map[0][0]);		//Number of entities on legend
	int aux = n + 1;					//row aux variable
	int ct = 0, cct = 0;				//row counter 
	std::map<int, std::string> legend;	//Map of entitie types on map (id on map - name on prefabs file)
	char xyz[3];						//Axis representation on map (Columns x Rows / Between layers) (x-y-z)
	int r, c;							//Mapsize (Row - columns)
	float s;							//Size between tiles
	int layer = 0;
	//Entity processing
	float slyr = 0.0;						//Size between layers
	int id = -1;						//id of entity to process
	//Position processing
	Ogre::Vector3 currentpos_ = { 0.0f, 0.0f, 0.0f };
	//Legend
	for (std::size_t i = 1; i <= n; i++)
	{
		legend[std::stoi(map[i][0])] = map[i][1];
	}
	//Axis representation
	for (std::size_t i = 0; i < 3; i++)
		xyz[i] = map[aux][i].back(); aux++;
	//Size between tiles
	s = std::stof(map[aux][0]);	aux++;
	//Mapsize (columns - rows)
	c = std::stoi(map[aux][0]);
	r = std::stoi(map[aux][1]); aux++;

	//Layers
	if (debug_)
		std::cout << "Layer : " << layer << '\n';
	for (auto row = map.begin() + aux++; row != map.end(); row++)
	{
		ct++;
		for (auto column = row->begin(); column != row->end(); column++)
		{				
			if (ct > r)	//If we are at the row between layers we get the distance between layers
			{
				layer++;
				slyr += std::stof(*column);
				ct = 0;
				if (debug_) {
					std::cout << "Layer: " << layer << '\n';
				}
				
			}
			else		//If not we get the next id..
			{
				id = std::stoi(*column);
				if (id != -1)
				{	
					//...set the next position..
					currentpos_ = setProperPosition(ct-1, cct, layer, xyz, s, slyr);
					//..and create the proper entity
					Container* e = CreateEntity(legend[id], prefabs, entities.size(), currentpos_);
					if (e != nullptr) entities.push_back(e);
				}
			}
			cct++;
		}
		cct = 0;
		std::cout << '\n';
	}

	//DEBUG----------------------------------
	if (debug)
	{
		std::cout << '\n' << "---------------------------------------ProcessMap-Start--------------------------------------" << '\n';
		std::cout << "n leyenda: " << n << '\n';
		//Legend
		for (auto it = legend.begin(); it != legend.end(); it++)
		{
			std::cout << "id: " << it->first << " - " << it->second << '\n';
		}
		//Axis representation
		std::cout << "Axis representation: ";
		for (std::size_t i = 0; i < 3; i++)
			std::cout << xyz[i];
		std::cout << '\n';
		//Size between tiles
		std::cout << "size between tiles: " << s << '\n';
		//Mapsize 
		std::cout << "Mapsize (CxR): " << c << 'x' << r << '\n';

		std::cout << '\n' << "---------------------------------------ProcessMap-End--------------------------------------" << '\n';
	}
	//DEBUG----------------------------------

	return entities;
}


std::vector<Container*> DataManager::Load(const std::string& map_file, const std::string& prefabs_file, bool debug_mode)
{
	debug_ = debug_mode;

	//Vector de entidades del mapa
	std::vector<Container*> entities;
	json prefabs;								//Prefabs data
	std::vector<std::vector<std::string>> map;	//Map data

	//Error fuse
	bool fail = false;

	std::cout << '\n' << "Game Data loading initiated... \n";

	//Lectura y carga del archivo mapa ----------------------------------------
	try
	{
		map = ReadMap(map_file);
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
			//----------------------------MAIN-----------------------------------------
			if (debug_)
			{
				DebugJson(prefabs);
				DebugMap(map, true);
			}			
			entities = ProcessMap(map, prefabs, debug_);
			//-------------------------------------------------------------------------
			if (!fail)
			{
				std::cout << "Game Data loading finished successfully! \n \n";
			}
		}
	}
	return entities;
}

void DataManager::setWEM(WEManager* wem) {
	_weM = wem;
}
