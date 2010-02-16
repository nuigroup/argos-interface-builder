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
#include "ofxArgosUI_Util.h"

class ofxArgosUI_Button : public ofxArgosUI_Control {
	
public:
	
	bool*			value;

	bool			beToggle;
	bool			beenPressed;
	
	ofxArgosUI_Button(string name, int x, int y, int width, int height, bool *value) : ofxArgosUI_Control(name) {
		beToggle	= false;
		beenPressed = false;
		this->value	= value;

		controlType = "Button";
		OSCaddress = "/button"; 

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
		createPropertyBool("cantoggle", false);
	}

	void updateProperties(){
		name = getPropertyString("name", name);
		x = getPropertyInt("x", x);
		y = getPropertyInt("y", y);
		width = getPropertyInt("w", width);
		height = getPropertyInt("h", height);
		OSCaddress = getPropertyString("osc", OSCaddress);

		// Button Specific Stuff: 
	}
	
	void loadFromXML(ofxXmlSettings &XML) {
		set(XML.getValue("controls:" + controlType + "_" + key + ":value", 0));
	}
	
	void saveToXML(ofxXmlSettings &XML) {
		int tagNum =  XML.addTag(controlType);
			XML.setValue(controlType + ":" + "name", name, tagNum);
			XML.setValue(controlType + ":" + "x", x, tagNum);
			XML.setValue(controlType + ":" + "y", y, tagNum);
			XML.setValue(controlType + ":" + "width", width, tagNum);
			XML.setValue(controlType + ":" + "height", height, tagNum);
			XML.setValue(controlType + ":" + "OSC", OSCaddress, tagNum);
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
	}

	void setToggleMode(bool b) {
		beToggle = b;
	}
	
	// ============================================= Mouse

	void focusActive() { if (canfocus) focus.set(this); }

	void onPress(int x, int y, int button) {
		beenPressed = true;	
		if(beToggle) (*value) = !(*value); 
		else (*value) = true;

		oschandler.sendOSC(1, OSCaddress);
	}
	
	void onRelease(int x, int y, int button) {
		if(!beToggle) (*value) = false;
	}

	// ============================================= Touch
	void onTouchDown(float x, float y, int ID){
		beenPressed = true;	
		if(beToggle) (*value) = !(*value); 
		else (*value) = true;
	}

	void onTouchMoveOver(float x, float y, int ID){
		beenPressed = true;	
		if(beToggle) (*value) = !(*value); 
		else (*value) = true;
	}
	void onTouchUp(float x, float y, int ID){
		if(!beToggle) (*value) = false;
	}

	void update() {
		if(!enabled) return;
		enabled = false;

		updateProperties(); 
	}

	void draw(float x, float y) {
	
		enabled = true;

		setPos(x, y);

		glPushMatrix();

			glTranslatef(x, y, 0);

			ofFill();
			setTextBGColor();

			if((*value) && beToggle) {
				ofSetColor(0x7d87d7);
			}

			rRectangle(0, 0, width, height, 8); 

			setTextColor();
			argosText::font.drawString(name, ((width/2) - (name.length() * 3.5)), (height/2) + 2);

		glPopMatrix();

	}

};
