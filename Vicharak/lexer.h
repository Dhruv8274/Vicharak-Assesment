#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <cctype>

enum class TokenType {
    TOKEN_INT,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_ASSIGN,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_IF,
    TOKEN_EQUAL,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_SEMICOLON,
    TOKEN_EOF,
    TOKEN_UNKNOWN
};

struct Token {
    TokenType type;
    std::string text;
};

class Lexer {
public:
    Lexer(const std::string& input);

    Token getNextToken();
    void skipWhitespace();

private:
    const std::string& input;
    size_t position;

    TokenType checkKeyword(const std::string& identifier);
    Token processIdentifier();
    Token processNumber();
};

#endif 
