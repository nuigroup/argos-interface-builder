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
#pragma once

#include "ofxArgosUI_Control.h"

class ofxArgosUI_Toggle : public ofxArgosUI_Control {
	
public:

	bool	*value;
	
	ofxArgosUI_Toggle(string name, int x, int y, int width, int height, bool *value) : ofxArgosUI_Control(name) {
		this->value	= value;
		
		controlType = "Toggle";
		OSCaddress = "/toggle"; 

		setup(x, y, width, height);

		createProperties();
		updateProperties(); 
	}
	
	void setup(int _x, int _y, int _width, int _height) {
		setPos(_x, _y); 
		setSize(_width, _height);
	}

	void createProperties() {
		ofxArgosUI_Control::createProperties(); 
	}

	void updateProperties(){
		name = getPropertyString("name", name);
		x = getPropertyInt("x", x);
		y = getPropertyInt("y", y);
		width = getPropertyInt("w", width);
		height = getPropertyInt("h", height);
		OSCaddress = getPropertyString("osc", OSCaddress);

		// Toggle Specific Stuff: 
	}
	
	void loadFromXML(ofxXmlSettings &XML) {}
	
	void saveToXML(ofxXmlSettings &XML) {
		int tagNum =  XML.addTag(controlType);
			XML.setValue(controlType + ":" + "name", name, tagNum);
			XML.setValue(controlType + ":" + "x", x, tagNum);
			XML.setValue(controlType + ":" + "y", y, tagNum);
			XML.setValue(controlType + ":" + "width", width, tagNum);
			XML.setValue(controlType + ":" + "height", height, tagNum);
			XML.setValue(controlType + ":" + "osc", OSCaddress, tagNum);
		XML.popTag();
	}
	
	
	bool getValue() {
		return (*value);
	}
	void set(bool b) {
		(*value) = b;
	}
	void toggle() {
		(*value) = !(*value); 
		oschandler.sendOSC(*value, OSCaddress);
	}

	// ============================================= Mouse

	void focusActive() { if (canfocus) focus.set(this); }

	void onPress(int x, int y, int button) {
		toggle();
	}

	// ============================================= Touch
	void onTouchDown(float x, float y, int ID){
		toggle();
	}

	void update() {
		if(!enabled) return;
		enabled = false;

		updateProperties(); 
	}
	
	void draw(float x, float y) {

		enabled = true;

		setPos(x, y);
		
		ofEnableAlphaBlending();

		glPushMatrix();

			glTranslatef(x, y, 0);
			
			// Left-side Box
			ofNoFill();
			setTextBGColor();  
			ofRect(0, 0, height, height);

			// Draw X
			if((*value)) {
				ofEnableSmoothing();
					ofFill();
					ofLine(0, 0, height, height);
					ofLine(height, 0, 0, height);
					ofNoFill();
					ofLine(0, 0, height, height);
					ofLine(height, 0, 0, height);
				ofDisableSmoothing();
			}

			ofFill();

			ofSetColor(0xdfdfdf); 
			argosText::font.drawString(name, height + 2, 14);

		glPopMatrix();

		ofDisableAlphaBlending();
	}
};
