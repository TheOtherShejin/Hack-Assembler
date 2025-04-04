#pragma once

#include <string>

struct Instruction {
	bool cInstruction = false;
	std::string value;
	std::string comp, dest, jump;
};
