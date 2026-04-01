#ifndef GAME_H
#define GAME_H

#include "../player/Player.h"
#include "../systems/InputHandler.h"
#include "../systems/ProgressionSystem.h"
#include "../ui/HUD.h"
#include "../biomes/BiomeContext.h"
#include "../enemies/EnemyFactory.h"
#include <vector>

class Game {
private:
    bool isRunning;
    Player* player;
    InputHandler* inputHandler;
    ProgressionSystem* progression;
    HUD* hud;
    BiomeContext* biomeManager;
    
    std::vector<Enemy*> activeEnemies;
    std::vector<EnemyFactory*> enemyFactories;
    
    float enemySpawnTimer;
    float biomeChangeTimer;

public:
    Game();
    ~Game();

    void init();
    void handleEvents();
    void update(float deltaTime);
    void render();
    void clean();

    bool running() const { return isRunning; }
};

#endif
