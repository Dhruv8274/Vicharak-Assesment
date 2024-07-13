#include "lexer.h"

Lexer::Lexer(const std::string& input) : input(input), position(0) {}

Token Lexer::getNextToken() {
    skipWhitespace();
    if (position >= input.size()) {
        return { TokenType::TOKEN_EOF, "" };
    }
    char currentChar = input[position];
    if (std::isdigit(currentChar)) {
        return processNumber();
    } else if (std::isalpha(currentChar)) {
        return processIdentifier();
    } else {
        switch (currentChar) {
            case '=':
                ++position;
                return { TokenType::TOKEN_ASSIGN, "=" };
            case '+':
                ++position;
                return { TokenType::TOKEN_PLUS, "+" };
            case '-':
                ++position;
                return { TokenType::TOKEN_MINUS, "-" };
            case '{':
                ++position;
                return { TokenType::TOKEN_LBRACE, "{" };
            case '}':
                ++position;
                return { TokenType::TOKEN_RBRACE, "}" };
            case ';':
                ++position;
                return { TokenType::TOKEN_SEMICOLON, ";" };
            default:
                ++position;
                return { TokenType::TOKEN_UNKNOWN, std::string(1, currentChar) };
        }
    }
}

void Lexer::skipWhitespace() {
    while (position < input.size() && std::isspace(input[position])) {
        ++position;
    }
}

TokenType Lexer::checkKeyword(const std::string& identifier) {
    if (identifier == "int") return TokenType::TOKEN_INT;
    else if (identifier == "if") return TokenType::TOKEN_IF;
    else if (identifier == "==") return TokenType::TOKEN_EQUAL;
    else return TokenType::TOKEN_IDENTIFIER;
}

Token Lexer::processIdentifier() {
    size_t start = position;
    while (position < input.size() && (std::isalnum(input[position]) || input[position] == '_')) {
        ++position;
    }
    std::string identifier = input.substr(start, position - start);
    TokenType type = checkKeyword(identifier);
    return { type, identifier };
}

Token Lexer::processNumber() {
    size_t start = position;
    while (position < input.size() && std::isdigit(input[position])) {
        ++position;
    }
    std::string number = input.substr(start, position - start);
    return { TokenType::TOKEN_NUMBER, number };
}
