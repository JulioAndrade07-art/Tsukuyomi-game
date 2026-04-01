#include "ProgressionSystem.h"
#include <iostream>

ProgressionSystem::ProgressionSystem() : totalScore(0), distanceTraveled(0), level(1) {}

void ProgressionSystem::onNotify(EventType event, const std::string& data) {
    if (event == EventType::SCORE_CHANGED) {
        totalScore = std::stoi(data);
        checkLevelUp();
    }
}

void ProgressionSystem::update(float distanceDelta) {
    distanceTraveled += static_cast<int>(distanceDelta);
    checkLevelUp();
}

void ProgressionSystem::checkLevelUp() {
    int requiredForNext = level * 1000 + (level * 500); // 1500, 3000, 4500
    if (totalScore + distanceTraveled >= requiredForNext) {
        level++;
        std::cout << "\n>>> LEVEL UP! NEW POWERS UNLOCKED! Level: " << level << " <<<\n\n";
        // Logic to unlock Powers (e.g. increase Dash efficiency or Glide duration)
    }
}
