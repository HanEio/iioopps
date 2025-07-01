#ifndef _SHUDU_COLOR_H_
#define _SHUDU_COLOR_H_
#include <iostream>

namespace Color {
    enum Code {
        FG_RED = 31, FG_GREEN = 32, FG_BLUE = 34, FG_DEFAULT = 39,
        BG_BLUE = 44, BG_YELLOW = 43, BG_DEFAULT = 49,
        BOLD = 1, RESET = 0
    };
    class Modifier {
        Code code;
    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream& operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
}
#endif