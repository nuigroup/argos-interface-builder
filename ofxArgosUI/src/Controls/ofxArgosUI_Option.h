#pragma once

#include "ofxArgosUI_Control.h"
#include "ofxArgosUI_Toggle.h"

//------------------------------------------------------------------------------ toggle
class ofxSimpleGuiOption : public ofxSimpleGuiToggle {
	
public:
	bool isOn;
	string group;
	
	ofxSimpleGuiOption(string name, string group) : ofxSimpleGuiToggle(name, value) {
		controlType = "Option";
	}
};
