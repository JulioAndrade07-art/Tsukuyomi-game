#include "Player.h"
#include <iostream>

Player::Player() {
    position = Vector2D(0, 0);
    velocity = Vector2D(5.0f, 0); // Runner moves right automatically
    isGrounded = true;
    gravity = 9.8f;
    baseSpeed = 5.0f;
    health = 100;
    energy = 100;
    currentState = new RunningState();
    currentState->enter(*this);
}

Player::~Player() {
    delete currentState;
}

void Player::handleInput(Command* command) {
    if (currentState) {
        currentState->handleInput(*this, command);
    }
}

void Player::update(float deltaTime) {
    if (currentState) {
        currentState->update(*this, deltaTime);
    }
    
    // Apply basic physics
    position += velocity * deltaTime;
    
    if (!isGrounded) {
        velocity.y += gravity * deltaTime;
    } else {
        velocity.y = 0;
        position.y = 0; // Ground level for simulation
    }

    // Energy regen
    if (energy < 100) energy += 10 * deltaTime;
}

void Player::render() {
    std::cout << "[Player Render] Pos: (" << position.x << ", " << position.y << ")\n";
}

void Player::changeState(PlayerState* newState) {
    if (currentState) {
        currentState->exit(*this);
        delete currentState;
    }
    currentState = newState;
    currentState->enter(*this);
    
    notifyObservers(EventType::POWER_METER_CHANGED, std::to_string(energy));
}

void Player::jump() {
    if (isGrounded) {
        velocity.y = -15.0f;
        isGrounded = false;
        std::cout << "Player Jumped!\n";
    }
}

void Player::dash() {
    if (energy >= 30) {
        velocity.x = baseSpeed * 3;
        energy -= 30;
        std::cout << "Player Dashed!\n";
    }
}

void Player::glide() {
    if (!isGrounded && energy >= 1) {
        velocity.y *= 0.8f; // Slow down fall
        energy -= 10;
        std::cout << "Player Gliding!\n";
    }
}

void Player::slide() {
    if (isGrounded) {
        velocity.x = baseSpeed * 0.5f;
        std::cout << "Player Sliding (causing AoE)!\n";
    }
}

void Player::takeDamage(int amount) {
    health -= amount;
    notifyObservers(EventType::PLAYER_DAMAGED, std::to_string(health));
    std::cout << "Player took " << amount << " damage. Health: " << health << "\n";
}
