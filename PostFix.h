#ifndef INC_8_7_58REWRITE_POSTFIX_H
#define INC_8_7_58REWRITE_POSTFIX_H


#include "Deque.h"
#include "Token.h"
#include "Lexer.h"

enum Associativity {LEFT, RIGHT};

class PostFix {
private:
    Deque<Token> infix;
    Deque<Token> opStack;
    Deque<Token> postfixTokens;

    bool numNext() {
        return infix.front().getType() == CONSTANT;
    }
    bool varNext() {
        return infix.front().getType() == VARIABLE;
    }
    bool oparNext() {
        return infix.front().getType() == PARENTHESES &&
               infix.front().getValue() == "(";
    }
    bool cparNext() {
        return infix.front().getType() == PARENTHESES &&
               infix.front().getValue() == ")";
    }
    bool opNext() {
        return infix.front().getType() == BINARY_OPERATOR ||
               infix.front().getType() == UNARY_OPERATOR;
    }

    bool shouldPopForOp(Token op);

    Associativity associativity(Token op);

    short precedence(Token op);
public:
    PostFix(const Deque<Token>& Infix) :
    infix(Infix), opStack(), postfixTokens() {}
    void reset(const Deque<Token>& Infix) {
        infix = Infix;
        opStack = Deque<Token>();
        postfixTokens = Deque<Token>();
    }
    void postfix();
    Deque<Token> getPostfixTokens() const {
        return postfixTokens;
    }
};



#endif
