#include <iostream>

#include "Deque.h"
#include "PostFix.h"
#include "Parser.h"
#include "ExpressionNode.h"
#include "Lexer.h"
#include "ConDec.h"
#include "ExpressionTreePrint.h"
#include "Expression.h"

int main() {
    banner("Expression Parser");

//    std::string strExpression = "(8-1+3)*6--((3+77)*2*(4+7^(3-1)+2*4*4))";
    std::string strExpression = "9*x+14/x";
    Lexer lexer(strExpression);
    lexer.tokenize();
    Deque<Token> tokens = lexer.getTokens();

    PostFix postFix(tokens);
    postFix.postfix();
    Deque<Token> postfixTokens = postFix.getPostfixTokens();

    Parser parser(postfixTokens);
    parser.parse();
    ExpressionNode* tree = parser.getExpressionTree();
    std::vector<VariableNode*> vars = parser.getVariables();

    Expression expression(tree, vars);

    divider("Tokens");
    std::cout << tokens << '\n';

    divider("Postfix");
    std::cout << postfixTokens << '\n';

    divider("Variables");
    expression.setVariableValue(0, 5);
    for(size_t i = 0; i < expression.getVariablesSize(); ++i) {
        std::cout << expression.getVariableName(i) << " = " << expression.getVariableValue(i) << '\n';
    }

    divider("Evaluation");
    std::cout << expression.evaluate() << '\n';

    divider("Tree");
    customPrintPreorder(tree, false, "   ", "│  ", "├─>", "└─>");
}
