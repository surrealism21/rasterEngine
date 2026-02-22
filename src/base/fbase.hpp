#pragma once
#include "Actors.hpp"
#include "actor.hpp"
#include <unordered_map>
#include <typeindex>

// Executes and manages, everything.
// Do NOT run these functions anywhere lmao
class fBase_c {
public:
    std::list<dBase_c*> Actors;

    // Defined in fbase.cpp
    static fBase_c instance;

    void commonExecute();
    void commonDraw();
    void commonControl();

    // Keys currently being pressed.
    std::set<int> keysPressed;
    std::set<int> mouseButtons;

    Vec2 mousepos;
    Vec2 res;

    // add all this later
    //void doSceneChange();

    // This doesn't use smart pointers so hopefully it won't deallocate when being tossed around.
    class fFactory {
        using buildfunc = std::function<dBase_c*()>;
        std::unordered_map<ActorID, buildfunc> funcs;

    public:
        template <typename T>
        void registerType(ActorID id) {
            // Auto-generated build function, thanks to lambdas. C++98 can't beat this thing (i mean new versions of c++ are actually better than old versions so)
            funcs[id] = [id]() -> dBase_c* {
                T* self = new T; 
                self->actorID = id;
                return self;
            };
        }

        dBase_c* create(ActorID actor);
    };

    fFactory factory;
};

// Global funcs

// Creates actor and adds it to the list
void createActor(ActorID actor);

// Returns a %set which contains all actors of a certain ID.
// Performance intensive...
std::set<dBase_c*> searchActors(ActorID actorid);

// Returns first actor found of a certain ID. Useful if there's only one such instance alive, as tags are slower.
dBase_c* findFirstActor(ActorID actorid);

template <typename T>
class Profile {
public:
    Profile(ActorID id) {
        cout << "Preparing profile " << (int)id << endl;
        this->id = id;
        fBase_c::instance.factory.registerType<T>(id);
    }
    // whatever
    ActorID id;
};