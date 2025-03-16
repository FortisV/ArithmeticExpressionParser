#ifndef INC_8_7_58REWRITE_TOKEN_H
#define INC_8_7_58REWRITE_TOKEN_H


#include <string>

enum TokenType {NONE, CONSTANT, VARIABLE, BINARY_OPERATOR,
        UNARY_OPERATOR, PARENTHESES};

class Token {
private:
    TokenType type;
    std::string value;
public:
    Token() : type(NONE), value() {}
    Token(TokenType Type) : type(Type), value() {}
    Token(TokenType Type, std::string Value) :
    type(Type), value(Value) {}

    TokenType getType() const {
        return type;
    }
    std::string getValue() const {
        return value;
    }
    std::ostream& print(std::ostream& os = std::cout) const {
        return os << value;
    }
    friend std::ostream& operator<<(std::ostream& os,
            const Token& token) {
        return token.print(os);
    }
};


#endif
