#ifndef ASSEMBLYCODE_H
#define ASSEMBLYCODE_H

#include <sstream>
#include "parser.h"

class CodeGenerator {
public:
    CodeGenerator();

    std::string generateCode(ASTNode* root);

private:
    std::stringstream output;
    int labelCount;

    void generateNode(ASTNode* node);
    void generateVariableDeclaration(ASTNode* node);
    void generateAssignment(ASTNode* node);
    void generateBinaryOperation(ASTNode* node);
};

#endif 
