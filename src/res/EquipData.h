#pragma once

#include <string>
#include <vector>

enum EquipType {

	WEAPON = 0,
	HEAD,
	BODY,
	ACCESSORY

};

struct EquipData {

	std::string id;
	std::string fileName;
	std::string filePath;
	std::string name;
	EquipType type;

	std::vector<std::string> skillsIds;
};