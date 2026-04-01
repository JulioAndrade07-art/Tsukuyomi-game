#include "InputHandler.h"
#include "../player/Player.h"

void JumpCommand::execute(Player& player) { player.handleInput(this); }
void DashCommand::execute(Player& player) { player.handleInput(this); }
void GlideCommand::execute(Player& player) { player.handleInput(this); }
void SlideCommand::execute(Player& player) { player.handleInput(this); }

InputHandler::InputHandler() {
    buttonSpace = new JumpCommand();
    buttonShift = new DashCommand();
    buttonCtrl = new SlideCommand();
    buttonAlt = new GlideCommand();
}

InputHandler::~InputHandler() {
    delete buttonSpace;
    delete buttonShift;
    delete buttonCtrl;
    delete buttonAlt;
}

Command* InputHandler::handleInput(Key k) {
    if (k == Key::SPACE) return buttonSpace;
    if (k == Key::SHIFT) return buttonShift;
    if (k == Key::CTRL) return buttonCtrl;
    if (k == Key::ALT) return buttonAlt;
    return nullptr;
}
