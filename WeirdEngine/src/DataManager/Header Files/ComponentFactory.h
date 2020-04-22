#pragma once
#include "C_Factory.h"
// Componentes de entidades
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "FactoriesGestor.h"
#include "TestComponent.h"

#define DEFINE_FACTORY(x) class x##Factory : public CompFactory {public: x##Component* Create(){ return new x##Component();}}
#define DEFINE_REGISTER(x) DEFINE_FACTORY(##x);  class x##RegisterFact { public: x##RegisterFact(){  FactoriesGestor::getInstance()->getFactories().insert({#x, new x##Factory()});  }}
#define CREATE_REGISTER(x) DEFINE_REGISTER(##x); x##RegisterFact* x##_aux = new x##RegisterFact(); 

/////////////////////////Aclaraciones///////////////////////////////
