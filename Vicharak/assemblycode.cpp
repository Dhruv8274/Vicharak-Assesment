#include "assemblycode.h"

CodeGenerator::CodeGenerator() : labelCount(0) {}

std::string CodeGenerator::generateCode(ASTNode* root) {
    generateNode(root);
    return output.str();
}

void CodeGenerator::generateNode(ASTNode* node) {
    switch (node->type) {
        case NodeType::VARIABLE_DECLARATION:
            generateVariableDeclaration(node);
            break;
        case NodeType::ASSIGNMENT:
            generateAssignment(node);
            break;
        case NodeType::BINARY_OPERATION:
            generateBinaryOperation(node);
            break;
        default:
            throw std::runtime_error("Unsupported node type");
    }
}

void CodeGenerator::generateVariableDeclaration(ASTNode* node) {
    output << "; Variable declaration: " << node->identifier << std::endl;
}

void CodeGenerator::generateAssignment(ASTNode* node) {
    output << "; Assignment: " << node->identifier << " = ";
    generateNode(node->children[0]);
    output << std::endl;
    output << "MOV " << node->identifier << ", " << "result_register" << std::endl;
}

void CodeGenerator::generateBinaryOperation(ASTNode* node) {
    generateNode(node->children[0]);
    switch (node->op) {
        case TokenType::TOKEN_PLUS:
            output << "ADD ";
            break;
        case TokenType::TOKEN_MINUS:
            output << "SUB ";
            break;
        default:
            throw std::runtime_error("Unsupported operation");
    }
    generateNode(node->children[1]);
    output << ", result_register" << std::endl;
}
