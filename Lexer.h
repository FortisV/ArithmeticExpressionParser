#ifndef INC_8_7_58REWRITE_LEXER_H
#define INC_8_7_58REWRITE_LEXER_H

#include <string>
#include "Token.h"
#include "Deque.h"

class Lexer {
private:
    std::string str;
    size_t pos;
    bool prevOp;
    Deque<Token> tokens;

    void consumeWS() {
        while(isspace(str[pos])) {
            ++pos;
        }
    }

    bool numNext() {
        return isdigit(str[pos]);
    }
    bool parNext() {
        return str[pos] == '(' || str[pos] == ')';
    }
    bool opNext() {
        return str[pos] == '+' ||
        str[pos] == '-' ||
        str[pos] == '*' ||
        str[pos] == '/' ||
        str[pos] == '%' ||
        str[pos] == '^';
    }
    bool varNext() {
        return isalpha(str[pos]);
    }
    bool wsNext() {
        return isblank(str[pos]);
    }

    static bool isnumeric(char c) {
        return isdigit(c) || c == '.';
    }

    bool done() {
        return pos == str.size();
    }

    Token lexNum() {
        size_t beg = pos;
        while(isnumeric(str[pos])) {
            pos++;
        }
        prevOp = false;
        return {CONSTANT, str.substr(beg, pos - beg)};
    }
    Token lexPar() {
        if(str.substr(pos, 1) == "(") {
            prevOp = true;
        } else {
            prevOp = false;
        }
        return {PARENTHESES, str.substr(pos++, 1)};
    }
    Token lexOp() {
        if(prevOp) {
            prevOp = true;
            return {UNARY_OPERATOR, str.substr(pos++, 1)};
        } else {
            prevOp = true;
            return {BINARY_OPERATOR, str.substr(pos++, 1)};
        }
    }
    Token lexVar() {
        size_t beg = pos;
        while(!done() && !opNext() && ! parNext() && !wsNext()) {
            pos++;
        }
        prevOp = false;
        return {VARIABLE, str.substr(beg, pos - beg)};
    }

public:
    Lexer(const std::string& Str) :
    str(Str), pos(0), prevOp(true), tokens() {}
    void reset(const std::string& Str) {
        str = Str;
        pos = 0;
        prevOp = true;
    }
    void tokenize() {
        while(!done()) {
            consumeWS();
            if(numNext()) {
                tokens.push_back(lexNum());
            } else if(parNext()) {
                tokens.push_back(lexPar());
            } else if(opNext()) {
                tokens.push_back(lexOp());
            } else if(varNext()) {
                tokens.push_back(lexVar());
            }
        }
    }
    Deque<Token> getTokens() const {
        return tokens;
    }
};

#endif
