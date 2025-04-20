#include "../headers/parser.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

int main() {
    interpreter test;

    
    std::cout << "Enter LittleC code (type end; to execute):\n";
    std::stringstream buffer;
    std::string line;

    while (std::getline(std::cin, line)) {
        if (line == "end;") break;
        buffer << line << "\n";
    }

    std::string code = buffer.str();

    try {
        Lexer lexer(code);
        std::vector<Token> tokens = lexer.tokenize();

        interpreter interp;
        Parser parser(tokens, interp);
        parser.parse();

        std::cout << "\n--- Program Output ---\n";
        interp.run_program();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
