#include "ofApp.hpp"
#include "raster.hpp"

int i = 0;

//--------------------------------------------------------------
void ofApp::setup() {
    auto scene = (dScene_c*)fBase_c::instance.factory.create(ActorID::Scene);
    cout << &scene->boundActors << endl;

    for (int i = 0; i < 32; i++) {
        SceneBoundActor* solid = scene->addActor(ActorID::Solid);
        solid->position.set(i*16*mul,400);
    }

    SceneBoundActor* test = scene->addActor(ActorID::AC_Test);
    test->position.set(50, 50);


    scene->addToList();
}

//--------------------------------------------------------------
void ofApp::update() {
    fBase_c::instance.commonExecute();
    fBase_c::instance.commonControl();
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofPushMatrix();
        fBase_c::instance.commonDraw();
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    fBase_c::instance.keysPressed.insert(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    // no two objects in this set will ever be alike so it's safe to just do this, probably
    fBase_c::instance.keysPressed.erase(key);
    // technically, this input thing is broken. But this could also work for a "no buttons pressed" case or smth
    if (fBase_c::instance.keysPressed.size()+1 == 1) {
        fBase_c::instance.keysPressed.insert(0xDEADBEEF);
    }
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
    scaleX = (w/internalX);
    scaleY = (h/internalY);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) { 

}