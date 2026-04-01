#ifndef COMMAND_H
#define COMMAND_H

class Player; // Forward declaration

class Command {
public:
    virtual ~Command() = default;
    virtual void execute(Player& player) = 0;
};

// Concrete Commands
class JumpCommand : public Command {
public:
    void execute(Player& player) override;
};

class DashCommand : public Command {
public:
    void execute(Player& player) override;
};

class GlideCommand : public Command {
public:
    void execute(Player& player) override;
};

class SlideCommand : public Command {
public:
    void execute(Player& player) override;
};

#endif
