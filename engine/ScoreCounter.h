#ifndef GAME_SCORECOUNTER_H
#define GAME_SCORECOUNTER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class ScoreCounter {
private:
    static sf::Font font;
    static sf::Text textField;
    static unsigned score;


public:
    static void init() {
        ScoreCounter::font.loadFromFile("../assets/PixelOperator8.ttf");
        ScoreCounter::textField = sf::Text("Score: 0", font);

        ScoreCounter::textField.setPosition(0, 0);
        ScoreCounter::textField.setCharacterSize(30);
        ScoreCounter::textField.setFillColor(sf::Color::White);
    }

    static void draw(sf::RenderWindow &window) {
        window.draw(ScoreCounter::textField);
    }

    static void increaseScore() {
        ScoreCounter::score++;
        ScoreCounter::textField.setString("Score: " + std::to_string(ScoreCounter::score));
        std::cout << "current score " << ScoreCounter::score << std::endl;
    }

};


sf::Font ScoreCounter::font;
sf::Text ScoreCounter::textField;
unsigned ScoreCounter::score = 0;

#endif //GAME_SCORECOUNTER_H
