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

    virtual void takeDamage(unsigned short amount, Context& context) {
        health -= amount;
    }

    virtual bool collides(const AbstractEntity &other) const {
        return (right() >= other.left() &&
                left() <= other.right() &&
                bottom() >= other.top() &&
                top() <= other.bottom());
    }



    float getX() const {
        return x;
    }

    float getY() const {
        return y;
    }

    float getVx() const {
        return vx;
    }

    float getVy() const {
        return vy;
    }

    float top() const {
        return y;
    }

    float bottom() const {
        return y + height;
    }

    float left() const {
        return x;
    }

    float right() const {
        return x + width;
    }

    sf::Vector2f center() const {
        return {x+width/2, y+height/2};
    }

    bool operator==(const AbstractEntity &other) const {
        return ID == other.ID;
    }

    AbstractEntity() {
        ID = entitiesCount++;
    }

    virtual ~AbstractEntity() = default;
};


#endif
