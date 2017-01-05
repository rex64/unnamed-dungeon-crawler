#pragma once

#include <string>
#include <vector>

#include "Stats.h"

struct HeroData {
	std::string id;
	std::string fileName;
	std::string filePath;
	std::string name;

	std::vector<std::string> skillsIds;
	std::vector<Stats> stats;
};