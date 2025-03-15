#include "Parser.h"


VariableNode *Parser::newVariableNode(const Token &var) {
    for(size_t i = 0; i < variables.size(); ++i) {
        if(var.getValue() == variables[i]->getName()) {
            return variables[i];
        }
    }
    variables.push_back(new VariableNode(postfix.front().getValue()));
    return variables.back();
}

BinaryOperatorNode *Parser::newBinaryOperatorNode(const Token &bop) {
    BinaryOperatorNode* newNode = new BinaryOperatorNode(bop.getValue());
    newNode->setR(stack.back());
    stack.pop_back();
    newNode->setL(stack.back());
    stack.pop_back();
    return newNode;
}

UnaryOperatorNode *Parser::newUnaryOperatorNode(const Token &bop) {
    UnaryOperatorNode* newNode = new UnaryOperatorNode(bop.getValue());
    newNode->set(stack.back());
    stack.pop_back();
    return newNode;
}

Expression Parser::parse() {
    while(!postfix.empty()) {
        ExpressionNode* newNode;
        if(numNext()) {
            newNode = new ConstantNode(std::stod(postfix.front().getValue()));
        } else if(varNext()) {
            newNode = newVariableNode(postfix.front());
        } else if(bopNext()) {
            newNode = newBinaryOperatorNode(postfix.front());
        } else if(uopNext()) {
            newNode = newUnaryOperatorNode(postfix.front());
        }
        stack.push_back(newNode);
        postfix.pop_front();
    }
    return {stack.front(), variables};
}
