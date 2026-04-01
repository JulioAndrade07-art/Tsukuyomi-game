#ifndef ENEMY_H
#define ENEMY_H

#include "../engine/Entity.h"
#include <iostream>

class Enemy : public Entity {
protected:
    int damage;
    int health;
public:
    Enemy(int hp, int dmg) : health(hp), damage(dmg) {}
    
    virtual void onDeath() = 0;
    virtual void attack() = 0;
};

class BasicEnemy : public Enemy {
public:
    BasicEnemy() : Enemy(10, 10) {}
    void update(float deltaTime) override { position.x -= 2.0f * deltaTime; } // Moves left
    void render() override { std::cout << "Render Basic Enemy at (" << position.x << ")\n"; }
    void attack() override { std::cout << "Basic Enemy attacks!\n"; }
    void onDeath() override { std::cout << "Basic Enemy defeated.\n"; }
};

class FastEnemy : public Enemy {
public:
    FastEnemy() : Enemy(5, 5) {}
    void update(float deltaTime) override { position.x -= 8.0f * deltaTime; } // Moves left fast
    void render() override { std::cout << "Render Fast Enemy at (" << position.x << ")\n"; }
    void attack() override { std::cout << "Fast Enemy attacks quickly!\n"; }
    void onDeath() override { std::cout << "Fast Enemy defeated.\n"; }
};

class FlyingEnemy : public Enemy {
public:
    FlyingEnemy() : Enemy(5, 15) {}
    void update(float deltaTime) override { position.x -= 3.0f * deltaTime; /* flies */ }
    void render() override { std::cout << "Render Flying Enemy at (" << position.x << ", " << position.y << ")\n"; }
    void attack() override { std::cout << "Flying Enemy swoops down!\n"; }
    void onDeath() override { std::cout << "Flying Enemy defeated.\n"; }
};

class HeavyEnemy : public Enemy {
public:
    HeavyEnemy() : Enemy(30, 20) {}
    void update(float deltaTime) override { position.x -= 1.0f * deltaTime; } // Slow move
    void render() override { std::cout << "Render Heavy Enemy at (" << position.x << ")\n"; }
    void attack() override { std::cout << "Heavy Enemy smashes ground!\n"; }
    void onDeath() override { std::cout << "Heavy Enemy defeated.\n"; }
};

#endif
