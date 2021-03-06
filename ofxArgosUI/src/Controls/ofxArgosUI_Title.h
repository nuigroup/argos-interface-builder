/***********************************************************************
 
 Copyright (c) 2009, 2010 Dimitri Diakopoulos, http://www.dimitridiakopoulos.com/


 Portions Copyright (c) 2008, 2009 Memo Aktens, http://www.memo.tv/
 -> Based on ofxSimpleGuiToo
 
 Portions Copyright (c) 2008 Todd Vanderlin, http://toddvanderlin.com/
 -> Inspired by ofxSimpleGui API

	Redistribution and use in source and binary forms, with or without modification, 
	are permitted provided that the following conditions are met:

	1. Redistributions of source code must retain the above copyright notice, 
	this list of conditions and the following disclaimer.

	2. Redistributions in binary form must reproduce the above copyright notice, 
	this list of conditions and the following disclaimer in the documentation and/or 
	other materials provided with the distribution.

	3. The name of the author may not be used to endorse or promote products derived 
	from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
	ARE DISCLAIMED. IN NOEVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, 
	INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
	(INCLUDING, BUT NOT LIMITED TO,PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
	LOSS OF USE, DATA, ORPROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
	AND ON ANY THEORY OFLIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
	OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
	OF THE USE OF THIS SOFTWARE,EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 

*************************************************************************/ 

// This class should be turned into ofxArgosUI_ViewTab
// The only feature that uses this class is Views, which uses it to scroll
// through the different views. 

#pragma once

#include "ofxArgosUI_Control.h"

class ofxArgosUI_Title : public ofxArgosUI_Control {
	
public:
	
	bool*			value;
	
	bool			beToggle;
	bool			beenPressed;
	
	ofxArgosUI_Title(string name, bool *value = NULL) : ofxArgosUI_Control(name) {
		beToggle	= false;
		beenPressed = false;
		this->value	= value;
		controlType = "Title";

		setup();
	}
	
	void setup() {
		//setSize();
	}
	
	void loadFromXML(ofxXmlSettings &XML) {
		if(!value) return;
		set(XML.getValue("controls:" + controlType + "_" + key + ":value", 0));
	}
	
	void saveToXML(ofxXmlSettings &XML) {
		if(!value) return;
		XML.addTag(controlType + "_" + key);
		XML.pushTag(controlType + "_" + key);
		XML.addValue("name", name);
		XML.addValue("value", getValue());
		XML.popTag();
	}
	
	
	bool getValue() {
		if(!value) return false;
		return (*value);
	}
	void set(bool b) {
		if(!value) return;
		(*value) = b;
	}
	void toggle() {
		if(!value) return;
		(*value) = !(*value); 
	}
	
	void setToggleMode(bool b) {
		if(!value) return;
		beToggle = b;
	}
	
	void onPress(int x, int y, int button) {
		if(!value) return;
		beenPressed = true;	
		if(beToggle) (*value) = !(*value); 
		else (*value) = true;
	}
	
	void onRelease(int x, int y, int button) {
		if(!value) return;
		if(!beToggle) (*value) = false;
	}
	
	void draw(float x, float y) {
		setPos(x, y);
		
		glPushMatrix();
			glTranslatef(x, y, 0);
			
			ofEnableAlphaBlending();
			ofFill();
			setTextBGColor(value != NULL);
			ofRect(0, 0, width, height);
			
			if(value && (*value) && beToggle) {
				setTextColor();
			}
			
			setTextColor(value != NULL);
			ofDrawBitmapString(name, 3, 15);
			
			ofDisableAlphaBlending();
			
		glPopMatrix();
	}
	
};
