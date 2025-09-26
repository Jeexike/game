#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include <iostream>

class EntityHolder; // circular dependency

class Context {
public:
    unsigned screenWidth = 0;
    unsigned screenHeight = 0;
    bool rightKeyPressed = false;
    bool leftKeyPressed = false;
    bool upKeyPressed = false;
    bool downKeyPressed = false;
    sf::Vector2i lastClickPos = {0, 0};
    bool lastClickProcessed = true;

    EntityHolder &holder;


    Context(unsigned w, unsigned h, EntityHolder &eh) : holder(eh) {
        screenHeight = h;
        screenWidth = w;
    }

    std::ostream &operator<<(std::ostream &os) const {
        os << "r=" << rightKeyPressed << "l=" << leftKeyPressed << "u=" << upKeyPressed << "d=" << downKeyPressed;
        return os;
    }

    Context(const Context &c) = delete;

    Context &operator=(const Context &c) = delete;


};


#endif //GAME_CONTEXT_H
