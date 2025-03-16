#include <iostream>

#include "Deque.h"
#include "PostFix.h"
#include "Parser.h"
#include "Lexer.h"
#include "ConDec.h"
#include "Expression.h"

long randomLong(long min, long max) {
    return rand() % (max - min + 1) + min;
}
double randomDouble(double min, double max) {
    return rand() % RAND_MAX / (RAND_MAX - 1.0) * (max - min) + min;
}
bool randomChance(double chance) {
    return randomDouble(0, 1) <= chance;
}
char randomOperator() {
    switch(randomLong(0, 5)) {
        case 0:
            return '+';
            break;
        case 1:
            return '-';
            break;
        case 2:
            return '*';
            break;
        case 3:
            return '/';
            break;
        case 4:
            return '%';
            break;
        case 5:
            return '^';
            break;
        default:
            return '+';
    }
}
std::string randomExpression(long minLen, long maxLen) {
    size_t len = randomLong(minLen, maxLen);
    size_t par = 0;
    std::string strExpression;
    for(size_t i = 0; i < len; ++i) {
        if(i > 0) {
            strExpression += randomOperator();
        }
        if(randomChance(0.5)) {
            par++;
            strExpression += '(';
        }
        if(randomChance(1.0/3.0)) {
            strExpression += '-';
        }
        if(randomChance(2.0/3.0)) {
            strExpression += std::to_string(randomLong(0, 100));
        } else {
            strExpression += static_cast<char>(randomLong('a', 'd'));
        }
        if(randomChance(0.40) && par > 0) {
            par--;
            strExpression += ')';
        }
    }
    while(par > 0) {
        strExpression += ')';
        par--;
    }
    return strExpression;
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    banner("Expression Parser");

    divider("String Expression");
//    std::string strExpression = randomExpression(300, 1000);
    std::string strExpression = randomExpression(2, 10);
//    std::string strExpression = "-5^4";
//    std::string strExpression = "-5*4";
    std::cout << strExpression << '\n';

    divider("Tokens");
    Lexer lexer(strExpression);
    lexer.tokenize();
    Deque<Token> tokens = lexer.getTokens();
    std::cout << tokens << '\n';

    divider("Postfix");
    PostFix postFix(tokens);
    postFix.postfix();
    Deque<Token> postfixTokens = postFix.getPostfixTokens();
    std::cout << postfixTokens << '\n';

    divider("Variables");
    Parser parser(postfixTokens);
    Expression expression = parser.parse();
    for(size_t i = 0; i < expression.getVariablesSize(); ++i) {
        expression.setVariableValue(i,
                        static_cast<double>(randomLong(-10,10)));
        std::cout << expression.getVariableName(i) << " = "
                  << expression.getVariableValue(i) << '\n';
    }

    divider("Evaluation");
    std::cout << expression.evaluate() << '\n';

    divider("Tree");
    expression.printTree();
}
