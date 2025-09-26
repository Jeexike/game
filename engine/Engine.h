#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>

#include "Player.h"
#include "Context.h"
#include "EntityHolder.h"
#include "AbstractEntity.h"
#include "WalkerEnemy.h"
#include "HeavyEnemy.h"
#include "FastEnemy.h"
#include "Tower.h"
#include "EnemySpawner.h"
#include "IntervalTimer.h"
#include "ScoreCounter.h"
#include "FillerText.h"

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

    void processEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                exitGame();
                break;
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    currentContext.lastClickPos = sf::Mouse::getPosition(window);
                    currentContext.lastClickProcessed = false;
                }
            }
        }

        currentContext.upKeyPressed =
                sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        currentContext.downKeyPressed =
                sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S);
        currentContext.rightKeyPressed =
                sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D);
        currentContext.leftKeyPressed =
                sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    }

    void runUpdaterThread() {
        EnemySpawner spawner = EnemySpawner();
        entityHolder.addEntity(std::make_unique<Player>(currentContext));
        entityHolder.addEntity(std::make_unique<Tower>(currentContext, [this]() { this->gameOver(); }));

        while (isRunning) {
            if (!isPaused) {
                std::lock_guard<std::mutex> lock(threadLock);
                entityHolder.updateAll(currentContext);
                spawner.update(currentContext);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(20)); // 50 ticks per second
        }
    }

    void clearWindow() {
        window.clear();
        window.draw(backgroundShape);
    }

public:
    Engine(const std::string &windowTitle, unsigned targetFPS)
        : window(sf::VideoMode::getDesktopMode(), windowTitle)
        , width(window.getSize().x)
        , height(window.getSize().y)
        , currentContext(width, height, entityHolder)
        , entityHolder()
    {
        if (engineCount > 0) {
            throw std::runtime_error("Only one instance of Engine is allowed at a time.");
        }
        std::cout << width << " " << height << std::endl;
        title = windowTitle;
        Engine::engineCount++;
        isRunning = true;
        window.setFramerateLimit(targetFPS);

        backgroundShape.setSize({static_cast<float>(width), static_cast<float>(height)});

        if (!backgroundTexture.loadFromFile("../assets/sprites/floor.png")) {
            std::cout << "couldn't load background texture" << std::endl;
            backgroundShape.setFillColor(sf::Color::White);
        } else {
            backgroundTexture.setRepeated(true);
            backgroundShape.setTextureRect(sf::IntRect(0, 0, static_cast<int>(width), static_cast<int>(height)));
            backgroundShape.setTexture(&backgroundTexture);
            backgroundShape.setScale(3, 3);
        }
    }

    Engine(const Engine &) = delete;
    Engine &operator=(const Engine &) = delete;

    ~Engine() {
        stop();
        Engine::engineCount--;
        std::cout << "destroyed engine" << std::endl;
    }

    void run() {
        ScoreCounter::init();
        std::thread t(&Engine::runUpdaterThread, this);

        // ui/drawing/main thread
        while (isRunning) {
            processEvents();
            clearWindow();
            {
                std::lock_guard<std::mutex> lock(threadLock);
                ScoreCounter::draw(window);
                entityHolder.drawAll(window);
            }
            window.display();
        }
        t.join();
    }

    void stop() {
        isRunning = false;
        std::cout << "engine stopped" << std::endl;
    }

    void pause() {
        isPaused = true;
    }

    void gameOver() {
        pause();
        entityHolder.clear();
        entityHolder.addEntity(std::make_unique<FillerText>(currentContext));
    }

    void exitGame() {
        stop();
        window.close();
    }
};

short Engine::engineCount = 0;
unsigned AbstractEntity::entitiesCount = 0;
short IntervalTimer::ticksPerSec = 50;

#endif // GAME_ENGINE_H