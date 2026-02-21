#include "raster.hpp"
#include "state.hpp"

class LoadscreenMgr : public dBase_c {
    void onCreate();
    void onExecute();

    USING_STATES(LoadscreenMgr);
    DECLARE_STATE(Begin);
    DECLARE_STATE(Evil);

    int timer;
};

CREATE_STATE(LoadscreenMgr, Begin);
CREATE_STATE(LoadscreenMgr, Evil);

const Profile loadscreenProfile = Profile<LoadscreenMgr>(ActorID::LoadScreen);

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
        return;
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
    cout << "Yaoi is a better word for this. I love it." << endl;
}

void LoadscreenMgr::endState_Evil() {
    cout << "Bye" << endl;
}