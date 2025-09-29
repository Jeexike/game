#include "includes/Tower.h"
#include "includes/Context.h"
#include "includes/EntityHolder.h"
#include <iostream>
#include <functional>
#include <utility>

short Tower::getTypeID() {
    return 3;
}

Tower::Tower(const Context &ctx, std::function<void()> deathCallback) : onDeath(std::move(deathCallback)) {
    bottomLayer.setSize({100, 20});
    bottomLayer.setFillColor(sf::Color::White);
    topLayer.setSize({100, 20});
    topLayer.setFillColor(sf::Color::Green);
    width = 100;
    height = 100;
    shape.setSize({width, height});
    health = 1000;
    if (!texture.loadFromFile("../assets/sprites/chest.png")) {
        std::cout << "couldn't load chest texture" << std::endl;
        shape.setFillColor(sf::Color::White);
        shape.setOutlineThickness(1);
        shape.setOutlineColor(sf::Color::Black);
    } else {
        shape.setTexture(&texture);
    }
    x = (ctx.screenWidth - 100) / 2;
    y = (ctx.screenHeight - 100) / 2;
    shape.setPosition(x, y);
    bottomLayer.setPosition(x, y + 120);
    topLayer.setPosition(x, y + 120);
}

void Tower::draw(sf::RenderWindow &window) {
    window.draw(bottomLayer);
    window.draw(topLayer);
    window.draw(shape);
}

void Tower::update(Context &context) {
    (void)context;
}

void Tower::takeDamage(unsigned short amount, Context &context) {
    (void)context;
    if (health <= amount) {
        health = 0;
        topLayer.setSize({0, 20});
        std::cout << "Game Over" << std::endl;
        onDeath();
        return;
    }
    health -= amount;
    topLayer.setSize({100 * ((float) health / 1000), 20});
}