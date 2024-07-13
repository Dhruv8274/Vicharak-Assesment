#include "lexer.h"
#include "parser.h"
#include "assemblycode.h"
#include<bits/stdc++.h>
using namespace std;
int main() {
    Lexer lexer("int a = b + c;");
    Parser parser(lexer);
    ASTNode* root = parser.parseProgram();

    CodeGenerator codeGenerator;
    string assemblyCode = codeGenerator.generateCode(root);

    cout << "Generated Assembly Code:" <<endl;
    cout << assemblyCode <<endl;

    return 0;
}
