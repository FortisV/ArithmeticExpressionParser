#ifndef INC_8_7_58REWRITE_EXPRESSIONTREEPRINT_H
#define INC_8_7_58REWRITE_EXPRESSIONTREEPRINT_H


#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "ExpressionNode.h"

const std::string FANCY_BLANK =  "  ";
const std::string FANCY_LINE =   "║ ";
const std::string FANCY_BRANCH = "╠═";
const std::string FANCY_CORNER = "╚═";
const std::string BLANK =  "  ";
const std::string LINE =   "| ";
const std::string BRANCH = "+-";
const std::string CORNER = "+-";
const char WHITESPACE = ' ';

void customPrintPreorder(ExpressionNode* root,
                         std::vector<bool>& ln,
                         bool space,
                         const std::string& blank,
                         const std::string& line,
                         const std::string& branch,
                         const std::string& corner) {
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
        ExpressionNode* next = dynamic_cast<UnaryOperatorNode*>(root)->get();
        ln.push_back(false);
        customPrintPreorder(next, ln, space, blank, line, branch, corner);
        ln.pop_back();
    } else if(dynamic_cast<BinaryOperatorNode*>(root)) {
        ExpressionNode* lnext = dynamic_cast<BinaryOperatorNode*>(root)->getL();
        ExpressionNode* rnext = dynamic_cast<BinaryOperatorNode*>(root)->getR();
        ln.push_back(true);
        customPrintPreorder(lnext, ln, space, blank, line, branch, corner);
        ln.pop_back();
        ln.push_back(false);
        customPrintPreorder(rnext, ln, space, blank, line, branch, corner);
        ln.pop_back();
    }
}

void customPrintPreorder(ExpressionNode* root,
                         bool space,
                         const std::string& blank,
                         const std::string& line,
                         const std::string& branch,
                         const std::string& corner) {
    std::vector<bool> ln;
    customPrintPreorder(root, ln, space, blank, line, branch, corner);
}

void printPreorder(ExpressionNode* root) {
    customPrintPreorder(root, false, BLANK, LINE, BRANCH, CORNER);
}

void printPreorderFancy(ExpressionNode* root) {
    customPrintPreorder(root, true, FANCY_BLANK, FANCY_LINE,
                        FANCY_BRANCH, FANCY_CORNER);
}


#endif
