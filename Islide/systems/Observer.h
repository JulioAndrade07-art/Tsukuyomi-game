#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

enum class EventType {
    SCORE_CHANGED,
    PLAYER_DAMAGED,
    BIOME_CHANGED,
    ENEMY_KILLED,
    POWER_METER_CHANGED
};

class Observer {
public:
    virtual ~Observer() = default;
    virtual void onNotify(EventType event, const std::string& data) = 0;
};

#endif
