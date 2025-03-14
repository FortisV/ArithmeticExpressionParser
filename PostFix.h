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

    bool shouldPopForOp(Token op) {
        short precedenceOp = precedence(op);
        short precedenceSt = precedence(opStack.back());
        if(op.getType() == UNARY_OPERATOR) {
            return false;
        }
        if(precedenceSt < precedenceOp) {
            return false;
        } else if(precedenceSt == precedenceOp) {
            return associativity(op) == LEFT;
        } else {
            return true;
        }
    }

    Associativity associativity(Token op) {
        if(op.getValue() == "+") {
            return LEFT;
        } else if(op.getValue()== "-") {
            if(op.getType() == BINARY_OPERATOR) {
                return LEFT;
            } else {
                return RIGHT;
            }
        } else if(op.getValue() == "*") {
            return LEFT;
        } else if(op.getValue() == "/") {
            return LEFT;
        } else if(op.getValue() == "%") {
            return LEFT;
        } else if(op.getValue() == "^") {
            return RIGHT;
        }
    }

    short precedence(Token op) {
        if(op.getValue() == "+") {
            return 1;
        } else if(op.getValue()== "-") {
            return 1;
        } else if(op.getValue() == "*") {
            return 2;
        } else if(op.getValue() == "/") {
            return 2;
        } else if(op.getValue() == "%") {
            return 2;
        } else if(op.getValue() == "^") {
            return 3;
        }
    }
public:
    PostFix(const Deque<Token>& Infix) : infix(Infix), opStack(), postfixTokens() {}
    void reset(const Deque<Token>& Infix) {
        infix = Infix;
        opStack = Deque<Token>();
        postfixTokens = Deque<Token>();
    }
    void postfix() {
        while(!infix.empty()) {
            if(numNext()) {
                postfixTokens.push_back(infix.front());
                infix.pop_front();
            } else if(varNext()) {
                postfixTokens.push_back(infix.front());
                infix.pop_front();
            } else if(oparNext()) {
                opStack.push_back(infix.front());
                infix.pop_front();
            } else if(cparNext()) {
                while(!opStack.empty() && opStack.back().getType() != PARENTHESES) {
                    postfixTokens.push_back(opStack.back());
                    opStack.pop_back();
                }
                if(infix.front().getType() == PARENTHESES) {
                    opStack.pop_back();
                }
                infix.pop_front();
            } else if(opNext()) {
                while(!opStack.empty() && shouldPopForOp(infix.front())) {
                    postfixTokens.push_back(opStack.back());
                    opStack.pop_back();
                }
                opStack.push_back(infix.front());
                infix.pop_front();
            }
        }
        while(!opStack.empty()) {
            if(opStack.back().getType() != PARENTHESES) {
                postfixTokens.push_back(opStack.back());
            }
            opStack.pop_back();
        }
    }
    Deque<Token> getPostfixTokens() const {
        return postfixTokens;
    }
};



#endif
