#include "includes/AbstractEntity.h"
#include "includes/Context.h"

unsigned AbstractEntity::entitiesCount = 0;

void AbstractEntity::takeDamage(unsigned short amount, Context& context) {
    (void)context; // suppress unused warning
    health -= amount;
}

bool AbstractEntity::collides(const AbstractEntity &other) const {
    return (right() >= other.left() &&
            left() <= other.right() &&
            bottom() >= other.top() &&
            top() <= other.bottom());
}

float AbstractEntity::getX() const { return x; }
float AbstractEntity::getY() const { return y; }
float AbstractEntity::getVx() const { return vx; }
float AbstractEntity::getVy() const { return vy; }
float AbstractEntity::top() const { return y; }
float AbstractEntity::bottom() const { return y + height; }
float AbstractEntity::left() const { return x; }
float AbstractEntity::right() const { return x + width; }

sf::Vector2f AbstractEntity::center() const {
    return {x + width / 2, y + height / 2};
}

bool AbstractEntity::operator==(const AbstractEntity &other) const {
    return ID == other.ID;
}

AbstractEntity::AbstractEntity() {
    ID = entitiesCount++;
}