#include "ofApp.hpp"
#include "raster.hpp"

int i = 0;

//--------------------------------------------------------------
void ofApp::setup() {
    scaleX = 1;
    scaleY = 1;

    auto scene = (dScene_c*)fBase_c::instance.factory.create(ActorID::Scene);
    cout << &scene->boundActors << endl;
    
    scene->addActor(ActorID::Solid);

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
        ofScale(scaleX, scaleY, 1);
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