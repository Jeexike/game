#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>
#include <string>
#include "GameState.h"
#include "Context.h"
#include "EntityHolder.h"
#include "MainMenu.h"

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
    GameState currentState = GameState::Menu;
    std::unique_ptr<MainMenu> mainMenu;
    bool gameIsOver = false;

    void runMainMenuLoop();
    void runGameLoop();
    void runPausedLoop();
    void initializeGame();
    void processEvents();
    void runUpdaterThread();
    void clearWindow();
    void togglePause();

public:
    Engine(const std::string &windowTitle, unsigned targetFPS);
    ~Engine();
    void run();
    void stop();
    void gameOver();
    void exitGame();
    void changeState(GameState newState);
};

#endif