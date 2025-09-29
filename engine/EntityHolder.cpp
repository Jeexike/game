#include "includes/EntityHolder.h"
#include "includes/Context.h"
#include "includes/AbstractEntity.h"
#include <stdexcept>

int EntityHolder::indexOf(const AbstractEntity &e) const {
    for (size_t i = 0; i < entities.size(); ++i) {
        if (*entities[i] == e) {
            return static_cast<int>(i);
        }
    }
    throw std::runtime_error("EntityHolder - entity not found.");
}

void EntityHolder::updateAll(Context &ctx) {
    for (size_t i = 0; i < entities.size(); ++i) {
        entities[i]->update(ctx);
    }
}

void EntityHolder::drawAll(sf::RenderWindow &w) const {
    for (size_t i = 0; i < entities.size(); ++i) {
        entities[i]->draw(w);
    }
}

void EntityHolder::addEntity(std::unique_ptr<AbstractEntity> e) {
    entities.push_back(std::move(e));
}

void EntityHolder::deleteEntity(const AbstractEntity &e) {
    entities.erase(entities.begin() + indexOf(e));
}

void EntityHolder::clear() {
    entities.clear();
}

AbstractEntity& EntityHolder::operator[](unsigned index) const {
    if (index >= entities.size()) {
        throw std::out_of_range("Entity Holder - index out of range.");
    }
    return *entities[index];
}

unsigned EntityHolder::size() const {
    return static_cast<unsigned>(entities.size());
}

AbstractEntity &EntityHolder::getPlayer() const {
    return *(entities[0]);
}

AbstractEntity &EntityHolder::getTower() const {
    return *(entities[1]);
}