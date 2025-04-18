#pragma once

#include "Instruction.h"
#include <iostream>
#include <fstream>
#include <vector>

#include <unordered_map>

class Parser {
private:
	Instruction ParseAInstruction(std::string instructionText);
	Instruction ParseCInstruction(std::string instructionText);

	std::unordered_map<std::string, std::string> symbolTable = {
		{ "R0",		"0" },
		{ "R1",		"1" },
		{ "R2",		"2" },
		{ "R3",		"3" },
		{ "R4",		"4" },
		{ "R5",		"5" },
		{ "R6",		"6" },
		{ "R7",		"7" },
		{ "R8",		"8" },
		{ "R9",		"9" },
		{ "R10",	"10" },
		{ "R11",	"11" },
		{ "R12",	"12" },
		{ "R13",	"13" },
		{ "R14",	"14" },
		{ "R15",	"15" },
		{ "SP",		"0" },
		{ "LCL",	"1" },
		{ "ARG",	"2" },
		{ "THIS",	"3" },
		{ "THAT",	"4" },
		{ "SCREEN", "16384" },
		{ "KBD",    "24576" }
	};
public:
	std::vector<Instruction> instructions;

	void ParseFile(std::string fileLocation);
};
