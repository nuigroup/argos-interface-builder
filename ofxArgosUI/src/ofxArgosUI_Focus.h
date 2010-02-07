#pragma once

#include "ofxArgosUI_Control.h"

class ofxArgosUI_Focus {

public: 

	bool verbose; 

	bool loaded; 

	ofxArgosUI_Control *focused; 

	ofxArgosUI_Focus() {
		verbose = true; 
		loaded = false; 
	}

	void set(ofxArgosUI_Control *ctrl){
		if (verbose) printf("ofxArgosUI_Focus::set\n");
		loaded = false; 
		focused = ctrl;
	}

	void clear(){
		if (verbose) printf("ofxArgosUI_Focus::clear\n"); 
		focused = NULL; 
	}	

	void showFocus(){
		if ((focused != NULL) && (focused->canfocus == true)){
			ofNoFill(); 
			ofSetColor(255, 255, 255); 
			ofSetLineWidth(1.0);
				
			// Top Left
			ofLine((focused->x-4), (focused->y-4), (focused->x+8), (focused->y-4));
			ofLine((focused->x-4), (focused->y-4), (focused->x-4), (focused->y+8));

			// Top Right
			ofLine(((focused->x + focused->width)+4), (focused->y-4), ((focused->x + focused->width)-8), (focused->y-4));
			ofLine(((focused->x + focused->width)+4), (focused->y-4), ((focused->x + focused->width)+4), (focused->y+8));

			// Bottom Left
			ofLine((focused->x-4), ((focused->y + focused->height)+4), (focused->x-4), ((focused->y + focused->height)-8));
			ofLine((focused->x-4), ((focused->y + focused->height)+4), (focused->x+8), ((focused->y + focused->height)+4));

			// Bottom Right
			ofLine(((focused->x + focused->width)+4), ((focused->y + focused->height)+4), ((focused->x + focused->width)-8), ((focused->y + focused->height)+4));
			ofLine(((focused->x + focused->width)+4), ((focused->y + focused->height)+4), ((focused->x + focused->width)+4), ((focused->y + focused->height)-8));

		}
	}
}; 

extern ofxArgosUI_Focus focus; 
extern ofxArgosUI_Focus textfocus; 