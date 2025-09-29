#ifndef GAME_ABSTRACTENTITY_H
#define GAME_ABSTRACTENTITY_H

#include <SFML/Graphics/RenderWindow.hpp>

class Context;

class AbstractEntity {
protected:
    float x = 0;
    float y = 0;
    float vx = 0;
    float vy = 0;
    unsigned ID = 0;
    unsigned short health = 1;
    float width = 0;
    float height = 0;

public:
    static unsigned entitiesCount;

    virtual short getTypeID() = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
    virtual void update(Context &context) = 0;
    virtual void takeDamage(unsigned short amount, Context& context);
    virtual bool collides(const AbstractEntity &other) const;

    float getX() const;
    float getY() const;
    float getVx() const;
    float getVy() const;
    float top() const;
    float bottom() const;
    float left() const;
    float right() const;
    sf::Vector2f center() const;
    bool operator==(const AbstractEntity &other) const;

    AbstractEntity();
    virtual ~AbstractEntity() = default;
};

#endif // GAME_ABSTRACTENTITY_H