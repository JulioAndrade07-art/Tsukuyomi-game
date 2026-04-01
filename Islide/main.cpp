#include "engine/Game.h"
#include <iostream>

int main() {
    Game* game = new Game();
    game->init();

    // Loop de tempo real
    sf::Clock clock;
    
    while (game->running()) {
        float deltaTime = clock.restart().asSeconds();
        if (deltaTime > 0.15f) deltaTime = 0.15f; // limitador de lag

        game->handleEvents();
        game->update(deltaTime);
        game->render();
    }

    game->clean();
    delete game;

    std::cout << "Simulacao concluida com sucesso.\n";

    return 0;
}
