#pragma once
#include <functional>

template <class owner>
class dState_c {
public:
    using funcPtr = std::function<void(owner&)>;

    dState_c(const char* name, funcPtr begin, funcPtr execute, funcPtr end) {
        this->begin = begin;
        this->execute = execute;
        this->end = end;
    }

    funcPtr begin;
    funcPtr execute;
    funcPtr end;
};

// This just runs functions from other states
template <class owner>
class dStateMgr_c {
public:
    dStateMgr_c() {
        initialized = false;
        return;
    }

    // If there's no current state, this will obviously crash the program. You should set the state during onCreate(). 
    // This is for performance reasons. Checking if a pointer exists every frame would be very wasteful!
    void execute();
    void doStateChange(dState_c<owner>* state);
    // added for fun, but this could probably be useful
    void revertToLastState();

    bool initialized;
    dState_c<owner>* currState;
    dState_c<owner>* lastState;
    owner* owningPtr;
};

// Declare a state. To be used inside a class definition. State will be called "StateID_[NAME]".
// The methods will be called beginState_[NAME], executeState_[NAME] and endState_[NAME]...
#define DECLARE_STATE(NAME) \
	static State StateID_##NAME; \
	void beginState_##NAME(); \
	void executeState_##NAME(); \
	void endState_##NAME();

// Declare a state. To be used inside a class definition. State will be called "StateID_[NAME]". Oh! And virtually.
// The methods will be called beginState_[NAME], executeState_[NAME] and endState_[NAME]...
#define DECLARE_STATE_VIRTUAL(NAME) \
	static State StateID_##NAME; \
	virtual void beginState_##NAME(); \
	virtual void executeState_##NAME(); \
	virtual void endState_##NAME();

// Declare a state, with somebody else's preferred names. To be used inside a class definition. State will be called "StateID_[NAME]".
// The methods will be called beginState_[NAME], executeState_[NAME] and endState_[NAME]...
// You will need to use CREATE_STATE_ALT.
#define DECLARE_STATE_ALT(NAME) \
	static State StateID_##NAME; \
	void initializeState_##NAME(); \
	void executeState_##NAME(); \
	void finalizeState_##NAME();

// Declare a state, with somebody else's preferred names. Oh! And virtually.
#define DECLARE_STATE_ALT_VIRTUAL(NAME) \
	static State StateID_##NAME; \
	virtual void initializeState_##NAME(); \
	virtual void executeState_##NAME(); \
	virtual void finalizeState_##NAME();

// Create a state's functions. Use outside of class.
#define CREATE_STATE(CLASS, NAME) \
	CLASS::State CLASS::StateID_##NAME \
		(#CLASS "::StateID_" #NAME, \
		&CLASS::beginState_##NAME, \
		&CLASS::executeState_##NAME, \
		&CLASS::endState_##NAME);

// Create a state's functions. Use outside of class. Use with the alternative names.
#define CREATE_STATE_ALT(CLASS, NAME) \
	CLASS::State CLASS::StateID_##NAME \
		(#CLASS "::StateID_" #NAME, \
		&CLASS::initializeState_##NAME, \
		&CLASS::executeState_##NAME, \
		&CLASS::finalizeState_##NAME);

// Create a state manager called acState. Required for using states
#define USING_STATES(CLASS) \
	typedef dState_c<CLASS> State; \
    dStateMgr_c<CLASS> acState;

// Start up the STATE MANAGER. State is set to STARTING_STATE
#define INIT_STATES(STARTING_STATE) \
    acState.owningPtr = this; \
    acState.doStateChange(STARTING_STATE);

#include "state.inl"