#include "raster.hpp"

class ac_test : public dPhysicsActor_c {
    void onCreate();
    void onDraw();
    void control(std::set<int> &keysPressed);
    void onCollide(dPhysicsActor_c* other);
};

const Profile testProfile = Profile<ac_test>(ActorID::AC_Test);

void ac_test::onCreate() {
    this->box = ofRectangle(pos.x, pos.y, 16, 32);
    addToPhysicsList();
}

void ac_test::onDraw() {
    ofSetColor(255, 255, 0); 
    box.draw();


    ofSetColor(0, 255, 0);
    ofNoFill();
    box.trueDraw();
    ofSetColor(255, 0, 0);
    offsetBox.trueDraw();
    ofFill();
    ofSetColor(255);
}

void ac_test::control(std::set<int> &keysPressed) {
    const float speed = 4;
    if (keysPressed.count(OF_KEY_DOWN) > 0) {
        MoveY(speed);
    }
    else if (keysPressed.count(OF_KEY_UP) > 0) {
        MoveY(-speed);
    }

    if (keysPressed.count(OF_KEY_RIGHT) > 0) {
        MoveX(speed);
    }
    else if (keysPressed.count(OF_KEY_LEFT) > 0) {
        MoveX(-speed);
    }
}

void ac_test::onCollide(dPhysicsActor_c* other) {

}