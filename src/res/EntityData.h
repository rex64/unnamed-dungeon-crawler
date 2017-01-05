#pragma once

#include <string>
#include "FieldEntityData.h"

struct EntityData {
	std::string id;
	std::string fileName;
	std::string name;
	FieldEntityData *data;
};