#pragma once
#include "types.hpp"
// fun, this is just a struct
class SceneBoundActor {
public:
    ActorID id;
    settingsType settings;
    Vec2 position;

    SceneBoundActor() {
        settings.settings = 0;
        position = Vec2(0, 0);
    }
};

class dScene_c : public dBase_c {
public:
    dScene_c();

    void onCreate();
    //void onDelete();
    virtual void onExecute();
    virtual void onDraw();

    // To be threaded
    void initActors();

    bool inited;
    vector<SceneBoundActor*> boundActors;

    dBase_c* loader;

    bool testBool;
};