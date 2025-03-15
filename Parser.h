#ifndef INC_8_7_58REWRITE_PARSER_H
#define INC_8_7_58REWRITE_PARSER_H


#include <vector>

#include "Deque.h"
#include "Expression.h"
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

    VariableNode* newVariableNode(const Token& var);
    BinaryOperatorNode* newBinaryOperatorNode(const Token& bop);
    UnaryOperatorNode* newUnaryOperatorNode(const Token& bop);
public:
    Parser(const Deque<Token>& Postfix) : postfix(Postfix), stack(), variables() {}
    void reset(const Deque<Token>& Postfix) {
        postfix = Postfix;
        stack = Deque<ExpressionNode*>();
        variables = std::vector<VariableNode*>();
    }
    Expression parse();
};


#endif
