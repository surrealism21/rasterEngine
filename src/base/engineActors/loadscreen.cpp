#include "raster.hpp"

// A loading screen. You can customize it...
class Loadscreen : public dBase_c {
    void onCreate();
    void onExecute();
    void onDraw();

    dScene_c* scene;
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
}

void Loadscreen::onDraw() {
    Vec3 begin = Vec3(0, 0, 0);
    Vec3 end = Vec3(50, 50, 50);
    ofDrawArrow(begin, end);
}