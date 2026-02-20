#include "game.hpp"

// FIXME: Maybe only use 1 loop??? I don't think I can avoid the drawing stuff, but...

// This one is more complex because it runs last and handles actor deletions. The iterator gets very fucked if we do not baby it,
// so we do that here. RemoveFromList is an illusion. Bye.
void fBase_c::commonExecute() {
    for (auto iter = Actors.begin(); iter != Actors.end();) {
        dBase_c* curr = *iter;
        if (curr->listPos == -1) {
            iter = Actors.erase(iter);
            delete curr;
            continue;
        }
        else {
            ++iter;
        }
        curr->onExecute(); 
    }
}

void fBase_c::commonDraw() {
    for (dBase_c* curr : Actors) {
        if (curr->listPos != -1) {
            curr->onDraw();
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
    auto it = funcs.find(actor);
    if (it != funcs.end()) {
        return it->second();
    }
    return NULL;
}