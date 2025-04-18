#include "../headers/parser.h"
#include <iostream>

bool inside_while = false;

Parser::Parser(std::vector<Token> tokens, interpreter& interp)
    : tokens(std::move(tokens)), current(0), interp(interp) {}

void Parser::parse() {
    while (!check(TokenType::END_OF_FILE)) {
        statement();
    }
}

Token Parser::peek() {
    return tokens[current];
}

Token Parser::previous() {
    return tokens[current - 1];
}

Token Parser::advance() {
    if (!check(TokenType::END_OF_FILE)) current++;
    return previous();
}

bool Parser::match(std::initializer_list<TokenType> types) {
    for (auto type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

bool Parser::check(TokenType type) {
    return peek().type == type;
}

void Parser::consume(TokenType type, const std::string& error_msg) {
    if (check(type)) {
        advance();
    } else {
        error(peek(), error_msg);
    }
}

void Parser::error(const Token& token, const std::string& message) {
    std::cerr << "[Line " << token.line << "] Error: " << message << " at '" << token.value << "'\n";
    exit(1);
}

void Parser::statement() {
    if (check(TokenType::INT_TYPE) || check(TokenType::STRING_TYPE) || check(TokenType::CHAR_TYPE)) {
        declaration();
    } else if (check(TokenType::IDENTIFIER)) {
        if (tokens[current + 1].type == TokenType::INCREMENT) {
            std::string name = advance().value;
            advance();
            interp.increment(name);
            consume(TokenType::SEMICOLON, "Expected ';' after increment.");
        } else if (tokens[current + 1].type == TokenType::DECREMENT) {
            std::string name = advance().value;
            advance();
            interp.decrement(name);
            consume(TokenType::SEMICOLON, "Expected ';' after decrement.");
        } else {
            assignment();
        }
    } else if (check(TokenType::PRINT)) {
        print_statement();
    } else if (check(TokenType::IF)) {
        if_statement();
    } else if (check(TokenType::WHILE)) {
        while_statement();
    } else if (check(TokenType::LBRACE)) {
        block();
    } else {
        error(peek(), "Unexpected statement.");
    }
}

void Parser::declaration() {
    Token type = advance();
    std::string var_name = advance().value;
    consume(TokenType::ASSIGN, "Expected '=' after variable name.");
    std::string val = advance().value;
    consume(TokenType::SEMICOLON, "Expected ';' after declaration.");

    if (type.type == TokenType::INT_TYPE) interp.create_int(var_name, std::stoi(val));
    else if (type.type == TokenType::STRING_TYPE) interp.create_string(var_name, val);
    else if (type.type == TokenType::CHAR_TYPE) interp.create_char(var_name, val[0]);
}


void Parser::assignment() {
    std::string var_name = advance().value;
    consume(TokenType::ASSIGN, "Expected '=' after variable name.");

    if (check(TokenType::IDENTIFIER)) {
        std::string right = advance().value;
        if (match({TokenType::PLUS, TokenType::MINUS, TokenType::STAR, TokenType::SLASH})) {
            char op = previous().value[0];
            std::string second = advance().value;
            interp.compare(right, second, op);
            interp.set_var(var_name, 0);
        } else {
            interp.set_var(var_name, right);
        }
    } else if (check(TokenType::INTEGER)) {
        std::string val = advance().value;
        interp.set_var(var_name, std::stoi(val));
    }

    consume(TokenType::SEMICOLON, "Expected ';' after assignment.");
}


void Parser::print_statement() {
    advance();
    std::string var = advance().value;
    consume(TokenType::SEMICOLON, "Expected ';' after print statement.");
    interp.print_var(var);
}

void Parser::parse_condition(std::string& left, char& op, std::string& right) {
    if (check(TokenType::LPAREN)) advance();
    left = advance().value;
    Token op_token = advance();
    right = advance().value;

    if (op_token.value == "~" || op_token.value == "|" ||
        op_token.value == "<" || op_token.value == ">") {
        op = op_token.value[0];
    } else {
        error(op_token, "Invalid operator in condition.");
    }

    if (check(TokenType::RPAREN)) advance();
}

void Parser::if_statement() {
    advance();
    std::string left, right;
    char op;
    parse_condition(left, op, right);
    interp.compare(left, right, op);
    interp.start_if();
    block();
    interp.end_if();
}

void Parser::while_statement() {
    advance();
    std::string left, right;
    char op;
    parse_condition(left, op, right);
    interp.compare(left, right, op);
    interp.start_while();

    //interp.compare(left, right, op);

    block();
    interp.compare(left, right, op); // trying this
    interp.end_while();
}

void Parser::block() {
    consume(TokenType::LBRACE, "Expected '{' to start block.");

    while (!check(TokenType::RBRACE) && !check(TokenType::END_OF_FILE)) {
        statement();
    }

    consume(TokenType::RBRACE, "Expected '}' to end block.");
}
