#ifndef PLAYER_H
#define PLAYER_H

#include "../engine/Entity.h"
#include "../systems/Subject.h"
#include "PlayerState.h"

class Command;

class Player : public Entity, public Subject {
private:
    PlayerState* currentState;

public:
    bool isGrounded;
    float gravity;
    float baseSpeed;
    int health;
    int energy; // For dashing/gliding

    Player();
    ~Player();

    void handleInput(Command* command);
    void update(float deltaTime) override;
    void render() override;
    
    void changeState(PlayerState* newState);
    
    // Actions triggered by States/Commands
    void jump();
    void dash();
    void glide();
    void slide();
    void takeDamage(int amount);
};

#endif
