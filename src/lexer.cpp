#include "../headers/lexer.h"
#include <cctype>
#include <unordered_map>

Lexer::Lexer(const std::string& src) : source(src), current(0), line(1) {}

char Lexer::peek() {
    if (current >= source.length()) return '\0';
    return source[current];
}

char Lexer::advance() {
    if (current >= source.length()) return '\0';
    return source[current++];
}

bool Lexer::match(char expected) {
    if (peek() == expected) {
        current++;
        return true;
    }
    return false;
}

void Lexer::skip_whitespace() {
    while (true) {
        char c = peek();
        if (c == ' ' || c == '\r' || c == '\t') {
            advance();
        } else if (c == '\n') {
            line++;
            advance();
        } else if (c == '/' && current + 1 < source.length() && source[current + 1] == '/') {
            while (peek() != '\n' && peek() != '\0') {
                advance();
            }
        } else {
            break;
        }
    }
}

Token Lexer::make_token(TokenType type, const std::string& value) {
    return Token(type, value, line);
}

Token Lexer::string_literal() {
    std::string value;
    while (peek() != '"' && peek() != '\0') {
        if (peek() == '\n') line++;
        value += advance();
    }
    advance();
    return make_token(TokenType::STRING_LITERAL, value);
}

Token Lexer::char_literal() {
    char c = advance();
    advance();
    return make_token(TokenType::CHAR_LITERAL, std::string(1, c));
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    static const std::unordered_map<std::string, TokenType> keywords = {
        {"int", TokenType::INT_TYPE},
        {"string", TokenType::STRING_TYPE},
        {"char", TokenType::CHAR_TYPE},
        {"print", TokenType::PRINT},
        {"if", TokenType::IF},
        {"while", TokenType::WHILE}
    };

    while (current < source.length()) {
        skip_whitespace();
        char c = peek();

        if (isalpha(c) || c == '_') {
            advance();
            size_t start = current - 1;
            while (isalnum(peek()) || peek() == '_') advance();
            std::string text = source.substr(start, current - start);
            auto it = keywords.find(text);
            if (it != keywords.end()) {
                tokens.push_back(make_token(it->second, text));
            } else {
                tokens.push_back(make_token(TokenType::IDENTIFIER, text));
            }
        } else if (isdigit(c)) {
            advance();
            size_t start = current - 1;
            while (isdigit(peek())) advance();
            std::string text = source.substr(start, current - start);
            tokens.push_back(make_token(TokenType::INTEGER, text));
        } else {
            advance();
            switch (c) {
                case '+':
                    tokens.push_back(match('+') ? make_token(TokenType::INCREMENT, "++") : make_token(TokenType::PLUS, "+"));
                    break;
                case '-':
                    tokens.push_back(match('-') ? make_token(TokenType::DECREMENT, "--") : make_token(TokenType::MINUS, "-"));
                    break;
                case '=':
                    tokens.push_back(make_token(TokenType::ASSIGN, "="));
                    break;
                case '~': tokens.push_back(make_token(TokenType::EQUAL, "~")); break;
                case '|': tokens.push_back(make_token(TokenType::NOT_EQUAL, "|")); break;
                case '*': tokens.push_back(make_token(TokenType::STAR, "*")); break;
                case '/': tokens.push_back(make_token(TokenType::SLASH, "/")); break;
                case '<': tokens.push_back(make_token(TokenType::LESS, "<")); break;
                case '>': tokens.push_back(make_token(TokenType::GREATER, ">")); break;
                case ';': tokens.push_back(make_token(TokenType::SEMICOLON, ";")); break;
                case '{': tokens.push_back(make_token(TokenType::LBRACE, "{")); break;
                case '}': tokens.push_back(make_token(TokenType::RBRACE, "}")); break;
                case '(': tokens.push_back(make_token(TokenType::LPAREN, "(")); break;
                case ')': tokens.push_back(make_token(TokenType::RPAREN, ")")); break;
                case '"': tokens.push_back(string_literal()); break;
                case '\'': tokens.push_back(char_literal()); break;
                default:
                    if (c != '\0') {
                        tokens.push_back(make_token(TokenType::UNKNOWN, std::string(1, c)));
                    }
                    break;
            }
        }
    }

    tokens.push_back(make_token(TokenType::END_OF_FILE, ""));
    return tokens;
}
