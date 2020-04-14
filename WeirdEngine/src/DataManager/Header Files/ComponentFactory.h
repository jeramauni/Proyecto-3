#pragma once
#include "C_Factory.h"
// Componentes de entidades




#define DEFINE_FACTORY(x) class x##Factory : public CompFactory {public: x##Component* Create(){ return new x##Component();}}


/////////////////////////Aclaraciones///////////////////////////////

