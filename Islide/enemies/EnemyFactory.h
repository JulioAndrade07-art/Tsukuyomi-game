#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include "Enemy.h"

class EnemyFactory {
public:
    virtual ~EnemyFactory() = default;
    virtual Enemy* createEnemy() = 0;
};

class BasicEnemyFactory : public EnemyFactory {
public:
    Enemy* createEnemy() override;
};

class FastEnemyFactory : public EnemyFactory {
public:
    Enemy* createEnemy() override;
};

class FlyingEnemyFactory : public EnemyFactory {
public:
    Enemy* createEnemy() override;
};

class HeavyEnemyFactory : public EnemyFactory {
public:
    Enemy* createEnemy() override;
};

#endif
