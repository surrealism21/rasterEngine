#pragma once
#include <ofMain.hpp>

typedef ofVec2f Vec2;
typedef ofVec3f Vec3;

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long long u64;
typedef signed long long s64;

typedef union settingsType {
    u64 settings;
    u64* multiSettings;
} settingsType;

////////////
// SHAPES //
////////////

// Since this engine's physics NEEDS a 5x larger "true" interal size, we have the multiply everything.
// All of our stuff is below...
// If you think this is evil the "floating point zone" (where decimals do not matter) is 2e23, or 4e22 in visual coordinates. You'll be fine.
// I NOT using doubles and also doubling the memory usage of games
// if there ever comes a need to fuck with the scaling. 5 is a whole number and is (more) accurate
const float mul = 5;

class RasRectangle : public ofRectangle {
public:
    RasRectangle();
    RasRectangle(float x, float y, float width, float height);
    RasRectangle(Vec2 position, float width, float height);
    RasRectangle(ofRectangle rect);

    RasRectangle operator=(ofRectangle other);
    inline void draw() {
        ofDrawRectangle(position/mul, width/mul, height/mul);
    }

    // Use draw(). This will draw the rectangle at its' interal size, 5 times its' visual size. Do not use!
    inline void trueDraw() {
        ofDrawRectangle(position, width, height);
    }

    void set(float x, float y, float width, float height);
};