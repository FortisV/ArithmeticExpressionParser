#include "ConDec.h"

#include <iostream>
#include <string>

using namespace std;

void divider() {
    cout << string(DIV_CHAR, CONSOLE_WIDTH);
}
void divider(const string& message) {
    bool odd = message.size() % 2;
    size_t space = (CONSOLE_WIDTH - message.size()) / 2;
    cout << string(space + odd, DIV_CHAR)
         << message << string(space, DIV_CHAR)
         << '\n';
}

void banner() {
    cout << BAN_CORN_CHAR << string(CONSOLE_WIDTH - 2, BAN_HORZ_CHAR)
         << BAN_CORN_CHAR << '\n';
    cout << BAN_VERT_CHAR << string(CONSOLE_WIDTH - 2, BAN_FILL_CHAR)
         << BAN_VERT_CHAR << '\n';
    cout << BAN_CORN_CHAR << string(CONSOLE_WIDTH - 2, BAN_HORZ_CHAR)
         << BAN_CORN_CHAR << '\n';
}
void banner(const string& message) {
    bool odd = message.size() % 2;
    size_t space = (CONSOLE_WIDTH - message.size() - 2) / 2;
    cout << BAN_CORN_CHAR << string(CONSOLE_WIDTH - 2, BAN_HORZ_CHAR)
         << BAN_CORN_CHAR << '\n';
    cout << BAN_VERT_CHAR
         << string(space + odd, BAN_FILL_CHAR)
         << message << string(space, BAN_FILL_CHAR)
         << BAN_VERT_CHAR << '\n';
    cout << BAN_CORN_CHAR << string(CONSOLE_WIDTH - 2, BAN_HORZ_CHAR)
         << BAN_CORN_CHAR << '\n';
}