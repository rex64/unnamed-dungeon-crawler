#pragma once
#include <string>
class Console
{
public:
	Console();
	~Console();
	void init();

	static Console* console;

	bool visible;
	std::string cmd;
	std::string buff;
};
