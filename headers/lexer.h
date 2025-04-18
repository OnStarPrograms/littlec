#include <string>
#include <vector>
#pragma once

// Token types for LittleC
// Keywords: int, string, char, print, if, while
// ~, |, <, >, +, -, /, *
enum class TokenType {
    INT_TYPE, STRING_TYPE, CHAR_TYPE,
    IDENTIFIER, INTEGER, STRING_LITERAL, CHAR_LITERAL,
    ASSIGN, PLUS, MINUS, STAR, SLASH, EQUAL, LESS, GREATER,
    PRINT, IF, WHILE, LBRACE, RBRACE, SEMICOLON, LPAREN, RPAREN,
    INCREMENT, DECREMENT, NOT_EQUAL,
    END_OF_FILE,
    UNKNOWN
};

struct Token {
    TokenType type;
    std::string value;
    int line;
    Token(TokenType t, const std::string& v, int l)
        : type(t), value(v), line(l) {}
};

class Lexer {
public:
    Lexer(const std::string& source);
    std::vector<Token> tokenize();

private:
    std::string source;
    size_t current = 0;
    int line = 1;

    char peek();
    char advance();
    bool match(char expected);
    void skip_whitespace();

    //variable names
    Token identifier();
    Token number();
    Token string_literal();
    Token char_literal();
    Token make_token(TokenType type, const std::string& value);
};
