#include "raster.hpp"

void dBase_c::addToList() {
    fBase_c::instance.Actors.push_back(this);
    this->listPos = fBase_c::instance.Actors.size();
    cout << listPos << " is new base in list index (ActorID: " << (int)this->actorID << ")" << endl;
    // Run onCreate
    this->onCreate();
}

// PROBABLY doesn't actually work! Fix!!
std::list<dBase_c*>::iterator dBase_c::findMe() {
    // This is arguably more creature but it does this in O(1) time so
    std::list<dBase_c*>::iterator test = fBase_c::instance.Actors.begin();
    std::advance(test, this->listPos-1);

    return test;
}

// Sort of a fake because it doesn't actually do that until "garbage collection or whatever"
void dBase_c::removeFromList() {
    // Handle an error
    if (listPos == -1) {
        cout << "Tried to remove an object from global list, that had already been removed!" << endl;
        cout << "ActorID: " << (int)this->actorID << " @" << this << endl;
        cout << "Aborted" << endl;
        exit(1);
    }
    cout << "Trying to remove: Actor #" << this->listPos << endl;

    // Run onDelete
    this->onDelete();

    // Make sure we can't remove a removed actor
    this->listPos = -1;
}

// make sure these exist since C++ doesn't support abstract functions
void dBase_c::onDraw() { return; }
void dBase_c::systemExecute() { return; }
void dBase_c::onExecute() { return; }
void dBase_c::onCreate() { return; }
void dBase_c::onDelete() { return; }
void dBase_c::control(std::set<int> &keysPressed) { return; }
dBase_c::dBase_c() : actorID(ActorID::Num) { return; }
dBase_c::~dBase_c() { return; }

dBase_c* dBase_c::createOwnedActor(ActorID actor, bool add) {
    auto acr = fBase_c::instance.factory.create(actor);
    acr->owner = this;
    if (add) {
        acr->addToList();
    }
    // Return a pointer to the actor
    return acr;
}