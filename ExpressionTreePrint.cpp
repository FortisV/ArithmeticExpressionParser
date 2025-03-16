#include "ExpressionTreePrint.h"


void customPrintPreorder(ExpressionNode *root,
                         std::vector<bool> &ln,
                         bool space,
                         const std::string &blank,
                         const std::string &line,
                         const std::string &branch,
                         const std::string &corner) {
    std::string whitespace;
    if(space) {
        whitespace = WHITESPACE;
    }
    if(!ln.empty()) {
        for(size_t i = 0; i < ln.size() - 1; ++i) {
            if(ln[i]) {
                std::cout << line << whitespace;
            } else {
                std::cout << blank << whitespace;
            }
        }
        if(ln.back()) {
            std::cout << branch << whitespace;
        } else {
            std::cout << corner << whitespace;
        }
    }
    std::cout << *root << '\n';
    if(space) {
        if(!ln.empty()) {
            for(size_t i = 0; i < ln.size(); ++i) {
                if(ln[i]) {
                    std::cout << line << whitespace;
                } else {
                    std::cout << blank << whitespace;
                }
            }
        }
        std::cout << '\n';
    }

    if(dynamic_cast<UnaryOperatorNode*>(root)) {
        ExpressionNode* next =
                dynamic_cast<UnaryOperatorNode*>(root)->get();
        ln.push_back(false);
        customPrintPreorder(next,
                            ln,
                            space,
                            blank,
                            line,
                            branch,
                            corner);
        ln.pop_back();
    } else if(dynamic_cast<BinaryOperatorNode*>(root)) {
        ExpressionNode* lNext =
                dynamic_cast<BinaryOperatorNode*>(root)->getL();
        ExpressionNode* rNext =
                dynamic_cast<BinaryOperatorNode*>(root)->getR();
        ln.push_back(true);
        customPrintPreorder(lNext,
                            ln,
                            space,
                            blank,
                            line,
                            branch,
                            corner);
        ln.pop_back();
        ln.push_back(false);
        customPrintPreorder(rNext,
                            ln,
                            space,
                            blank,
                            line,
                            branch,
                            corner);
        ln.pop_back();
    }
}
