#include "PlayerState.h"
#include "Player.h"
#include "../systems/Command.h"
#include <iostream>

// Running State
void RunningState::handleInput(Player& player, Command* command) {
    if (dynamic_cast<JumpCommand*>(command)) player.changeState(new JumpingState());
    else if (dynamic_cast<DashCommand*>(command)) player.changeState(new DashingState());
    else if (dynamic_cast<SlideCommand*>(command)) player.changeState(new SlidingState());
}
void RunningState::update(Player& player, float deltaTime) {
    player.velocity.x = player.baseSpeed;
    if (!player.isGrounded) player.changeState(new JumpingState());
}
void RunningState::enter(Player& player) { std::cout << "-> Entering RUNNING State\n"; }
void RunningState::exit(Player& player) {}

// Jumping State
void JumpingState::handleInput(Player& player, Command* command) {
    if (dynamic_cast<GlideCommand*>(command)) player.changeState(new GlidingState());
    else if (dynamic_cast<DashCommand*>(command)) player.changeState(new DashingState());
}
void JumpingState::update(Player& player, float deltaTime) {
    if (player.isGrounded) player.changeState(new RunningState());
}
void JumpingState::enter(Player& player) { 
    std::cout << "-> Entering JUMPING State\n"; 
    player.jump();
}
void JumpingState::exit(Player& player) {}

// Dashing State
void DashingState::handleInput(Player& player, Command* command) {} // Invincible/locked input during dash
void DashingState::update(Player& player, float deltaTime) {
    dashTimer -= deltaTime;
    if (dashTimer <= 0) {
        if (player.isGrounded) player.changeState(new RunningState());
        else player.changeState(new JumpingState());
    }
}
void DashingState::enter(Player& player) {
    std::cout << "-> Entering DASHING State\n";
    dashTimer = 0.5f; // Dash duration
    player.dash();
}
void DashingState::exit(Player& player) { player.velocity.x = player.baseSpeed; }

// Gliding State
void GlidingState::handleInput(Player& player, Command* command) {
    // Release glide or switch to dash
    if (dynamic_cast<DashCommand*>(command)) player.changeState(new DashingState());
    // In a real app, releasing the input would go back to Jumping
}
void GlidingState::update(Player& player, float deltaTime) {
    player.glide();
    if (player.energy <= 0 || player.isGrounded) {
        player.changeState(player.isGrounded ? (PlayerState*)new RunningState() : (PlayerState*)new JumpingState());
    }
}
void GlidingState::enter(Player& player) { std::cout << "-> Entering GLIDING State\n"; }
void GlidingState::exit(Player& player) {}

// Sliding State
void SlidingState::handleInput(Player& player, Command* command) {
    if (dynamic_cast<JumpCommand*>(command)) player.changeState(new JumpingState());
}
void SlidingState::update(Player& player, float deltaTime) {
    player.slide();
    // In a real setup, slide holds as long as input is held, then returns to run.
    player.changeState(new RunningState()); // mock instant release
}
void SlidingState::enter(Player& player) { std::cout << "-> Entering SLIDING State\n"; }
void SlidingState::exit(Player& player) {}
