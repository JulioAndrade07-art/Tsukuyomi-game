#ifndef ENTITY_H
#define ENTITY_H

#include "Vector2D.h"
#include <string>

class Entity {
public:
    Vector2D position;
    Vector2D velocity;
    bool isActive;

    Entity() : isActive(true) {}
    virtual ~Entity() = default;

    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
};

#endif
