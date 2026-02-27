#include "raster.hpp"

// FIXME: Maybe only use 1 loop??? I don't think I can avoid the drawing stuff, but...

// This one is more complex because it runs last and handles actor deletions. The iterator gets very fucked if we do not baby it,
// so we do that here. RemoveFromList is an illusion. Bye.
void fBase_c::commonExecute() {
    // lazy ass physics garbage collection
    // needs to come first otherwise the normal one will Kill it okay thanks
    for (auto iter = PhysicsActors.begin(); iter != PhysicsActors.end();) {
        dPhysicsActor_c* curr = *iter;
        if (curr->physicsListPos == -1) {
            iter = PhysicsActors.erase(iter);
            // no deletion yay!
            continue;
        }
        else {
            ++iter;
        }
    }

    // normal running
    for (auto iter = Actors.begin(); iter != Actors.end();) {
        dBase_c* curr = *iter;
        // collect garbage
        if (curr->listPos == -1) {
            iter = Actors.erase(iter);
            delete curr;
            continue;
        }
        else {
            ++iter;
        }
        // SOMETIMES does physics stuff, but i'd like to keep this polymorphic or whatever you call it? Custom
        curr->systemExecute();
        curr->onExecute();
    }
}

void fBase_c::commonDraw() {
    for (dBase_c* curr : Actors) {
        if (curr->listPos != -1) {
            curr->onDraw();
            // TODO: add debug stuff. For now, always on
            curr->debugDraw();
        }
    }
}

void fBase_c::commonControl() {
    // This is my optimization. So super good
    if (keysPressed.size() != 0 || mouseButtons.size() != 0) {
        for (dBase_c* curr : Actors) {
            if (curr->listPos != -1) {
                curr->control(keysPressed);
            }
        }
    }
}

dBase_c* fBase_c::fFactory::create(ActorID actor) {
    // dummy check
    assert(funcs.find(actor) != nullptr);
    auto it = funcs.find(actor);
    if (it != funcs.end()) {
        return it->second();
    }
    return NULL;
}

// Global funcs

void createActor(ActorID actorid) {
    dBase_c* actor = fBase_c::instance.factory.create(actorid);
    actor->addToList();
    return;
}

dBase_c* findFirstActor(ActorID actorid) {
    for (dBase_c* curr : fBase_c::instance.Actors) {
        if (curr->actorID == actorid) {
            return curr;
        }
    }
    return NULL;
}

std::list<dBase_c*> searchActors(ActorID actorid) {
    std::list<dBase_c*> ret;
    for (dBase_c* curr : fBase_c::instance.Actors) {
        if (curr->actorID == actorid) {
            ret.push_back(curr);
        }
    }
    return ret;
}