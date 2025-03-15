#include "PostFix.h"


bool PostFix::shouldPopForOp(Token op) {
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

Associativity PostFix::associativity(Token op) {
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
    return LEFT;
}

short PostFix::precedence(Token op) {
    if(op.getValue() == "+") {
        return 1;
    } else if(op.getValue()== "-") {
        if(op.getType() == UNARY_OPERATOR) {
            return 2;
        } else {
            return 1;
        }
    } else if(op.getValue() == "*") {
        return 2;
    } else if(op.getValue() == "/") {
        return 2;
    } else if(op.getValue() == "%") {
        return 2;
    } else if(op.getValue() == "^") {
        return 3;
    }
    return 0;
}

void PostFix::postfix() {
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
