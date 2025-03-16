#ifndef INC_8_7_58REWRITE_EXPRESSIONNODE_H
#define INC_8_7_58REWRITE_EXPRESSIONNODE_H


#include <iostream>
#include <cmath>

class ExpressionNode {
public:
    virtual ~ExpressionNode() {}
    virtual double getValue() const {
        return 0;
    }
    virtual std::ostream& print(std::ostream& os) const {
        return os;
    }
    friend std::ostream& operator<<(std::ostream& os,
            const ExpressionNode& en) {
        return en.print(os);
    }
};

class ConstantNode : public ExpressionNode {
private:
    double value;
public:
    ConstantNode(double Value) : value(Value) {}
    double getValue() const override {
        return value;
    }
    std::ostream & print(std::ostream &os) const override {
        return os << value;
    }
};

class VariableNode : public ExpressionNode {
private:
    double value;
    std::string name;
public:
    VariableNode(const std::string& Name) : value(0), name(Name) {}
    double getValue() const override {
        return value;
    }
    void setValue(double Value) {
        value = Value;
    }
    std::string getName() const {
        return name;
    }
    std::ostream & print(std::ostream &os) const override {
        return os << name;
    }
};

class UnaryOperatorNode : public ExpressionNode {
private:
    std::string operation;
    ExpressionNode* operand;
public:
    UnaryOperatorNode(const std::string& Operation) :
    operation(Operation), operand(nullptr) {}
    UnaryOperatorNode(const UnaryOperatorNode& unaryOperatorNode) :
    operation(unaryOperatorNode.operation),
    operand(unaryOperatorNode.operand) {}
    UnaryOperatorNode& operator=(const UnaryOperatorNode&
            unaryOperatorNode) {
        if(this != &unaryOperatorNode) {
            delete operand;
            operation = unaryOperatorNode.operation;
            operand = unaryOperatorNode.operand;
        }
        return *this;
    }
    ~UnaryOperatorNode() {
        if(!dynamic_cast<VariableNode*>(operand)) {
            delete operand;
        }
    }
    double getValue() const override {
        if(operation == "-") {
            return -operand->getValue();
        }
        return 0;
    }
    void set(ExpressionNode* Operand) {
        operand = Operand;
    }
    ExpressionNode* get() {
        return operand;
    }
    std::ostream & print(std::ostream &os) const override {
        return os << operation;
    }
};

class BinaryOperatorNode : public ExpressionNode {
private:
    std::string operation;
    ExpressionNode* lOperand;
    ExpressionNode* rOperand;
public:
    BinaryOperatorNode(const std::string& Operation) :
    operation(Operation), lOperand(nullptr), rOperand(nullptr) {}
    BinaryOperatorNode(const BinaryOperatorNode& binaryOperatorNode) :
    operation(binaryOperatorNode.operation),
    lOperand(binaryOperatorNode.lOperand),
    rOperand(binaryOperatorNode.rOperand) {}
    BinaryOperatorNode& operator=(const BinaryOperatorNode&
            binaryOperatorNode) {
        if(this != &binaryOperatorNode) {
            delete lOperand;
            delete rOperand;
            operation = binaryOperatorNode.operation;
            lOperand = binaryOperatorNode.lOperand;
            rOperand = binaryOperatorNode.rOperand;
        }
        return *this;
    }
    ~BinaryOperatorNode() {
        if(!dynamic_cast<VariableNode*>(lOperand)) {
            delete lOperand;
        }
        if(!dynamic_cast<VariableNode*>(rOperand)) {
            delete rOperand;
        }
    }
    double getValue() const override {
        if(operation == "+") {
            return lOperand->getValue() + rOperand->getValue();
        } else if(operation == "-") {
            return lOperand->getValue() - rOperand->getValue();
        } else if(operation == "*") {
            return lOperand->getValue() * rOperand->getValue();
        } else if(operation == "/") {
            return lOperand->getValue() / rOperand->getValue();
        } else if(operation == "%") {
            return fmod(lOperand->getValue(), rOperand->getValue());
        } else if(operation == "^") {
            return pow(lOperand->getValue(), rOperand->getValue());
        }
        else return 0;
    }
    void setL(ExpressionNode* LOperand) {
        lOperand = LOperand;
    }
    void setR(ExpressionNode* ROperand) {
        rOperand = ROperand;
    }
    ExpressionNode* getL() {
        return lOperand;
    }
    ExpressionNode* getR() {
        return rOperand;
    }
    std::ostream & print(std::ostream &os) const override {
        return os << operation;
    }
};


#endif
