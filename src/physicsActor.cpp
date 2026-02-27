#include "raster.hpp"

///////////////////
// Physics Actor //
///////////////////

/* todo list awesome
* #1 fix the glaring issue with rectangles where you can pixel perfect slide into the corner of the rectangle and get stuff if going faster than 1u/s
*    (this may need to be done in systemExecute() so that actors can check even when not moving)
* #2 add lines; i implemented these while trying to fix the initial weirdness so shouldn't be all that hard
*    lines will need to keep track of their slope so we can add (slope*microsoftsign) to the other axis while moving on it (this may be precarious though,
*    because collisions there will not be checked. prehaps add a bool to disable line checks so it can't get checked again and become particle accelerator)
* #3 WHY IS THE SPEED LIMIT 4 MY PHONE BURNS
*    possibly just make the movement functions recursive and only do 4 at a time. given the games tics this shouldn't be a problem...
* #4 Moving objects
*    This may be hard because Yes. time for more copying celeste physics i guess
*/

void dPhysicsActor_c::systemExecute() {
    this->box.x = pos.x;
    this->box.y = pos.y;
}

// not really the microsoft sign func anymore, more like "my sign function for physics"
// it's also static so who cares
int PhysicsSign(float num) {
    return num >= 0 ? num ? mul : 0 : -mul;
}

// REAL microsoft sign
int MicrosoftSign(float num) {
    return num >= 0 ? num ? 1 : 0 : -1;
}

// essentially copied from celeste / towerfall. Fun! Most of that game's systems weren't revealed in the glorified blogpost this is from SO
// it's fine. Plus this binary will be more efficent - REDDITEVIL
void dPhysicsActor_c::MoveX(float amount) {
    // our fractional movement...
    this->xRemainder += amount*mul;

    int move = round(xRemainder);
    // dummy check
    if (move != 0) {
        // pixel by pixel shitee
        xRemainder -= move;
        int sign = PhysicsSign(move);
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
    this->yRemainder += amount*mul;

    int move = round(yRemainder);
    // dummy check
    if (move != 0) {
        // pixel by pixel shitee
        yRemainder -= move;
        int sign = PhysicsSign(move);
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
        if (offsetBox.intersects(other->box)) {
            return other;
        }
    }
    return 0;
}

void dPhysicsActor_c::onCollide(dPhysicsActor_c* other) { return; }