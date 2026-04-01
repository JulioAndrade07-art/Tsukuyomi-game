#include "EnemyFactory.h"

Enemy* BasicEnemyFactory::createEnemy() {
    return new BasicEnemy();
}

Enemy* FastEnemyFactory::createEnemy() {
    return new FastEnemy();
}

Enemy* FlyingEnemyFactory::createEnemy() {
    return new FlyingEnemy();
}

Enemy* HeavyEnemyFactory::createEnemy() {
    return new HeavyEnemy();
}
