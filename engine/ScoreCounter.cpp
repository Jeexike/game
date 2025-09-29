#include "includes/ScoreCounter.h"
#include <iostream>

sf::Font ScoreCounter::font;
sf::Text ScoreCounter::textField;
unsigned ScoreCounter::score = 0;

void ScoreCounter::init() {
    if (!ScoreCounter::font.loadFromFile("../assets/PixelOperator8.ttf")) {
        std::cout << "Failed to load font ../assets/PixelOperator8.ttf" << std::endl;
    }
    ScoreCounter::textField = sf::Text("Score: 0", font);

    ScoreCounter::textField.setPosition(0, 0);
    ScoreCounter::textField.setCharacterSize(30);
    ScoreCounter::textField.setFillColor(sf::Color::White);
}

void ScoreCounter::draw(sf::RenderWindow &window) {
    window.draw(ScoreCounter::textField);
}

void ScoreCounter::increaseScore() {
    ScoreCounter::score++;
    ScoreCounter::textField.setString("Score: " + std::to_string(ScoreCounter::score));
    std::cout << "current score " << ScoreCounter::score << std::endl;
}