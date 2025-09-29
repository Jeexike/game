#ifndef GAME_SCORECOUNTER_H
#define GAME_SCORECOUNTER_H

#include <SFML/Graphics.hpp>

class ScoreCounter {
private:
    static sf::Font font;
    static sf::Text textField;
    static unsigned score;

public:
    static void init();
    static void draw(sf::RenderWindow &window);
    static void increaseScore();
};

#endif // GAME_SCORECOUNTER_H