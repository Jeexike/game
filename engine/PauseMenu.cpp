#include "includes/PauseMenu.h"
#include <iostream>

PauseMenu::PauseMenu(unsigned int width, unsigned int height)
    : windowWidth(width), windowHeight(height) {

    if (!font.loadFromFile("../assets/PixelOperator8.ttf")) {
        std::cerr << "Error loading font 'PixelOperator8.ttf' for pause menu!" << std::endl;
    }

    titleText.setFont(font);
    titleText.setString("PAUSED");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color::White);
    titleText.setStyle(sf::Text::Bold);

    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.left + titleBounds.width / 2.0f, titleBounds.top + titleBounds.height / 2.0f);
    titleText.setPosition(windowWidth / 2.0f, windowHeight * 0.2f);

    continueText.setFont(font);
    continueText.setString("Continue");
    continueText.setCharacterSize(30);
    continueText.setFillColor(sf::Color::White);

    sf::FloatRect continueBounds = continueText.getLocalBounds();
    continueText.setOrigin(continueBounds.left + continueBounds.width / 2.0f, continueBounds.top + continueBounds.height / 2.0f);
    continueText.setPosition(windowWidth / 2.0f, windowHeight * 0.40f);

    continueButton.setSize(sf::Vector2f(continueBounds.width + 40, continueBounds.height + 20));
    continueButton.setFillColor(idleColor);
    continueButton.setOutlineColor(sf::Color::White);
    continueButton.setOutlineThickness(2);
    continueButton.setOrigin(continueButton.getSize().x / 2.0f, continueButton.getSize().y / 2.0f);
    continueButton.setPosition(windowWidth / 2.0f, windowHeight * 0.40f);

    menuText.setFont(font);
    menuText.setString("Main Menu");
    menuText.setCharacterSize(30);
    menuText.setFillColor(sf::Color::White);

    sf::FloatRect menuBounds = menuText.getLocalBounds();
    menuText.setOrigin(menuBounds.left + menuBounds.width / 2.0f, menuBounds.top + menuBounds.height / 2.0f);
    menuText.setPosition(windowWidth / 2.0f, windowHeight * 0.50f);

    menuButton.setSize(sf::Vector2f(menuBounds.width + 40, menuBounds.height + 20));
    menuButton.setFillColor(idleColor);
    menuButton.setOutlineColor(sf::Color::White);
    menuButton.setOutlineThickness(2);
    menuButton.setOrigin(menuButton.getSize().x / 2.0f, menuButton.getSize().y / 2.0f);
    menuButton.setPosition(windowWidth / 2.0f, windowHeight * 0.50f);

    exitText.setFont(font);
    exitText.setString("Exit Game");
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

void PauseMenu::setCallbacks(std::function<void()> continueCallback,
                             std::function<void()> menuCallback,
                             std::function<void()> exitCallback) {
    onContinuePressed = continueCallback;
    onMenuPressed = menuCallback;
    onExitPressed = exitCallback;
}

void PauseMenu::handleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            if (onExitPressed) onExitPressed();
            return;
        }
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

            if (continueButton.getGlobalBounds().contains(mousePos) && onContinuePressed) {
                onContinuePressed();
            }
            if (menuButton.getGlobalBounds().contains(mousePos) && onMenuPressed) {
                onMenuPressed();
            }
            if (exitButton.getGlobalBounds().contains(mousePos) && onExitPressed) {
                onExitPressed();
            }
        }
    }
}

void PauseMenu::update(sf::RenderWindow& window) {
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

    if (continueButton.getGlobalBounds().contains(mousePos)) {
        continueButton.setFillColor(hoverColor);
    } else {
        continueButton.setFillColor(idleColor);
    }
    if (menuButton.getGlobalBounds().contains(mousePos)) {
        menuButton.setFillColor(hoverColor);
    } else {
        menuButton.setFillColor(idleColor);
    }
    if (exitButton.getGlobalBounds().contains(mousePos)) {
        exitButton.setFillColor(hoverColor);
    } else {
        exitButton.setFillColor(idleColor);
    }
}

void PauseMenu::draw(sf::RenderWindow& window, bool clearAndDisplay) const {
    if (clearAndDisplay) {
        window.clear();
    }
    window.draw(titleText);
    window.draw(continueButton);
    window.draw(continueText);
    window.draw(menuButton);
    window.draw(menuText);
    window.draw(exitButton);
    window.draw(exitText);
    if (clearAndDisplay) {
        window.display();
    }
}