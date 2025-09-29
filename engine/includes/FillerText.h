#ifndef GAME_FILLERTEXT_H
#define GAME_FILLERTEXT_H

#include "AbstractEntity.h"
#include <SFML/Graphics.hpp>

class Context;

class FillerText : public AbstractEntity {
private:
    sf::Text text;
    sf::Font font;

public:
    short getTypeID() override;
    explicit FillerText(const Context &c);
    void draw(sf::RenderWindow &window) override;
    void update(Context &context) override;
    ~FillerText() override = default;
};

#endif // GAME_FILLERTEXT_H