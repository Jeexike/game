#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "AbstractEntity.h"
#include <SFML/Graphics.hpp>

class Context;
class EntityHolder;
class Bullet;

class Player : public AbstractEntity {
private:
    sf::RectangleShape shape;
    sf::Texture texture;

    void shoot(Context &context);

public:
    short getTypeID() override;
    explicit Player(Context &context);
    void draw(sf::RenderWindow &window) override;
    void update(Context &context) override;
    ~Player() override = default;
};

#endif // GAME_PLAYER_H