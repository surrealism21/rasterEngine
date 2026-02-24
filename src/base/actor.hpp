#pragma once
// yeah this causes errors because this include system is kind of Trish
#include "types.hpp"
#include "Actors.hpp"

// A class which updates and draws every frame. Has a XY position. Base actor
class dBase_c {
public:

    dBase_c();
    virtual ~dBase_c();

    // When added/removed from the global list
    virtual void onCreate();
    virtual void onDelete();

    // Haha, do not use this Jonathan!
    virtual void systemExecute();
    virtual void onExecute();
    
    virtual void onDraw();

    // Input. Passes by reference to avoid ram bloat
    virtual void control(std::set<int> &keysPressed);

    // Remove from / add to global actor list.
    void addToList();
    void removeFromList();
    std::list<dBase_c*>::iterator findMe();

    dBase_c* createOwnedActor(ActorID actor, bool add = true);

    // Content, not funcs

    s64 listPos;

    // Actor ID
    ActorID actorID;
    
    Vec2 pos;

    // settings...
    settingsType settings;

    // Owner. We do not have "parents" here.
    // uhm, that may have come out wrong. I AM --- interested in that and LIKE it when stuff happens
    dBase_c* owner;
};