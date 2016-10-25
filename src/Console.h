#pragma once
#include <string>
class Console
{
public:
	Console();
	~Console();

	bool visible;
	std::string cmd;
	std::string buff;
};

