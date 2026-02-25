#include "raster.hpp"

class Solid : public dPhysicsActor_c {
    void onCreate();
    void onDraw();
    void onExecute();
};

const Profile solidProfile = Profile<Solid>(ActorID::Solid);

void Solid::onCreate() {
    this->box = ofRectangle(pos.x, pos.y, 32, 32);
    addToPhysicsList();
}

void Solid::onExecute() {

}

void Solid::onDraw() {
    ofSetColor(255, 0, 255);
    ofDrawRectangle(box.position, box.width, box.height);
    ofSetColor(255);
}