#include "includes/MainMenu.h"
#include <iostream>

MainMenu::MainMenu(unsigned int width, unsigned int height)
    : windowWidth(width), windowHeight(height) {

    if (!font.loadFromFile("../assets/PixelOperator8.ttf")) {
        std::cerr << "Error loading font 'PixelOperator8.ttf' for menu!" << std::endl;
    }

    titleText.setFont(font);
    titleText.setString("SFML Game");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color::White);
    titleText.setStyle(sf::Text::Bold);

    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.left + titleBounds.width / 2.0f, titleBounds.top + titleBounds.height / 2.0f);
    titleText.setPosition(windowWidth / 2.0f, windowHeight * 0.2f);

    startText.setFont(font);
    startText.setString("Start Game");
    startText.setCharacterSize(30);
    startText.setFillColor(sf::Color::White);

    sf::FloatRect startBounds = startText.getLocalBounds();
    startText.setOrigin(startBounds.left + startBounds.width / 2.0f, startBounds.top + startBounds.height / 2.0f);
    startText.setPosition(windowWidth / 2.0f, windowHeight * 0.40f);

    startButton.setSize(sf::Vector2f(startBounds.width + 40, startBounds.height + 20));
    startButton.setFillColor(idleColor);
    startButton.setOutlineColor(sf::Color::White);
    startButton.setOutlineThickness(2);
    startButton.setOrigin(startButton.getSize().x / 2.0f, startButton.getSize().y / 2.0f);
    startButton.setPosition(windowWidth / 2.0f, windowHeight * 0.40f);


    settingsText.setFont(font);
    settingsText.setString("Settings");
    settingsText.setCharacterSize(30);
    settingsText.setFillColor(sf::Color::White);

    sf::FloatRect settingsBounds = settingsText.getLocalBounds();
    settingsText.setOrigin(settingsBounds.left + settingsBounds.width / 2.0f, settingsBounds.top + settingsBounds.height / 2.0f);
    settingsText.setPosition(windowWidth / 2.0f, windowHeight * 0.50f);

    settingsButton.setSize(sf::Vector2f(settingsBounds.width + 40, settingsBounds.height + 20));
    settingsButton.setFillColor(idleColor);
    settingsButton.setOutlineColor(sf::Color::White);
    settingsButton.setOutlineThickness(2);
    settingsButton.setOrigin(settingsButton.getSize().x / 2.0f, settingsButton.getSize().y / 2.0f);
    settingsButton.setPosition(windowWidth / 2.0f, windowHeight * 0.50f);

    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(30);
    exitText.setFillColor(sf::Color::White);

    sf::FloatRect exitBounds = exitText.getLocalBounds();
    exitText.setOrigin(exitBounds.left + exitBounds.width / 2.0f, exitBounds.top + exitBounds.height / 2.0f);
    exitText.setPosition(windowWidth / 2.0f, windowHeight * 0.60f);

    exitButton.setSize(sf::Vector2f(exitBounds.width + 40, exitBounds.height + 20));
    exitButton.setFillColor(idleColor);
    exitButton.setOutlineColor(sf::Color::White);
    exitButton.setOutlineThickness(2);
    exitButton.setOrigin(exitButton.getSize().x / 2.0f, exitButton.getSize().y / 2.0f);
    exitButton.setPosition(windowWidth / 2.0f, windowHeight * 0.60f);
}

void MainMenu::setCallbacks(std::function<void()> startCallback, std::function<void()> settingsCallback, std::function<void()> exitCallback) {
    onStartPressed = startCallback;
    onSettingsPressed = settingsCallback;
    onExitPressed = exitCallback;
}

void MainMenu::handleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            if (onExitPressed) onExitPressed();
            return;
        }
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

            if (startButton.getGlobalBounds().contains(mousePos) && onStartPressed) {
                onStartPressed();
            }
            if (settingsButton.getGlobalBounds().contains(mousePos) && onSettingsPressed) {
                onSettingsPressed();
            }
            if (exitButton.getGlobalBounds().contains(mousePos) && onExitPressed) {
                onExitPressed();
            }
        }
    }
}

void MainMenu::update(sf::RenderWindow& window) {
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

    if (startButton.getGlobalBounds().contains(mousePos)) {
        startButton.setFillColor(hoverColor);
    } else {
        startButton.setFillColor(idleColor);
    }

    if (settingsButton.getGlobalBounds().contains(mousePos)) {
        settingsButton.setFillColor(hoverColor);
    } else {
        settingsButton.setFillColor(idleColor);
    }

    if (exitButton.getGlobalBounds().contains(mousePos)) {
        exitButton.setFillColor(hoverColor);
    } else {
        exitButton.setFillColor(idleColor);
    }
}

void MainMenu::draw(sf::RenderWindow& window) const {
    window.clear();
    window.draw(titleText);
    window.draw(startButton);
    window.draw(startText);
    window.draw(settingsButton);
    window.draw(settingsText);
    window.draw(exitButton);
    window.draw(exitText);
    window.display();
}

bool MainMenu::isMouseOver(const sf::RectangleShape& button, sf::RenderWindow& window) const {
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
    return button.getGlobalBounds().contains(mousePos);
}