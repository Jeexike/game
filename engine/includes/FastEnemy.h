#ifndef GAME_FASTENEMY_H
#define GAME_FASTENEMY_H

#include "AbstractEntity.h"
#include <SFML/Graphics.hpp>

class Context;
class EntityHolder;

class FastEnemy : public AbstractEntity {
private:
    sf::RectangleShape shape;
    sf::Texture texture;

    const unsigned short damage = 5;
    short velocity = 4;

public:
    short getTypeID() override;
    explicit FastEnemy(const Context &c);
    void draw(sf::RenderWindow &window) override;
    void update(Context &context) override;
    void takeDamage(unsigned short amount, Context &context) override;
    ~FastEnemy() override = default;
};

#endif // GAME_FASTENEMY_H