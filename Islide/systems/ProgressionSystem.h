#ifndef PROGRESSIONSYSTEM_H
#define PROGRESSIONSYSTEM_H

#include "../systems/Observer.h"
#include "../systems/Subject.h"

// Hybrid Progression System: Distance + Pickups (represented by score/events)
class ProgressionSystem : public Observer, public Subject {
private:
    int totalScore;
    int distanceTraveled;
    int level;

public:
    ProgressionSystem();

    void onNotify(EventType event, const std::string& data) override;
    void update(float distanceDelta);
    
    void checkLevelUp();
};

#endif
