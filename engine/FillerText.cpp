#include "includes/FillerText.h"
#include "includes/Context.h"
#include <iostream>

short FillerText::getTypeID() {
    return 6;
}

FillerText::FillerText(const Context &c) {
    if (!font.loadFromFile("../assets/PixelOperator8.ttf")) {
        std::cout << "Failed to load font ../assets/PixelOperator8.ttf" << std::endl;
    }
    text.setString("Game Over");
    text.setFont(font);
    text.setPosition((c.screenWidth - text.getLocalBounds().width) / 2, 
                     (c.screenHeight - text.getLocalBounds().height) / 2);
}

void FillerText::draw(sf::RenderWindow &window) {
    window.clear(sf::Color::Black);
    window.draw(text);
}

void FillerText::update(Context &context) {
    // empty
}