#include "line.h"

bool Line::operator!=(const Line &l) {
    return !(*this == l);
}

bool Line::operator==(const Line &l) {
    return p1 == l.p1 && p2 == l.p2;
}