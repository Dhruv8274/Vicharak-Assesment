#include "parser.h"

Parser::Parser(Lexer& lexer) : lexer(lexer), currentToken(lexer.getNextToken()) {}

void Parser::eat(TokenType expectedType) {
    if (currentToken.type == expectedType) {
        currentToken = lexer.getNextToken();
    } else {
        throw std::runtime_error("Syntax error: Expected token type");
    }
}

ASTNode* Parser::parseProgram() {
    ASTNode* programNode = new ASTNode{ NodeType::CONDITIONAL };
    programNode->children.push_back(parseStatement());
    while (currentToken.type != TokenType::TOKEN_EOF) {
        programNode->children.push_back(parseStatement());
    }
    return programNode;
}

ASTNode* Parser::parseStatement() {
    switch (currentToken.type) {
        case TokenType::TOKEN_INT:
            return parseVariableDeclaration();
        case TokenType::TOKEN_IDENTIFIER:
            return parseAssignment();
        case TokenType::TOKEN_IF:
            return parseConditional();
        default:
            throw std::runtime_error("Syntax error: Unexpected token");
    }
}

ASTNode* Parser::parseVariableDeclaration() {
    ASTNode* declarationNode = new ASTNode{ NodeType::VARIABLE_DECLARATION };
    eat(TokenType::TOKEN_INT);
    declarationNode->identifier = currentToken.text; 
    eat(TokenType::TOKEN_IDENTIFIER); 
    eat(TokenType::TOKEN_SEMICOLON); 
    return declarationNode;
}

ASTNode* Parser::parseAssignment() {
    ASTNode* assignmentNode = new ASTNode{ NodeType::ASSIGNMENT };
    assignmentNode->identifier = currentToken.text; 
    eat(TokenType::TOKEN_IDENTIFIER); 
    eat(TokenType::TOKEN_ASSIGN); 
    assignmentNode->children.push_back(parseExpression()); 
    eat(TokenType::TOKEN_SEMICOLON); 
    return assignmentNode;
}

ASTNode* Parser::parseExpression() {
    ASTNode* expressionNode = parseVariableDeclaration();
    return expressionNode;
}

ASTNode* Parser::parseConditional() {
    ASTNode* conditionalNode = new ASTNode{ NodeType::CONDITIONAL };
    eat(TokenType::TOKEN_IF); 
    conditionalNode->children.push_back(parseExpression());
    eat(TokenType::TOKEN_LBRACE);
    while (currentToken.type != TokenType::TOKEN_RBRACE) {
        conditionalNode->children.push_back(parseStatement());
    }
    eat(TokenType::TOKEN_RBRACE);
    return conditionalNode;
}
