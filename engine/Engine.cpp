#include "includes/Engine.h"

#include "includes/Player.h"
#include "includes/Context.h"
#include "includes/EntityHolder.h"
#include "includes/AbstractEntity.h"
#include "includes/WalkerEnemy.h"
#include "includes/HeavyEnemy.h"
#include "includes/FastEnemy.h"
#include "includes/Tower.h"
#include "includes/EnemySpawner.h"
#include "includes/IntervalTimer.h"
#include "includes/ScoreCounter.h"
#include "includes/FillerText.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

short Engine::engineCount = 0;

void Engine::processEvents() {
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

void Engine::runUpdaterThread() {
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

void Engine::clearWindow() {
    window.clear();
    window.draw(backgroundShape);
}

Engine::Engine(const std::string &windowTitle, unsigned targetFPS)
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

Engine::~Engine() {
    stop();
    Engine::engineCount--;
    std::cout << "destroyed engine" << std::endl;
}

void Engine::run() {
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

void Engine::stop() {
    isRunning = false;
    std::cout << "engine stopped" << std::endl;
}

void Engine::pause() {
    isPaused = true;
}

void Engine::gameOver() {
    pause();
    entityHolder.clear();
    entityHolder.addEntity(std::make_unique<FillerText>(currentContext));
}

void Engine::exitGame() {
    stop();
    window.close();
}