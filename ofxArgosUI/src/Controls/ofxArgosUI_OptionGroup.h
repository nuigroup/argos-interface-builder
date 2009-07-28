#pragma once

#include "ofxArgosUI_Control.h"
#include "ofxArgosUI_Title.h"

class ofxSimpleGuiOptionGroup  : public ofxSimpleGuiTitle {
public:
	int *value;
	
	
	ofxSimpleGuiOptionGroup(string name, int *value) : ofxSimpleGuiTitle(name) {
		controlType = "OptionGroup";
	}
};
