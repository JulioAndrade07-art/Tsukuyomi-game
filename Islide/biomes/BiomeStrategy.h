#ifndef BIOMESTRATEGY_H
#define BIOMESTRATEGY_H

#include "../player/Player.h"
#include <string>

// Strategy Interface
class BiomeStrategy {
public:
    virtual ~BiomeStrategy() = default;
    
    // Modifies player physics and behaviors dynamically based on the current biome
    virtual void applyModifiers(Player& player) = 0;
    
    virtual std::string getBiomeName() const = 0;
};

// Concrete Strategies
class SnowBiome : public BiomeStrategy {
public:
    void applyModifiers(Player& player) override {
        // Slippery: slide does more AoE, run speed increases slightly
        player.baseSpeed = 6.0f;
    }
    std::string getBiomeName() const override { return "Snow (Slippery)"; }
};

class DesertBiome : public BiomeStrategy {
public:
    void applyModifiers(Player& player) override {
        // Sandstorms: reduced visibility, slightly slower speed, jump is heavier
        player.baseSpeed = 4.5f;
        player.gravity = 11.0f;
    }
    std::string getBiomeName() const override { return "Desert (Sandstorm)"; }
};

class ForestBiome : public BiomeStrategy {
public:
    void applyModifiers(Player& player) override {
        // Normal stats, but level generation will spawn more vertical platforms
        player.baseSpeed = 5.0f;
        player.gravity = 9.8f;
    }
    std::string getBiomeName() const override { return "Forest (Vertical)"; }
};

#endif
