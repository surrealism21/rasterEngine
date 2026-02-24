// Class for scenes.
#include "actor.hpp"
#include "types.hpp"
#include "fbase.hpp"
#include <vector>
#include <thread>
using namespace std;

#include "scene.hpp"

// 100% a hack! but stl containers are dogshite
dScene_c::dScene_c() {
    boundActors = vector<SceneBoundActor*>();
}

void dScene_c::initActors() {
    // die
    for (auto &acr : boundActors) {
        // note this is not the global createactor because it auto-adds them to the list
        dBase_c* newAcr = fBase_c::instance.factory.create(acr->id);
        newAcr->pos = acr->position;
        newAcr->settings = acr->settings;
        newAcr->addToList();
        // free the memory it was using in the heap
        delete acr;
    }
    cout << "--- done ---" << endl;
    inited = true;
}

const Profile sceneProfile = Profile<dScene_c>(ActorID::Scene);

void dScene_c::onCreate() {
    inited = false;
    thread t(&dScene_c::initActors, this);
    cout << "Scene is preparing actors with thread ID "  << t.get_id() << ". Bye." << endl;

    // create the loading screen
    cout << "--- loading screen ---" << endl;
    loader = createOwnedActor(ActorID::LoadScreen);
    cout << "--- inits ---" << endl;
    t.detach();
}

void dScene_c::onExecute() { return; }
void dScene_c::onDraw() { return; }

SceneBoundActor* dScene_c::addActor(ActorID id) {
    // this is deleted in initActors(), no leakage
    SceneBoundActor* ac = new SceneBoundActor;
    ac->id = id;
    ac->position.set(0,0);
    ac->settings.settings = 0;
    this->boundActors.push_back(ac);
    return ac;
}