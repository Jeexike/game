#ifndef GAME_PAUSEMENU_H
#define GAME_PAUSEMENU_H

#include <SFML/Graphics.hpp>
#include <functional>

class PauseMenu {
private:
    sf::Font font;
    sf::Text titleText;
    sf::Text continueText;
    sf::Text menuText;
    sf::Text exitText;

    sf::RectangleShape continueButton;
    sf::RectangleShape menuButton;
    sf::RectangleShape exitButton;

    sf::Color idleColor = sf::Color(50, 50, 50, 200);
    sf::Color hoverColor = sf::Color(100, 100, 100, 200);

    unsigned int windowWidth;
    unsigned int windowHeight;

    std::function<void()> onContinuePressed;
    std::function<void()> onMenuPressed;
    std::function<void()> onExitPressed;

public:
    PauseMenu(unsigned int width, unsigned int height);

    void setCallbacks(std::function<void()> continueCallback,
                      std::function<void()> menuCallback,
                      std::function<void()> exitCallback);

    void handleInput(sf::RenderWindow& window);
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window, bool clearAndDisplay = false) const;
};

#endif