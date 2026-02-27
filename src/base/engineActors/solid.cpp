#include "raster.hpp"

class Solid : public dPhysicsActor_c {
    void onCreate();
    void onDraw();
    void debugDraw();
    void onExecute();
};

const Profile solidProfile = Profile<Solid>(ActorID::Solid);

void Solid::onCreate() {
    this->box = ofRectangle(pos.x, pos.y, 16, 16);
    addToPhysicsList();
}

void Solid::onExecute() {

}

void Solid::onDraw() {

}

void Solid::debugDraw() {
    ofSetColor(255, 0, 255, 100);
    box.draw();
    ofSetColor(255);
}