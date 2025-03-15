#include "Expression.h"


bool Expression::hasVariable(const std::string &name) {
    for(size_t i = 0; i < variables.size(); ++i) {
        if(variables[i]->getName() == name) {
            return true;
        }
    }
    return false;
}

size_t Expression::findVariable(const std::string &name) {
    for(size_t i = 0; i < variables.size(); ++i) {
        if(variables[i]->getName() == name) {
            return i;
        }
    }
    return npos;
}
