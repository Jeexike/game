#ifndef GAME_BULLET_H
#define GAME_BULLET_H

#include <SFML/Graphics.hpp>
#include "AbstractEntity.h"
#include "Context.h"
#include "EntityHolder.h"

class Bullet : public AbstractEntity {
private:
    sf::CircleShape shape;
    float angle = 0;
    float velocity = 30;
    const short damage = 100;

public:
    short getTypeID() override;
    explicit Bullet(float angl, float startX, float startY);
    void draw(sf::RenderWindow &window) override;
    void update(Context &context) override;
    ~Bullet() override = default;
};

#endif // GAME_BULLET_H