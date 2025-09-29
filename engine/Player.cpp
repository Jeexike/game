#include "includes/Player.h"
#include "includes/Context.h"
#include "includes/EntityHolder.h"
#include "includes/Bullet.h"
#include <iostream>
#include <cmath>

short Player::getTypeID() {
    return 1;
}

Player::Player(Context &context) {
    vx = 5;
    vy = 5;
    width = 45;
    height = 80;
    x = context.screenWidth / 3;
    y = context.screenHeight / 2 - height;
    shape.setSize({width, height});
    if (!texture.loadFromFile("../assets/sprites/player.png")) {
        std::cout << "couldn't load player texture" << std::endl;
        shape.setFillColor(sf::Color::Blue);
    } else {
        shape.setTexture(&texture);
    }
    shape.setOrigin(width / 2, height / 2);
    shape.setPosition(x, y);
}

void Player::draw(sf::RenderWindow &window) {
    window.draw(shape);
}

void Player::update(Context &context) {
    if (context.leftKeyPressed && (left() >= vx)) {
        x -= vx;
        shape.setScale({-1.f, 1.f});
    }
    if (context.rightKeyPressed && (right() <= context.screenWidth)) {
        x += vx;
        shape.setScale({1.f, 1.f});
    }
    if (context.upKeyPressed && (top() >= vy)) {
        y -= vy;
    }
    if (context.downKeyPressed && (bottom() <= context.screenHeight)) {
        y += vy;
    }
    shape.setPosition(x, y);
    if (!context.lastClickProcessed) {
        shoot(context);
        context.lastClickProcessed = true;
    }
}

void Player::shoot(Context &context) {
    float xDiff = context.lastClickPos.x - x;
    float yDiff = context.lastClickPos.y - y;
    float angle = atan2(yDiff, xDiff);
    context.holder.addEntity(std::make_unique<Bullet>(angle, x, y));
}