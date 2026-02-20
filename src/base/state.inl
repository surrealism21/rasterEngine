// The state system
#include "state.hpp"

// the function calls here are surprisingly C-like because this is an object owned by another that calls functions on its' behalf

template <class owner>
void dStateMgr_c<owner>::execute() {
    currState->execute(*owningPtr);
}

// Now for the fun to begin.
template <class owner>
void dStateMgr_c<owner>::doStateChange(dState_c<owner>* state) {
    if (initialized == true) {
        // run current state end logic first!
        currState->end(*owningPtr);

        // set the last state to the current
        lastState = currState;
    }

    // Do state change
    currState = state;

    // Now we actually have a state set
    initialized = true;

    // Start it up
    currState->begin(*owningPtr);
}