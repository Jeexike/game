#ifndef GAME_MAINMENU_H
#define GAME_MAINMENU_H

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>
#include "GameState.h"

class MainMenu {
private:
    sf::Font font;
    sf::Text titleText;
    sf::Text startText;
    sf::Text settingsText;
    sf::Text exitText;

    sf::RectangleShape startButton;
    sf::RectangleShape settingsButton;
    sf::RectangleShape exitButton;

    sf::Color idleColor = sf::Color(50, 50, 50, 200);
    sf::Color hoverColor = sf::Color(100, 100, 100, 200);

    unsigned int windowWidth;
    unsigned int windowHeight;

    std::function<void()> onStartPressed;
    std::function<void()> onSettingsPressed;
    std::function<void()> onExitPressed;

    bool isMouseOver(const sf::RectangleShape& button, sf::RenderWindow& window) const;

public:
    MainMenu(unsigned int width, unsigned int height);
    ~MainMenu() = default;

    void setCallbacks(std::function<void()> startCallback, std::function<void()> settingsCallback, std::function<void()> exitCallback);

    void handleInput(sf::RenderWindow& window);
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window) const;
};

#endif // GAME_MAINMENU_H