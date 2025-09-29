#ifndef GAME_TOWER_H
#define GAME_TOWER_H

#include "AbstractEntity.h"
#include <SFML/Graphics.hpp>
#include <functional>

class Context;
class EntityHolder;

class Tower : public AbstractEntity {
private:
    sf::RectangleShape bottomLayer;
    sf::RectangleShape topLayer;
    sf::RectangleShape shape;
    sf::Texture texture;
    std::function<void()> onDeath;

public:
    short getTypeID() override;
    explicit Tower(const Context &ctx, std::function<void()> deathCallback);
    void draw(sf::RenderWindow &window) override;
    void update(Context &context) override;
    void takeDamage(unsigned short amount, Context &context) override;
    ~Tower() override = default;
};

#endif // GAME_TOWER_H