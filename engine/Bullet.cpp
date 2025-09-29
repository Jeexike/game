#include "includes/Bullet.h"
#include <iostream>
#include <cmath>

short Bullet::getTypeID() {
    return 4;
}

Bullet::Bullet(float angl, float startX, float startY) {
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

void Bullet::draw(sf::RenderWindow &window) {
    window.draw(shape);
}

void Bullet::update(Context &context) {
    y += sin(angle) * velocity;
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