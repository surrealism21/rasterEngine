#include "ofMain.hpp"
#include "ofApp.hpp"

// 100% a hack, but if this guy doesn't exist instantly then All Your Pointers Will Dangle Forever...
#include "base/fbase.hpp"
fBase_c fBase_c::instance;

//========================================================================
int main() {

	//Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
	ofGLWindowSettings settings;
	settings.setSize(1024, 768);
	settings.windowMode = OF_FULLSCREEN;

	auto window = ofCreateWindow(settings);

	ofRunApp(window, std::make_shared<ofApp>());
	ofRunMainLoop();

}
