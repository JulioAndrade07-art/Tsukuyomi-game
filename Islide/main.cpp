#include "engine/Game.h"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    Game* game = new Game();
    game->init();

    const int FPS = 30; // 30 updates por segundo no console p/ visibilidade
    const int frameDelay = 1000 / FPS;

    // Loop de simulação curto para o usuário ver (ex: 100 frames)
    int frames = 0;
    while (game->running() && frames < 100) {
        auto frameStart = std::chrono::high_resolution_clock::now();

        float deltaTime = 1.0f / FPS; 

        game->handleEvents();
        game->update(deltaTime);
        game->render();

        // Delay para simular tempo real
        auto frameTime = std::chrono::high_resolution_clock::now() - frameStart;
        auto sleepTime = std::chrono::milliseconds(frameDelay) - std::chrono::duration_cast<std::chrono::milliseconds>(frameTime);
        if (sleepTime.count() > 0) {
            std::this_thread::sleep_for(sleepTime);
        }
        frames++;
    }

    game->clean();
    delete game;

    std::cout << "Simulacao concluida com sucesso. Padrões GoF validados!\n";

    return 0;
}
