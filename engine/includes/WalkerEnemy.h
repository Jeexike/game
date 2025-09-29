#ifndef GAME_WALKERENEMY_H
#define GAME_WALKERENEMY_H

#include "AbstractEntity.h"
#include <SFML/Graphics.hpp>

class Context;
class EntityHolder;

class WalkerEnemy : public AbstractEntity {
private:
    sf::RectangleShape shape;
    sf::Texture texture;

    const unsigned short damage = 10;
    short velocity = 2;

public:
    short getTypeID() override;
    explicit WalkerEnemy(const Context &c);
    void draw(sf::RenderWindow &window) override;
    void update(Context &context) override;
    void takeDamage(unsigned short amount, Context &context) override;
    ~WalkerEnemy() override = default;
};

#endif // GAME_WALKERENEMY_H