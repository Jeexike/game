#include <memory>
#include "Context.h"
#include "WalkerEnemy.h"
#include "HeavyEnemy.h"
#include "FastEnemy.h"

#ifndef GAME_ENEMYSPAWNER_H
#define GAME_ENEMYSPAWNER_H

class EnemySpawner {
private:
    int spawnTimer = 0;
    const int spawnInterval = 50; // ticks

public:
    void update(Context &context) {
        spawnTimer++;
        if (spawnTimer >= spawnInterval) {
            spawnTimer = 0;
            int type = rand() % 3;
            if (type == 0) {
                context.holder.addEntity(std::make_unique<WalkerEnemy>(context));
            } else if (type == 1) {
                context.holder.addEntity(std::make_unique<HeavyEnemy>(context));
            } else {
                context.holder.addEntity(std::make_unique<FastEnemy>(context));
            }
        }
    }
};

#endif // GAME_ENEMYSPAWNER_H