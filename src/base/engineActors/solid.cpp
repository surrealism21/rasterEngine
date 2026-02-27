#include "raster.hpp"

class Solid : public dPhysicsActor_c {
    void onCreate();
    void onDraw();
    void onExecute();
};

const Profile solidProfile = Profile<Solid>(ActorID::Solid);

void Solid::onCreate() {
    this->box = ofRectangle(pos.x, pos.y, 24, 24);
    addToPhysicsList();
}

void Solid::onExecute() {

}

void Solid::onDraw() {
    ofSetColor(255, 0, 255);
    box.draw();
    ofNoFill();
    box.trueDraw();
    ofFill();
    ofSetColor(255);
}