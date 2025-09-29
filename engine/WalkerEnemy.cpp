#include "includes/WalkerEnemy.h"
#include "includes/Context.h"
#include "includes/EntityHolder.h"
#include "includes/ScoreCounter.h"
#include <iostream>
#include <math.h>
#include <cstdlib>

short WalkerEnemy::getTypeID() {
    return 2;
}

WalkerEnemy::WalkerEnemy(const Context &c) {
    bool vertical = rand() % 2;
    bool first = rand() % 2;

    if (vertical) {
        x = (first) ? 0 : c.screenWidth;
        y = rand() % c.screenHeight;
    } else {
        x = rand() % c.screenWidth;
        y = (first) ? 0 : c.screenHeight;
    }

    health = 200;
    width = 60;
    height = 80;

    shape.setSize({width, height});
    if (!texture.loadFromFile("../assets/sprites/walker_enemy.png")) {
        std::cout << "couldn't load walker enemy texture" << std::endl;
        shape.setFillColor(sf::Color::Red);
        shape.setOutlineThickness(1);
        shape.setOutlineColor(sf::Color::Black);
    } else {
        shape.setTexture(&texture);
    }
    shape.setPosition(x, y);
}

void WalkerEnemy::draw(sf::RenderWindow &window) {
    window.draw(shape);
}

void WalkerEnemy::update(Context &context) {
    AbstractEntity &tower = context.holder.getTower();
    if (collides(tower)) {
        tower.takeDamage(damage, context);
        return;
    }

    float xDiff = tower.center().x - center().x;
    float yDiff = tower.center().y - center().y;
    float angle = atan2(yDiff, xDiff);
    angle = (angle < 0) ? angle * -1 : M_PI * 2 - angle;

    y -= sin(angle) * velocity;
    x += cos(angle) * velocity;

    shape.setPosition(x, y);
}

void WalkerEnemy::takeDamage(unsigned short amount, Context &context) {
    health -= amount;
    if (health <= 0) {
        ScoreCounter::increaseScore();
        context.holder.deleteEntity(*this);
    }
}