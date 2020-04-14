#include "FactoryRegister.h"
#include "ComponentFactory.h"
FactoryRegister::FactoryRegister(std::unordered_map<std::string, CompFactory*>& factories) {
	
	std::string aux = "Transform";
	
	factories.insert({ aux, new TransformFactory() });
	aux = "Render";
	factories.insert({ aux, new RenderFactory() });
}