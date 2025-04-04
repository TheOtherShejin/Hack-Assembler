#include "Parser.h"

void Parser::ParseFile(std::string fileLocation) {
	std::ifstream file(fileLocation.c_str());
	if (!file.is_open()) {
		std::cout << "Failed to open file at: " << fileLocation << '\n';
		return;
	}

	std::string line;
	// First Pass
	int nextLineNumber = 0;
	while (std::getline(file, line)) {
		line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
		if (line[0] == '/' || line == "") continue;

		// Label
		if (line[0] == '(') {
			std::string label = line.substr(1, line.length() - 2);
			symbolTable.insert({ label, std::to_string(nextLineNumber) });
			continue;
		}

		nextLineNumber++;
	}

	// Second Pass
	file.clear();
	file.seekg(0, file.beg);
	int nextVariableAddress = 16;
	while (std::getline(file, line)) {
		line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
		if (line[0] == '/' || line[0] == '(' || line == "") continue;

		if (line[0] == '@') {
			std::string value = line.substr(1, line.length() - 1);
			if (!std::isdigit(value[0])) {
				if (symbolTable.find(value) == symbolTable.end()) {
					symbolTable.insert({ value, std::to_string(nextVariableAddress) });
					value = symbolTable[value];
					nextVariableAddress++;
				}
				else value = symbolTable[value];
			}

			instructions.push_back(ParseAInstruction(value));
		}
		else instructions.push_back(ParseCInstruction(line));
	}

	file.close();
}

Instruction Parser::ParseAInstruction(std::string value) {
	Instruction instruction;
	instruction.cInstruction = false;
	instruction.value = value;
	return instruction;
}

Instruction Parser::ParseCInstruction(std::string instructionText) {
	Instruction instruction;
	instruction.cInstruction = true;

	int equalIdx = instructionText.find('=');
	int semicolonIdx = instructionText.find(';');

	instruction.comp = instructionText.substr(equalIdx + 1, semicolonIdx == -1 ? (instructionText.length() - semicolonIdx) : (semicolonIdx - equalIdx) - 1);
	if (equalIdx != -1)
		instruction.dest = instructionText.substr(0, equalIdx);
	if (semicolonIdx != -1)
		instruction.jump = instructionText.substr(semicolonIdx + 1, 3);

	return instruction;
}