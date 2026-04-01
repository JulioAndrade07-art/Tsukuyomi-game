#include "Game.h"
#include "../biomes/BiomeStrategy.h"
#include <iostream>
#include <cstdlib>

Game::Game() : isRunning(false), enemySpawnTimer(0), biomeChangeTimer(0) {}

Game::~Game() {}

void Game::init() {
    std::cout << "Inicializando Jogo estilo Alto's...\n";
    isRunning = true;

    player = new Player();
    inputHandler = new InputHandler();
    progression = new ProgressionSystem();
    hud = new HUD();
    biomeManager = new BiomeContext();

    // Wiring up Observers
    player->addObserver(hud);
    player->addObserver(progression);
    biomeManager->addObserver(hud);

    // Initial Biome setup
    biomeManager->setBiome(new SnowBiome());

    // Enemy Factories
    enemyFactories.push_back(new BasicEnemyFactory());
    enemyFactories.push_back(new FastEnemyFactory());
    enemyFactories.push_back(new FlyingEnemyFactory());
    enemyFactories.push_back(new HeavyEnemyFactory());
}

void Game::handleEvents() {
    // Simulating random inputs to test State and Command
    int r = rand() % 100;
    Command* cmd = nullptr;
    if (r < 5) cmd = inputHandler->handleInput(Key::SPACE); // Jump
    else if (r < 8) cmd = inputHandler->handleInput(Key::SHIFT); // Dash
    else if (r < 10) cmd = inputHandler->handleInput(Key::CTRL); // Slide
    else if (r < 12) cmd = inputHandler->handleInput(Key::ALT); // Glide

    if (cmd) {
        player->handleInput(cmd);
    }
}

void Game::update(float deltaTime) {
    player->update(deltaTime);
    progression->update(player->baseSpeed * deltaTime); // Distance based on speed

    // Apply Biome Modifiers
    biomeManager->apply(*player);

    // Simulating Biome Changes every 10 seconds
    biomeChangeTimer += deltaTime;
    if (biomeChangeTimer >= 10.0f) {
        biomeChangeTimer = 0.0f;
        int b = rand() % 3;
        if (b == 0) biomeManager->setBiome(new SnowBiome());
        else if (b == 1) biomeManager->setBiome(new DesertBiome());
        else biomeManager->setBiome(new ForestBiome());
    }

    // Spawn enemies randomly
    enemySpawnTimer += deltaTime;
    if (enemySpawnTimer >= 2.0f) {
        enemySpawnTimer = 0.0f;
        int f = rand() % enemyFactories.size();
        activeEnemies.push_back(enemyFactories[f]->createEnemy());
    }

    // Update Enemies
    for (auto it = activeEnemies.begin(); it != activeEnemies.end(); /* no increment */) {
        Enemy* e = *it;
        e->update(deltaTime);
        
        // Simulating Combat Detection (very simplified)
        // If player is in Dash or Slide, deals damage
        if (player->position.x >= e->position.x - 5.0f && player->position.x <= e->position.x + 5.0f) {
            std::cout << ">>> Combat Clash! <<<\n";
            // For now, player auto kills it in simulation, or takes damage
            int r = rand() % 2;
            if (r == 0) {
                player->takeDamage(e->health); // Take some damage
            } else {
                std::cout << "Enemy Defeated by Player!\n";
                player->notifyObservers(EventType::SCORE_CHANGED, std::to_string(500)); // Increase score wrapper
            }
            e->onDeath();
            delete e;
            it = activeEnemies.erase(it);
        } else {
            ++it;
        }
    }
}

void Game::render() {
    // Console Render Simulation
    // std::system("cls"); // Uncomment to clear screen on Windows
    std::cout << "\n--- Rendering Frame ---\n";
    biomeManager->getCurrentBiomeName();
    player->render();
    for (Enemy* e : activeEnemies) {
        e->render();
    }
    hud->render();
    std::cout << "-----------------------\n";
}

void Game::clean() {
    std::cout << "Limpando recursos e fechando o jogo...\n";
    delete player;
    delete inputHandler;
    delete progression;
    delete hud;
    delete biomeManager;
    for (Enemy* e : activeEnemies) delete e;
    for (EnemyFactory* ef : enemyFactories) delete ef;
}
