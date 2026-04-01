#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

class Player; // Forward declaration
class Command;

class PlayerState {
public:
    virtual ~PlayerState() = default;
    
    virtual void handleInput(Player& player, Command* command) = 0;
    virtual void update(Player& player, float deltaTime) = 0;
    virtual void enter(Player& player) = 0;
    virtual void exit(Player& player) = 0;
};

class RunningState : public PlayerState {
public:
    void handleInput(Player& player, Command* command) override;
    void update(Player& player, float deltaTime) override;
    void enter(Player& player) override;
    void exit(Player& player) override;
};

class JumpingState : public PlayerState {
public:
    void handleInput(Player& player, Command* command) override;
    void update(Player& player, float deltaTime) override;
    void enter(Player& player) override;
    void exit(Player& player) override;
};

class DashingState : public PlayerState {
private:
    float dashTimer;
public:
    void handleInput(Player& player, Command* command) override;
    void update(Player& player, float deltaTime) override;
    void enter(Player& player) override;
    void exit(Player& player) override;
};

class GlidingState : public PlayerState {
public:
    void handleInput(Player& player, Command* command) override;
    void update(Player& player, float deltaTime) override;
    void enter(Player& player) override;
    void exit(Player& player) override;
};

class SlidingState : public PlayerState {
public:
    void handleInput(Player& player, Command* command) override;
    void update(Player& player, float deltaTime) override;
    void enter(Player& player) override;
    void exit(Player& player) override;
};

#endif
