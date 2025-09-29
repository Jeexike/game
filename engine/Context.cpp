#include "includes/Context.h"
#include "includes/EntityHolder.h"

Context::Context(unsigned w, unsigned h, EntityHolder &eh) : holder(eh) {
    screenHeight = h;
    screenWidth = w;
}

std::ostream &Context::operator<<(std::ostream &os) const {
    os << "r=" << rightKeyPressed << "l=" << leftKeyPressed << "u=" << upKeyPressed << "d=" << downKeyPressed;
    return os;
}