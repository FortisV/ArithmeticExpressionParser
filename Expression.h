#ifndef INC_8_7_58REWRITE_EXPRESSION_H
#define INC_8_7_58REWRITE_EXPRESSION_H


#include <iostream>

#include "Lexer.h"
#include "Token.h"
#include "Deque.h"
#include "ExpressionNode.h"


class Expression {
private:
    std::vector<VariableNode*> variables;
    ExpressionNode* expressionNode;
public:
    static const size_t npos = -1UL;
    Expression(ExpressionNode* ExpressionNode, const std::vector<VariableNode*>& Variables) : expressionNode(ExpressionNode), variables(Variables) {}
    ~Expression() {
        delete expressionNode;
    }
    double evaluate() {
        return expressionNode->getValue();
    }
    void setVariableValue(size_t i, double value) {
        variables[i]->setValue(value);
    }
    double getVariableValue(size_t i) const {
        return variables[i]->getValue();
    }
    std::string getVariableName(size_t i) const {
        return variables[i]->getName();
    }
    size_t getVariablesSize() {
        return variables.size();
    }
    bool hasVariable(const std::string& name);
    size_t findVariable(const std::string& name);
};


#endif
