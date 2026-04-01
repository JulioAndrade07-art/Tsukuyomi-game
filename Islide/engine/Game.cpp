#include "Game.h"
#include "../biomes/BiomeStrategy.h"
#include <iostream>
#include <cstdlib>

Game::Game() : isRunning(false), enemySpawnTimer(0), biomeChangeTimer(0), window(nullptr) {}

Game::~Game() {
    if (window) {
        delete window;
    }
}

void Game::init() {
    std::cout << "Inicializando Jogo estilo Alto's...\n";
    isRunning = true;
    
    window = new sf::RenderWindow(sf::VideoMode({800, 600}), "Islide - VS Runner");
    window->setFramerateLimit(60);

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
    while (const std::optional<sf::Event> event = window->pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            isRunning = false;
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            Command* cmd = nullptr;
            if (keyPressed->scancode == sf::Keyboard::Scancode::Space) cmd = inputHandler->handleInput(Key::SPACE);
            else if (keyPressed->scancode == sf::Keyboard::Scancode::LShift) cmd = inputHandler->handleInput(Key::SHIFT);
            else if (keyPressed->scancode == sf::Keyboard::Scancode::LCtrl) cmd = inputHandler->handleInput(Key::CTRL);
            else if (keyPressed->scancode == sf::Keyboard::Scancode::LAlt) cmd = inputHandler->handleInput(Key::ALT);

            if (cmd) {
                player->handleInput(cmd);
            }
        }
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
    window->clear(sf::Color(40, 40, 60)); // Dark background
    
    // As entidades ainda não estão com o signature de render(sf::RenderWindow&) 
    // mas chamamos o printf simulado
    biomeManager->getCurrentBiomeName();
    player->render();
    for (Enemy* e : activeEnemies) {
        e->render();
    }
    hud->render();

    window->display();
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
    
    if (window && window->isOpen()) {
        window->close();
    }
}
