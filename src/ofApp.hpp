#pragma once

#include "ofMain.hpp"
#include "types.hpp"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		float internalX = 854;
		float internalY = 480;

		float scaleX;
		float scaleY;
};
