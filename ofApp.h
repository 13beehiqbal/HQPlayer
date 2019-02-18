#pragma once

#include "HQPlayer.h"
#include "ofMain.h"
#include "ofxUI.h"


class ofApp : public ofBaseApp{
public:
	void setup();//setups the program by reading all data from files and setting gui and default values of widgets
	void update();//updates in background the values changing
	void draw();//draws constantly changing features like slider values etc
	void exit(); //writes files , delete (frees memory) 
	ofTrueTypeFont* listplay;
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void drawGrid(float x, float y);
	ofxUIRangeSlider* range;
	void setGUI();
	ofxUIToggle* markfavSearch;
	ofxUILabelButton* queueSearch;
	ofxUILabelButton* playSearch;
	ofxUILabelButton* deleteSearch;
	song* searchedSong;
	int searchedIndex;
	ofxUISuperCanvas *gui3;
	HQPlayer* HQplayer;
	ofxUILabel* current;
	ofxUITextInput *textInput; 
	ofxUITextInput *textInput1; 
	ofxUITextInput *textInput2; 
	ofxUISlider * track;
	ofxUISlider * equalizer0;
	ofxUISlider * equalizer1;
	ofxUISlider * equalizer2;
	ofxUISlider * equalizer3;
	ofxUISlider * equalizer4;
	ofxUISlider * equalizer5;
	ofxUISlider * equalizer6;
	ofxUISlider * equalizer7;
	ofxUISlider * equalizer8;
	ofxUISlider * equalizer9;
	ofxUISlider * equalizer10;
	ofxUISlider * equalizer11;
	ofxUISlider * equalizer12;
	ofxUISlider * equalizer13;
	ofxUICircleSlider* beats;

	bool hideGUI;

	float red, green, blue;
	bool bdrawGrid;
	bool bdrawPadding;
	Heap* mostPlayed;
	void guiEvent(ofxUIEventArgs &e);
	string playlist;
	int min,max;
	int selection;
	int nBandsToGet;
	float 	* fftSmoothed;
	ofImage *img;


};
