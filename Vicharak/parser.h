#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "lexer.h"
#include <stdexcept>

enum class NodeType {
    VARIABLE_DECLARATION,
    ASSIGNMENT,
    BINARY_OPERATION,
    CONDITIONAL
};

struct ASTNode {
    NodeType type;
    std::string identifier; 
    int value;              
    TokenType op;           
    std::vector<ASTNode*> children;
};

class Parser {
public:
    Parser(Lexer& lexer);

    ASTNode* parseProgram();

private:
    Lexer& lexer;
    Token currentToken;

    void eat(TokenType expectedType);
    ASTNode* parseStatement();
    ASTNode* parseVariableDeclaration();
    ASTNode* parseAssignment();
    ASTNode* parseExpression();
    ASTNode* parseConditional();
};

#endif
