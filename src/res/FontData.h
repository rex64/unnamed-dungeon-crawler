#pragma once

#include <string>
#include <unordered_map>

#include "CharData.h"

struct FontData {
	std::string id;
	std::string fileName;
	std::string filePath;
	std::string name;

	int height;

	int hSpacing;
	int vSpacing;

	std::unordered_map<std::string, CharData*> chars;
};