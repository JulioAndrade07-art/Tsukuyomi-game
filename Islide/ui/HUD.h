#ifndef HUD_H
#define HUD_H

#include "../systems/Observer.h"
#include <iostream>

class HUD : public Observer {
private:
    int score;
    int health;
    int energy;
    std::string currentBiome;

public:
    HUD() : score(0), health(100), energy(100), currentBiome("Snow") {}

    void onNotify(EventType event, const std::string& data) override {
        switch (event) {
            case EventType::SCORE_CHANGED:
                score = std::stoi(data);
                break;
            case EventType::PLAYER_DAMAGED:
                health = std::stoi(data);
                break;
            case EventType::POWER_METER_CHANGED:
                energy = std::stoi(data);
                break;
            case EventType::BIOME_CHANGED:
                currentBiome = data;
                break;
            default:
                break;
        }
    }

    void render() {
        std::cout << "============== HUD ==============\n";
        std::cout << "HP: " << health << " | Energy: " << energy << "\n";
        std::cout << "Score: " << score << " | Biome: " << currentBiome << "\n";
        std::cout << "=================================\n";
    }
};

#endif
