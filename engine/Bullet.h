#include <SFML/Graphics.hpp>
#include "AbstractEntity.h"
#include <iostream>
#include "Context.h"
#include "EntityHolder.h"
#include "WalkerEnemy.h"
#ifndef GAME_BULLET_H
#define GAME_BULLET_H
class Bullet : public AbstractEntity {
private:
    sf::CircleShape shape;
    float angle = 0;
    float velocity = 30;
    const short damage = 100;
public:
    short getTypeID() override {
        return 4;
    }
    explicit Bullet(float angl, float startX, float startY) {
        width = 5;
        height = 5;
        angle = angl;
        x = startX - width * 2;
        y = startY - height * 2;
        shape.setRadius(width * 2);
        shape.setFillColor(sf::Color{255, 237, 0});
        shape.setOutlineColor(sf::Color{255, 139, 0});
        shape.setOutlineThickness(3);
    }
    void draw(sf::RenderWindow &window) override {
        window.draw(shape);
    }
    void update(Context &context) override {
        y -= sin(angle) * velocity;
        x += cos(angle) * velocity;
        if (left() > context.screenWidth || bottom() > context.screenHeight) {
            context.holder.deleteEntity(*this);
            return;
        }
        shape.setPosition(x, y);
        for (unsigned i = 0; i < context.holder.size(); i++) {
            if (context.holder[i].getTypeID() == 2) {
                if (collides(context.holder[i])) {
                    context.holder[i].takeDamage(damage, context);
                    context.holder.deleteEntity(*this);
                    return;
                }
            }
        }
    }
    ~Bullet() override = default;
};
#endif