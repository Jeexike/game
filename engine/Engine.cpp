#include "includes/Engine.h"
#include "includes/Player.h"
#include "includes/Context.h"
#include "includes/EntityHolder.h"
#include "includes/WalkerEnemy.h"
#include "includes/HeavyEnemy.h"
#include "includes/FastEnemy.h"
#include "includes/Tower.h"
#include "includes/EnemySpawner.h"
#include "includes/ScoreCounter.h"
#include "includes/MainMenu.h"

short Engine::engineCount = 0;

void Engine::runMainMenuLoop() {
    if (!mainMenu) {
        mainMenu = std::make_unique<MainMenu>(width, height);
        mainMenu->setCallbacks(
            [this]() { this->changeState(GameState::Playing); },
            []() { /* Колбэк для "Settings" - пока пустой */ },
            [this]() { this->exitGame(); }
        );
    }
    while (isRunning && currentState == GameState::Menu) {
        mainMenu->handleInput(window);
        if (currentState == GameState::Menu) {
            mainMenu->update(window);
            mainMenu->draw(window);
        }
    }
}

void Engine::runGameLoop() {
    ScoreCounter::init();
    std::thread t(&Engine::runUpdaterThread, this);
    while (isRunning && currentState == GameState::Playing) {
        processEvents();
        if (currentState == GameState::Playing) {
            clearWindow();
            {
                std::lock_guard<std::mutex> lock(threadLock);
                ScoreCounter::draw(window);
                entityHolder.drawAll(window);
            }
            window.display();
        }
    }
    t.join();
}

void Engine::runPausedLoop() {
    while (isRunning && currentState == GameState::Paused) {
        processEvents();
        if (currentState == GameState::Paused) {
            clearWindow();
            {
                std::lock_guard<std::mutex> lock(threadLock);
                ScoreCounter::draw(window);
                entityHolder.drawAll(window);
            }
            window.display();
        }
    }
}

void Engine::initializeGame() {
    gameIsOver = false;
    entityHolder.clear();
    entityHolder.addEntity(std::make_unique<Player>(currentContext));
    entityHolder.addEntity(std::make_unique<Tower>(currentContext, [this]() { this->gameOver(); }));
}

void Engine::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            exitGame();
            return;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
            togglePause();
            return;
        }
        if (currentState == GameState::Playing && event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                currentContext.lastClickPos = sf::Mouse::getPosition(window);
                currentContext.lastClickProcessed = false;
            }
        }
    }
    if (currentState == GameState::Playing || currentState == GameState::Paused) {
        currentContext.upKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        currentContext.downKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S);
        currentContext.rightKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D);
        currentContext.leftKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    }
}

void Engine::runUpdaterThread() {
    EnemySpawner spawner;
    while (isRunning && (currentState == GameState::Playing || currentState == GameState::Paused)) {
        if (gameIsOver) {
            changeState(GameState::Menu);
            return;
        }
        if (currentState == GameState::Playing) {
            std::lock_guard<std::mutex> lock(threadLock);
            entityHolder.updateAll(currentContext);
            spawner.update(currentContext);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
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
    , entityHolder()
    , currentContext(width, height, entityHolder)
{
    if (engineCount > 0) throw std::runtime_error("Only one instance of Engine is allowed at a time.");
    title = windowTitle;
    Engine::engineCount++;
    isRunning = true;
    window.setFramerateLimit(targetFPS);
    backgroundShape.setSize({static_cast<float>(width), static_cast<float>(height)});

    if (!backgroundTexture.loadFromFile("../assets/sprites/floor.png")) {
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
}

void Engine::run() {
    while (isRunning) {
        switch (currentState) {
            case GameState::Menu: runMainMenuLoop(); break;
            case GameState::Playing: runGameLoop(); break;
            case GameState::Paused: runPausedLoop(); break;
            case GameState::GameOver: changeState(GameState::Menu); break;
        }
    }
}

void Engine::stop() {
    isRunning = false;
}

void Engine::gameOver() {
    changeState(GameState::Menu);
}

void Engine::exitGame() {
    stop();
    window.close();
}

void Engine::changeState(GameState newState) {
    if (currentState == newState) return;
    currentState = newState;
    if (newState == GameState::Playing) initializeGame();
}

void Engine::togglePause() {
    if (currentState == GameState::Playing) changeState(GameState::Paused);
    else if (currentState == GameState::Paused) changeState(GameState::Playing);
}