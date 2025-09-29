#ifndef GAME_ENTITYHOLDER_H
#define GAME_ENTITYHOLDER_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <vector>

class Context;
class AbstractEntity;

class EntityHolder {
private:
    std::vector<std::unique_ptr<AbstractEntity>> entities;

    int indexOf(const AbstractEntity &e) const;

public:
    void updateAll(Context &ctx);
    void drawAll(sf::RenderWindow &w) const;
    void addEntity(std::unique_ptr<AbstractEntity> e);
    void deleteEntity(const AbstractEntity &e);
    void clear();
    AbstractEntity& operator[](unsigned index) const;
    unsigned size() const;

    EntityHolder() = default;
    EntityHolder(const EntityHolder &e) = delete;
    EntityHolder &operator=(const EntityHolder &e) = delete;

    AbstractEntity &getPlayer() const;
    AbstractEntity &getTower() const;
};

#endif // GAME_ENTITYHOLDER_H