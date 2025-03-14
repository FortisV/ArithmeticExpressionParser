#ifndef INC_8_7_58REWRITE_PARSER_H
#define INC_8_7_58REWRITE_PARSER_H


#include "Deque.h"
#include "ExpressionNode.h"
#include "Token.h"

class Parser {
private:
    Deque<Token> postfix;
    Deque<ExpressionNode*> stack;
    std::vector<VariableNode*> variables;

    bool numNext() {
        return postfix.front().getType() == CONSTANT;
    }
    bool varNext() {
        return postfix.front().getType() == VARIABLE;
    }
    bool bopNext() {
        return postfix.front().getType() == BINARY_OPERATOR;
    }
    bool uopNext() {
        return postfix.front().getType() == UNARY_OPERATOR;
    }

    VariableNode* newVariableNode(const Token& var) {
        for(size_t i = 0; i < variables.size(); ++i) {
            if(var.getValue() == variables[i]->getName()) {
                return variables[i];
            }
        }
        variables.push_back(new VariableNode(postfix.front().getValue()));
        return variables.back();
    }
    BinaryOperatorNode* newBinaryOperatorNode(const Token& bop) {
        BinaryOperatorNode* newNode = new BinaryOperatorNode(bop.getValue());
        newNode->setR(stack.back());
        stack.pop_back();
        newNode->setL(stack.back());
        stack.pop_back();
        return newNode;
    }
    UnaryOperatorNode* newUnaryOperatorNode(const Token& bop) {
        UnaryOperatorNode* newNode = new UnaryOperatorNode(bop.getValue());
        newNode->set(stack.back());
        stack.pop_back();
        return newNode;
    }
public:
    Parser(const Deque<Token>& Postfix) : postfix(Postfix), stack(), variables() {}
    void reset(const Deque<Token>& Postfix) {
        postfix = Postfix;
        stack = Deque<ExpressionNode*>();
        variables = std::vector<VariableNode*>();
    }
    void parse() {
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
    }
    ExpressionNode* getExpressionTree() {
        return stack.front();
    }
    std::vector<VariableNode*> getVariables() {
        return variables;
    }
};


#endif
