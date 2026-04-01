#include "BiomeContext.h"
#include <iostream>

BiomeContext::BiomeContext() : currentStrategy(nullptr) {}

BiomeContext::~BiomeContext() {
    delete currentStrategy;
}

void BiomeContext::setBiome(BiomeStrategy* newStrategy) {
    if (currentStrategy) {
        delete currentStrategy;
    }
    currentStrategy = newStrategy;
    std::string name = currentStrategy->getBiomeName();
    std::cout << "\n[BIOME CHANGED] -> " << name << "\n";
    notifyObservers(EventType::BIOME_CHANGED, name);
}

void BiomeContext::apply(Player& player) {
    if (currentStrategy) {
        currentStrategy->applyModifiers(player);
    }
}

std::string BiomeContext::getCurrentBiomeName() const {
    return currentStrategy ? currentStrategy->getBiomeName() : "None";
}
