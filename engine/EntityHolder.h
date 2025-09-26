#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <stdexcept>

class Context;
class AbstractEntity;

#ifndef GAME_ENTITYHOLDER_H
#define GAME_ENTITYHOLDER_H

class EntityHolder {
private:
    std::vector<std::unique_ptr<AbstractEntity>> entities;

    int indexOf(const AbstractEntity &e) const {
        for (size_t i = 0; i < entities.size(); ++i) {
            if (*entities[i] == e) {
                return static_cast<int>(i);
            }
        }
        throw std::runtime_error("EntityHolder - entity not found.");
    }

public:
    void updateAll(Context &ctx) {
        for (size_t i = 0; i < entities.size(); ++i) {
            entities[i]->update(ctx);
        }
    }

    void drawAll(sf::RenderWindow &w) const {
        for (size_t i = 0; i < entities.size(); ++i) {
            entities[i]->draw(w);
        }
    }

    void addEntity(std::unique_ptr<AbstractEntity> e) {
        entities.push_back(std::move(e));
    }

    void deleteEntity(const AbstractEntity &e) {
        entities.erase(entities.begin() + indexOf(e));
    }

    void clear() {
        entities.clear();
    }

    AbstractEntity& operator[](unsigned index) const {
        if (index >= entities.size()) {
            throw std::out_of_range("Entity Holder - index out of range.");
        }
        return *entities[index];
    }

    unsigned size() const {
        return static_cast<unsigned>(entities.size());
    }

    EntityHolder() = default;
    EntityHolder(const EntityHolder &e) = delete;
    EntityHolder &operator=(const EntityHolder &e) = delete;

    AbstractEntity &getPlayer() const {
        return *(entities[0]);
    }

    AbstractEntity &getTower() const {
        return *(entities[1]);
    }
};

#endif // GAME_ENTITYHOLDER_H