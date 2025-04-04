#include "Parser.h"
#include "Code.h"

const std::string FILE_LOCATION = "D:/SHEJIN/Programs/nand2tetris/projects/6/pong/Pong.asm";
const std::string SAVE_FILE_LOCATION = "D:/SHEJIN/Programs/nand2tetris/projects/6/pong/Pong.hack";

int main() {
	std::ofstream binaryFile(SAVE_FILE_LOCATION.c_str());

	Parser parser;
	parser.ParseFile(FILE_LOCATION);

	Code code;

	if (!binaryFile.is_open()) {
		std::cout << "Failed to open file at: " << SAVE_FILE_LOCATION << '\n';
		return -1;
	}

	for (auto& instruction : parser.instructions) {
		binaryFile << code.Convert(instruction) << '\n';
	}

	std::cout << "Hack assembly program has been assembled to: " << SAVE_FILE_LOCATION << '\n';

	binaryFile.close();
	return 0;
}