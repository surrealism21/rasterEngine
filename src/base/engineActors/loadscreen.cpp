#include "raster.hpp"

// A loading screen. You can customize it...
class Loadscreen : public dBase_c {
    void onCreate();
    void onExecute();
    void onDraw();

    dScene_c* scene;

    string periods;
};

const Profile loaderProfile = Profile<Loadscreen>(ActorID::LoadScreen);

void Loadscreen::onCreate() {
    scene = (dScene_c*)owner;
}

void Loadscreen::onExecute() {
    // this is always like this
    if (scene->inited) {
        this->removeFromList();
    }
    periods += ".";
}

void Loadscreen::onDraw() {
    ofSetColor(0);
    ofDrawRectangle(0, 0, 1080, 1920);
    ofSetColor(255);
    
    ofDrawBitmapString("Loading"+periods, 0, 10);
}