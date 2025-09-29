#include "includes/EnemySpawner.h"
#include "includes/WalkerEnemy.h"
#include "includes/HeavyEnemy.h"
#include "includes/FastEnemy.h"
#include "includes/EntityHolder.h"
#include <cstdlib>

void EnemySpawner::update(Context &context) {
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