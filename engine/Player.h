#include <SFML/Graphics.hpp>
#include "AbstractEntity.h"
#include <iostream>
#include "Context.h"
#include "EntityHolder.h"
#include "Bullet.h"
#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H
class Player : public AbstractEntity {
private:
    sf::RectangleShape shape;
    sf::Texture texture;
    void shoot(Context &context) {
        float xDiff = context.lastClickPos.x - x;
        float yDiff = context.lastClickPos.y - y;
        float angle = atan2(yDiff, xDiff);
        angle = (angle < 0) ? -angle : M_PI * 2 - angle;
        context.holder.addEntity(std::make_unique<Bullet>(angle, x, y));
    }
public:
    short getTypeID() override {
        return 1;
    }
    explicit Player(Context &context) {
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
    void draw(sf::RenderWindow &window) override {
        window.draw(shape);
    }
    void update(Context &context) override {
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
    ~Player() override = default;
};
#endif //GAME_PLAYER_H