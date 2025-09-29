#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>
#include <string>

#include "Context.h"
#include "EntityHolder.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

class EnemySpawner;
class FillerText;

class Engine {
    static short engineCount;

private:
    sf::RenderWindow window;
    const unsigned width;
    const unsigned height;
    std::string title;
    EntityHolder entityHolder;
    Context currentContext;
    sf::Texture backgroundTexture;
    sf::RectangleShape backgroundShape;
    std::mutex threadLock;

    bool isRunning = false;
    bool isPaused = false;

    void processEvents();
    void runUpdaterThread();
    void clearWindow();

public:
    Engine(const std::string &windowTitle, unsigned targetFPS);
    Engine(const Engine &) = delete;
    Engine &operator=(const Engine &) = delete;

    ~Engine();

    void run();
    void stop();
    void pause();
    void gameOver();
    void exitGame();
};

#endif // GAME_ENGINE_H