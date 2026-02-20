#pragma once
#include "game.hpp"
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