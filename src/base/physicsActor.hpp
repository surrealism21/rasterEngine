#pragma once
#include "raster.hpp"

class dPhysicsActor_c;

struct CollisionInfo {
    bool collided;
    // pointer only set if collided is true
    dPhysicsActor_c* other;
};

// actor that has physics, fully
class dPhysicsActor_c : public dBase_c {
public:
    void addToPhysicsList();
    void removeFromPhysicsList();
    s64 physicsListPos;

    void systemExecute();
    virtual void onCollide(dPhysicsActor_c* other);
    virtual void MoveX(float amount);
    virtual void MoveY(float amount);

    Vec2 velocity;

    // physics stuff
    float xRemainder;
    float yRemainder;

    RasRectangle box;
    RasRectangle offsetBox;

    bool solid;

    dPhysicsActor_c* collideAt(Vec2 offs);
};