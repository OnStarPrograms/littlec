#include "lexer.h"
#include "interpreter.h"
#include <vector>
#include <string>
#pragma once

class Parser {
public:
    Parser(std::vector<Token> tokens, interpreter& interp);
    void parse();

private:
    std::vector<Token> tokens;
    size_t current;
    interpreter& interp;

    Token peek();
    Token previous();
    Token advance();
    bool match(std::initializer_list<TokenType> types);
    bool check(TokenType type);

    void statement();
    void declaration();
    void assignment();
    void print_statement();
    void parse_condition(std::string& left, char& op, std::string& right);
    void if_statement();
    void while_statement();
    void block();

    void consume(TokenType type, const std::string& error_msg);
    void error(const Token& token, const std::string& message);
};
