#include "Code.h"

std::string Code::Convert(Instruction instruction) {
	std::string binary;

	if (!instruction.cInstruction)
		binary = std::bitset<16>(std::stoi(instruction.value)).to_string();
	else
		binary = "111" + compTable[instruction.comp] + destTable[instruction.dest] + jumpTable[instruction.jump];

	return binary;
}