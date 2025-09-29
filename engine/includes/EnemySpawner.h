#ifndef GAME_ENEMYSPAWNER_H
#define GAME_ENEMYSPAWNER_H

#include <memory>
#include "Context.h"

class WalkerEnemy;
class HeavyEnemy;
class FastEnemy;

class EnemySpawner {
private:
    int spawnTimer = 0;
    const int spawnInterval = 50; // ticks

public:
    void update(Context &context);
};

#endif // GAME_ENEMYSPAWNER_H