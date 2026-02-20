#include "game.hpp"
#include "state.hpp"

class LoadscreenMgr : public dBase_c {
    void onCreate();
    void onExecute();

    typedef dState_c<LoadscreenMgr> State;
    dStateMgr_c<LoadscreenMgr> acState;
    DECLARE_STATE(Begin);
    DECLARE_STATE(Evil);

    int timer;
};

CREATE_STATE(LoadscreenMgr, Begin);
CREATE_STATE(LoadscreenMgr, Evil);

Profile loadscreenProfile = Profile<LoadscreenMgr>(ActorID::LoadScreen);

void LoadscreenMgr::onCreate() {
    timer = 0;
    INIT_STATES(&StateID_Begin);
}

void LoadscreenMgr::onExecute() {
    acState.execute();
}

void LoadscreenMgr::beginState_Begin() {
    cout << "Hi" << endl;
}

void LoadscreenMgr::executeState_Begin() {
    timer++;
    if (timer > 60) {
        acState.doStateChange(&StateID_Evil);
    }
    cout << "Trial amount finna it" << endl;
}

void LoadscreenMgr::endState_Begin() {
    cout << "You ran out of BEGIN" << endl;
}

void LoadscreenMgr::beginState_Evil() {
    cout << "Eviling" << endl;
    timer = 0;
}

void LoadscreenMgr::executeState_Evil() {
    timer++;
    if (timer > 90) {
        this->removeFromList();
    }
    cout << "gay seggs" << endl;
}

void LoadscreenMgr::endState_Evil() {
    cout << "Bye" << endl;
}