#ifndef GAME_FILLERTEXT_H
#define GAME_FILLERTEXT_H


#include "AbstractEntity.h"
#include <iostream>
#include "Context.h"
#include <SFML/Graphics.hpp>

class FillerText : public AbstractEntity {
private:
    sf::Text text;
    sf::Font font;

public:
    short getTypeID() override {
        return 6;
    }

    explicit FillerText(const Context &c) {
        font.loadFromFile("../assets/PixelOperator8.ttf");
        text.setString("Game Over");
        text.setFont(font);
        text.setPosition((c.screenWidth - text.getLocalBounds().width) / 2, (c.screenHeight - text.getLocalBounds().height) / 2);
    }

    void draw(sf::RenderWindow &window) override {
        window.clear(sf::Color::Black);
        window.draw(text);
    }

    void update(Context &context) override {
    }


    ~FillerText() override = default;

};


#endif //GAME_FILLERTEXT_H
