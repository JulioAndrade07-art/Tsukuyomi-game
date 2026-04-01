#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "Command.h"
#include <map>

// Simulated Keys
enum class Key {
    SPACE,
    SHIFT,
    CTRL,
    ALT
};

class InputHandler {
private:
    Command* buttonSpace;
    Command* buttonShift;
    Command* buttonCtrl;
    Command* buttonAlt;

public:
    InputHandler();
    ~InputHandler();

    Command* handleInput(Key k);
};

#endif
