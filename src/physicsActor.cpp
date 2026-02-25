#include "raster.hpp"

///////////////////
// Physics Actor //
///////////////////

void dPhysicsActor_c::systemExecute() {
    this->box.x = pos.x;
    this->box.y = pos.y;
}

// microsoft's sign slop from C#. basically cloned so
int MicrosoftSign(float num) {
    if (signbit(num)) {
        return -1;
    }
    else {
        return 1;
    }
}

// essentially copied from celeste / towerfall. Fun! Most of that game's systems weren't revealed in the glorified blogpost this is from SO
// it's fine. Plus this binary will be more efficent - REDDITEVIL
void dPhysicsActor_c::MoveX(float amount) {
    // our fractional movement...
    this->xRemainder += amount;

    int move = round(xRemainder);
    // dummy check
    if (move != 0) {
        // pixel by pixel shitee
        xRemainder -= move;
        int sign = MicrosoftSign(move);
        Vec2 offs = Vec2(sign, 0);
        while (move != 0) {
            dPhysicsActor_c* collide = collideAt(offs);
            if (!collide) {
                // no collision
                // The "sign bit" is whether or not the number is positive. If it is 1, then move forward.
                this->pos.x += sign;
                // Sub or add to counter
                move -= sign;
            }
            else {
                onCollide(collide);
                collide->onCollide(this);
                break;
            }
        }
    }
}

void dPhysicsActor_c::MoveY(float amount) {
    // our fractional movement...
    this->yRemainder += amount;

    int move = round(yRemainder);
    // dummy check
    if (move != 0) {
        // pixel by pixel shitee
        yRemainder -= move;
        int sign = MicrosoftSign(move);
        Vec2 offs = Vec2(0, sign);
        while (move != 0) {
            dPhysicsActor_c* collide = collideAt(offs);
            if (!collide) {
                // no collision
                // The "sign bit" is whether or not the number is positive. If it is 1, then move forward.
                this->pos.y += sign;
                // Sub or add to counter
                move -= sign;
            }
            else {
                onCollide(collide);
                collide->onCollide(this);
                break;
            }
        }
    }
}

void dPhysicsActor_c::addToPhysicsList() {
    fBase_c::instance.PhysicsActors.push_back(this);
    this->physicsListPos = fBase_c::instance.PhysicsActors.size();
    // not much more is needed as this is essentially a list of references for calculation.
}

void dPhysicsActor_c::removeFromPhysicsList() {
    // note that this is 
    if (physicsListPos == -1) {
        cout << "Tried to remove an PhysicsObject from global physics list, that had already been removed!" << endl;
        cout << "ActorID: " << (int)this->actorID << " @" << this << endl;
        cout << "Aborted" << endl;
        exit(1);
    }

    this->physicsListPos = -1;
}

dPhysicsActor_c* dPhysicsActor_c::collideAt(Vec2 offs) {
    // this is for checking to insure that we're NEXT to something, but not TOUCHING it. Atoms never touch, my shitty rectangles never touch.
    this->offsetBox = this->box;
    offsetBox.position.x += offs.x;
    offsetBox.position.y += offs.y;
    for (dPhysicsActor_c* other : fBase_c::instance.PhysicsActors) { 
        if (this == other) {
            continue;
        }
        // do shit with the other box so collision isn't broken
        ofRectangle otherBox = other->box;
        if (signbit(offs.x)) {
            otherBox.position.x -= -3;
        }
        if (signbit(offs.y)) {
            otherBox.position.y -= -3;
        }
        if (offsetBox.intersects(otherBox)) {
            return other;
        }
    }
    return 0;
}

void dPhysicsActor_c::onCollide(dPhysicsActor_c* other) { return; }