#ifndef GAME_HEAVYENEMY_H
#define GAME_HEAVYENEMY_H

#include "AbstractEntity.h"
#include <SFML/Graphics.hpp>

class Context;
class EntityHolder;

class HeavyEnemy : public AbstractEntity {
private:
    sf::RectangleShape shape;
    sf::Texture texture;

    const unsigned short damage = 20;
    short velocity = 1;

public:
    short getTypeID() override;
    explicit HeavyEnemy(const Context &c);
    void draw(sf::RenderWindow &window) override;
    void update(Context &context) override;
    void takeDamage(unsigned short amount, Context &context) override;
    ~HeavyEnemy() override = default;
};

#endif // GAME_HEAVYENEMY_H