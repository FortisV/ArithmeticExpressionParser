#ifndef CONDEC_CONDEC_H
#define CONDEC_CONDEC_H


#include <string>

const size_t CONSOLE_WIDTH = 80;
const char DIV_CHAR = '-';
const char BAN_CORN_CHAR = '@';
const char BAN_VERT_CHAR = '|';
const char BAN_HORZ_CHAR = '-';
const char BAN_FILL_CHAR = ' ';

void divider();
void divider(const std::string& message);

void banner();
void banner(const std::string& message);


#endif
