#ifndef GAME_HEAVYENEMY_H
#define GAME_HEAVYENEMY_H

#include "AbstractEntity.h"
#include <iostream>
#include "Context.h"
#include "EntityHolder.h"
#include <SFML/Graphics.hpp>
#include "ScoreCounter.h"
#include <math.h>

class HeavyEnemy : public AbstractEntity {
private:
    sf::RectangleShape shape;
    sf::Texture texture;

    const unsigned short damage = 20;
    short velocity = 1;

public:
    short getTypeID() override {
        return 2;
    }

    explicit HeavyEnemy(const Context &c) {
        bool vertical = rand() % 2;
        bool first = rand() % 2;

        if (vertical) {
            x = (first) ? 0 : c.screenWidth;
            y = rand() % c.screenHeight;
        } else {
            x = rand() % c.screenWidth;
            y = (first) ? 0 : c.screenHeight;
        }

        health = 400;
        width = 100;
        height = 100;

        shape.setSize({width, height});
        if (!texture.loadFromFile("../assets/sprites/heavy_enemy.png")) {
            std::cout << "couldn't load heavy enemy texture" << std::endl;
            shape.setFillColor(sf::Color::Red);
            shape.setOutlineThickness(1);
            shape.setOutlineColor(sf::Color::Black);
        } else {
            shape.setTexture(&texture);
        }
        shape.setPosition(x, y);
    }

    void draw(sf::RenderWindow &window) override {
        window.draw(shape);
    }

    void update(Context &context) override {
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

    void takeDamage(unsigned short amount, Context &context) override {
        health -= amount;
        if (health <= 0) {
            ScoreCounter::increaseScore();
            context.holder.deleteEntity(*this);
        }
    }


    ~HeavyEnemy() override = default;

};


#endif //GAME_HEAVYENEMY_H
