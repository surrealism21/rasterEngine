// plans for this
/*

Types of colliders:
The square
The line
-that's really all you need to make Infinte. Shapes. with any algorithm, the square is just a Dumb optimization because that is faster

These are solid lines the actor-to-actor stuff will be handled with something else haha 

*/

#include "raster.hpp"

class dSolid_c : public dBase_c {
    void onCreate();
    void onDraw();
};

const Profile solidProfile = Profile<dSolid_c>(ActorID::Solid);

void dSolid_c::onCreate() {

}

void dSolid_c::onDraw() {
    ofSetColor(0, 0, 255, 255);
    ofDrawRectangle(90, 200, 100, 100);
    ofSetColor(255);
}