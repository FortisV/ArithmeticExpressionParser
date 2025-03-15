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
                         const std::string& corner);

inline void customPrintPreorder(ExpressionNode* root,
                                bool space,
                                const std::string& blank,
                                const std::string& line,
                                const std::string& branch,
                                const std::string& corner) {
    std::vector<bool> ln;
    customPrintPreorder(root, ln, space, blank, line, branch, corner);
}

inline void printPreorder(ExpressionNode* root) {
    customPrintPreorder(root, false, BLANK, LINE, BRANCH, CORNER);
}

inline void printPreorderFancy(ExpressionNode* root) {
    customPrintPreorder(root, true, FANCY_BLANK, FANCY_LINE,
                        FANCY_BRANCH, FANCY_CORNER);
}


#endif
